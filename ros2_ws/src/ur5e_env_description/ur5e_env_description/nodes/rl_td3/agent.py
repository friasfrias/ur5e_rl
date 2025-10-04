import os
import torch as T
import torch.nn.functional as F
import numpy as np
from buffer import ReplayBuffer
from networks import ActorNetwork, CriticNetwork

class Agent:
    def __init__(
        self, alpha, beta, input_dims, tau, env,
        gamma=0.99, update_actor_interval=2, warmup=1000,
        n_actions=2, max_size=1_000_000, layer1_size=400, layer2_size=300,
        batch_size=256, noise=0.1
    ):
        # Hyperparameters
        self.gamma = gamma
        self.tau = tau
        self.batch_size = batch_size
        self.learn_step_cntr = 0
        self.time_step = 0
        self.warmup = warmup
        self.n_actions = n_actions
        self.update_actor_iter = update_actor_interval
        self.noise = noise

        # Action bounds (como tens no repo original)
        self.max_action = env.action_space.high
        self.min_action = env.action_space.low

        # Device
        self.device = T.device("cuda" if T.cuda.is_available() else "cpu")

        # Replay buffer
        input_dim = input_dims[0] if isinstance(input_dims, tuple) else input_dims
        self.memory = ReplayBuffer(
            max_size, input_dim, n_actions,
            device=("cuda" if T.cuda.is_available() else "cpu")
        )

        # Networks
        self.actor = ActorNetwork(
            input_dims=input_dims, fc1_dims=layer1_size, fc2_dims=layer2_size,
            n_actions=n_actions, name='actor', learning_rate=alpha
        ).to(self.device)

        self.target_actor = ActorNetwork(
            input_dims=input_dims, fc1_dims=layer1_size, fc2_dims=layer2_size,
            n_actions=n_actions, name='target_actor', learning_rate=alpha
        ).to(self.device)

        self.critic_1 = CriticNetwork(
            input_dims=input_dims, fc1_dims=layer1_size, fc2_dims=layer2_size,
            n_actions=n_actions, name='critic_1', learning_rate=beta
        ).to(self.device)

        self.critic_2 = CriticNetwork(
            input_dims=input_dims, fc1_dims=layer1_size, fc2_dims=layer2_size,
            n_actions=n_actions, name='critic_2', learning_rate=beta
        ).to(self.device)

        self.target_critic_1 = CriticNetwork(
            input_dims=input_dims, fc1_dims=layer1_size, fc2_dims=layer2_size,
            n_actions=n_actions, name='target_critic_1', learning_rate=beta
        ).to(self.device)

        self.target_critic_2 = CriticNetwork(
            input_dims=input_dims, fc1_dims=layer1_size, fc2_dims=layer2_size,
            n_actions=n_actions, name='target_critic_2', learning_rate=beta
        ).to(self.device)

        # Sync targets
        self.update_network_parameters(tau=1)

    def choose_action(self, observation, validation=False):
        if self.time_step < self.warmup and not validation:
            # warmup: uniforme nos limites de ação
            low  = T.tensor(self.min_action, dtype=T.float32, device=self.actor.device)
            high = T.tensor(self.max_action, dtype=T.float32, device=self.actor.device)
            mu = low + (high - low) * T.rand(self.n_actions, device=self.actor.device)
        else:
            state = T.tensor(observation, dtype=T.float32, device=self.actor.device)
            mu = self.actor(state)

        if not validation:
            noise = T.tensor(
                np.random.normal(0, self.noise, size=self.n_actions),
                dtype=T.float32, device=mu.device
            )
            mu = mu + noise

        low  = T.tensor(self.min_action, dtype=T.float32, device=mu.device)
        high = T.tensor(self.max_action, dtype=T.float32, device=mu.device)
        mu = T.max(T.min(mu, high), low)

        self.time_step += 1
        return mu.cpu().detach().numpy()



    def remember(self, state, action, reward, new_state, terminated, truncated):
        """
        Guarda transition com flags separados.
        """
        self.memory.store_transition(state, action, reward, new_state, terminated, truncated)

    def learn(self):
        if len(self.memory) < self.batch_size:
            return

        # já vêm como Tensors (device certo, ver buffer)
        state, action, reward, new_state, terminated, truncated = \
            self.memory.sample_buffer(self.batch_size)

        device = self.critic_1.device

        # garante dtype correto e device (no-op se já estiverem)
        state      = state.to(device=device, dtype=T.float32)
        new_state  = new_state.to(device=device, dtype=T.float32)
        action     = action.to(device=device, dtype=T.float32)
        reward     = reward.to(device=device, dtype=T.float32).view(-1, 1)
        terminated = terminated.to(device=device, dtype=T.bool)
        truncated  = truncated.to(device=device, dtype=T.bool)

        done = (terminated | truncated).to(dtype=T.float32).view(-1, 1)

        # --- target policy smoothing ---
        with T.no_grad():
            target_actions = self.target_actor(new_state)
            noise = T.clamp(T.randn_like(target_actions) * 0.2, -0.5, 0.5)
            target_actions = T.clamp(target_actions + noise,
                                    T.tensor(self.min_action, device=device),
                                    T.tensor(self.max_action, device=device))

            q1_next = self.target_critic_1(new_state, target_actions)
            q2_next = self.target_critic_2(new_state, target_actions)
            q_next  = T.min(q1_next, q2_next)

            target = reward + self.gamma * (1.0 - done) * q_next  # máscara (1 - done)

        # --- critic update ---
        self.critic_1.optimizer.zero_grad()
        self.critic_2.optimizer.zero_grad()

        q1 = self.critic_1(state, action)
        q2 = self.critic_2(state, action)

        critic_loss = F.mse_loss(q1, target) + F.mse_loss(q2, target)
        critic_loss.backward()
        self.critic_1.optimizer.step()
        self.critic_2.optimizer.step()

        self.learn_step_cntr += 1
        if self.learn_step_cntr % self.update_actor_iter != 0:
            return

        # --- actor update (delayed) ---
        self.actor.optimizer.zero_grad()
        actor_actions = self.actor(state)
        actor_loss = -self.critic_1(state, actor_actions).mean()
        actor_loss.backward()
        self.actor.optimizer.step()

        # --- soft update ---
        self.update_network_parameters()




    def update_network_parameters(self, tau=None):
        if tau is None:
            tau = self.tau

        # State dicts
        actor_params         = dict(self.actor.named_parameters())
        target_actor_params  = dict(self.target_actor.named_parameters())
        critic1_params       = dict(self.critic_1.named_parameters())
        target_critic1_params= dict(self.target_critic_1.named_parameters())
        critic2_params       = dict(self.critic_2.named_parameters())
        target_critic2_params= dict(self.target_critic_2.named_parameters())

        # Polyak averaging
        for name in critic1_params:
            critic1_params[name] = tau * critic1_params[name].clone() + \
                                   (1 - tau) * target_critic1_params[name].clone()
        for name in critic2_params:
            critic2_params[name] = tau * critic2_params[name].clone() + \
                                   (1 - tau) * target_critic2_params[name].clone()
        for name in actor_params:
            actor_params[name] = tau * actor_params[name].clone() + \
                                 (1 - tau) * target_actor_params[name].clone()

        # Load
        self.target_critic_1.load_state_dict(critic1_params)
        self.target_critic_2.load_state_dict(critic2_params)
        self.target_actor.load_state_dict(actor_params)

    def save_models(self):
        self.actor.save_checkpoint()
        self.target_actor.save_checkpoint()
        self.critic_1.save_checkpoint()
        self.critic_2.save_checkpoint()
        self.target_critic_1.save_checkpoint()
        self.target_critic_2.save_checkpoint()

    def load_models(self):
        try:
            self.actor.load_checkpoint()
            self.target_actor.load_checkpoint()
            self.critic_1.load_checkpoint()
            self.critic_2.load_checkpoint()
            self.target_critic_1.load_checkpoint()
            self.target_critic_2.load_checkpoint()
            print("-----------------------------------------")
            print("Successfully loaded models")
        except Exception as e:
            print(f"Failed to load models. Starting from scratch. ({e})")
