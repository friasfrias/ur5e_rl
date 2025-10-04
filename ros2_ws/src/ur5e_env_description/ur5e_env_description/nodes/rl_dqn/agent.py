import random
import numpy as np
import torch
import torch.nn.functional as F
import torch.optim as optim
from torch.utils.tensorboard import SummaryWriter
import time
import os
import datetime
from env import BalanceEnv


from model import DQNNetwork, soft_update
from replay_buffer import ReplayBuffer

class DQNAgent:
    """
    Agente DQN com principal/target networks
    """
    def __init__(self, env, n_observations, n_actions, hidden_layer = 128, warmup = 5000, lr=0.0001, gamma=0.99, buffer_capacity=100000,
                batch_size=64, epsilon_start=1.0, epsilon_end=0.1, tau=0.005):
        
        self.env = env
        self.gamma = gamma
        self.tau = tau
        self.batch_size = batch_size
        self.epsilon = epsilon_start
        self.epsilon_end = epsilon_end
        self.epsilon_decay = ((epsilon_end/epsilon_start)**(1/warmup)) # Find the right value to take epsilon to min_epsilon over 10000 steps
        self.step_count = 0
        self.n_actions = n_actions
        self.warmup = warmup

        self.device = torch.device('cuda:0' if torch.cuda.is_available() else 'cpu')

        # Criar redes 

        self.principal_net = DQNNetwork(n_observations, n_actions, hidden_layer).to(self.device)

        self.target_net = DQNNetwork(n_observations, n_actions, hidden_layer).to(self.device)
        self.target_net.load_state_dict(self.principal_net.state_dict())       

        # Otimizador e buffer de replay
        self.optimizer = optim.Adam(self.principal_net.parameters(), lr=lr)
        self.memory = ReplayBuffer(max_size=buffer_capacity, input_shape=(n_observations,), device=self.device)

    def choose_action(self, state):
        """
        Seleção ε-greedy com warmup.
        - Nos primeiros `warmup` steps usa sempre ação aleatória.
        - Depois, com probabilidade ε explora aleatoriamente,
          caso contrário escolhe argmax Q(s,a).
        Após `warmup`, ε decresce linearmente até epsilon_end.
        """
        # 1) Exploração pura no warmup
        if self.step_count < self.warmup:
            action = self.env.action_space.sample()
        else:
            # 2) ε-greedy normal
            if random.random() < self.epsilon:
                action = self.env.action_space.sample()
            else:
                state_v = torch.tensor(state, dtype=torch.float32, device=self.device).unsqueeze(0)
                q_values  = self.principal_net(state_v)
                action  = torch.argmax(q_values, dim=1).item()

        # 3) Conte o passo e atualize ε (apenas após warmup)
        self.step_count += 1
        if self.step_count >= self.warmup:
            self.epsilon = max(self.epsilon_end, self.epsilon * self.epsilon_decay)

        return action

    def train(self, episodes, max_episode_steps, summary_writer_suffix):

        # Gera um nome do tipo: runs/dqn_250808_1542_lr1e-4_bs64
        date = datetime.datetime.now().strftime("%y%m%d_%H%M")
        summary_writer_name = f"runs/DQN_{date}_{summary_writer_suffix}"

        writer = SummaryWriter(summary_writer_name)

        if not os.path.exists('models'):
            os.makedirs('models')

        total_steps = 0

        for episode in range(episodes):

            episode_reward = 0
            episode_steps = 0
            episode_start_time = time.time()

            state, _ = self.env.reset()
            done = False

            while not done and episode_steps < max_episode_steps:
                action = self.choose_action(state)
                next_state, reward, terminated, truncated, info = self.env.step(action)

                done = bool(terminated) or bool(truncated)


                if done:
                    # regista a transição final, se quiseres
                    self.memory.store_transition(state, action, reward, next_state, done)
                    break

                self.memory.store_transition(state, action, reward, next_state, done)

                state = next_state
                episode_reward += reward
                episode_steps += 1
                total_steps += 1

                # QSA = Q-value, state, action

                if self.memory.can_sample(self.batch_size):

                    states, actions, rewards, next_states, dones = self.memory.sample_buffer(self.batch_size)

                    dones = dones.unsqueeze(1).float()

                    q_values = self.principal_net(states)
                    actions = actions.long()
                    qsa_batch = q_values.gather(1, actions) 



                    next_actions = torch.argmax(self.principal_net(next_states), dim=1, keepdim=True)

                    next_q_values = self.target_net(next_states).gather(1, next_actions)

                    target_b = rewards + (1 - dones) * self.gamma * next_q_values


                    loss = F.mse_loss(qsa_batch, target_b.detach())

                    writer.add_scalar("Loss/model", loss.item(), total_steps)

                    self.optimizer.zero_grad()
                    loss.backward()
                    self.optimizer.step()

                    soft_update(self.target_net, self.principal_net, self.tau)
                    
            
            self.principal_net.save_the_model()

            episode_time = time.time() - episode_start_time

            writer.add_scalar('Score', episode_reward, episode)
            writer.add_scalar('Epsilon', self.epsilon, episode)
            writer.add_scalar("Time/Episode", episode_time, episode)

            print(f"Completed episode {episode} with score {episode_reward}")
            print(f"Episode Time: {episode_time:1f} seconds")
            print(f"Episode Steps: {episode_steps}")

        writer.close()

    def test(self):

        self.principal_net.load_the_model()
        self.principal_net.eval()

        # Mantém ε em zero para política determinística
        prev_epsilon = self.epsilon
        self.epsilon = 0.0

        done = False
        episode_reward = 0
        episode_steps = 0
        total_steps = 0
        reward = 0
        state, info = self.env.reset()

        while not done:

            state_v = torch.tensor(state, dtype=torch.float32, device=self.device).unsqueeze(0)
            q_values  = self.principal_net(state_v)
            action  = torch.argmax(q_values, dim=1).item()

            next_state, reward, terminated, truncated, info = self.env.step(action)
            done = bool(terminated) or bool(truncated)


            if(done):
                break

            state = next_state
            episode_reward += reward
            episode_steps += 1
            total_steps += 1

            print(f"Test Episode: reward={episode_reward:.2f}, steps={episode_steps}")

        # Restaura modo treino e ε
        self.epsilon = prev_epsilon
        self.principal_net.train()

       





    

         

