import os
import time
import numpy as np
from agent import Agent
from buffer import ReplayBuffer
from torch.utils.tensorboard import SummaryWriter
from env import BalanceEnv  # <- replace with your custom environment
import datetime

if __name__ == '__main__':
    # Create directory for checkpoints if it doesn't exist
    if not os.path.exists("tmp/td3"):
        os.makedirs("tmp/td3")

    # Setup TensorBoard logging
    now = datetime.datetime.now().strftime("%Y-%m-%d_%H-%M-%S")
    experiment_name = f"TD3_Equilibrio_dxdy_{now}"
    writer = SummaryWriter(f"runs/{experiment_name}")

    # Initialize the custom environment
    env = BalanceEnv()
    input_dims = env.observation_space.shape
    n_actions = env.action_space.shape[0]

    # TD3 hyperparameters
    alpha = 0.001                    # Learning rate for the actor
    beta = 0.001                     # Learning rate for the critics
    batch_size = 128                # Number of samples per training step
    tau = 0.005                     # Soft update factor for target networks
    gamma = 0.99                    # Discount factor for future rewards
    warmup = 1000                   # Number of steps before using policy to choose actions
    max_episodes = 10000            # Maximum number of training episodes
    max_steps = 1000                # Maximum number of steps per episode
    update_actor_interval = 2       # Frequency of actor updates (delayed updates)

    # Initialize the TD3 agent
    agent = Agent(alpha=alpha, beta=beta, input_dims=input_dims, tau=tau,
                  env=env, gamma=gamma, update_actor_interval=update_actor_interval,
                  warmup=warmup, n_actions=n_actions,
                  batch_size=batch_size)
    
    # Save hyperparameters to TensorBoard
    writer.add_text("Hyperparameters", 
        f"alpha={alpha}, beta={beta}, tau={tau}, gamma={gamma}, "
        f"warmup={warmup}, batch_size={batch_size}, "
        f"update_actor_interval={update_actor_interval}, "
        f"max_steps={max_steps}"
    )
    
    best_score = -np.inf

    # Main training loop
    for ep in range(max_episodes):
        episode_start_time = time.time()
        obs, info = env.reset()
        done = False
        score = 0
        step_count = 0

        while not done and step_count < max_steps:
            # Select action using the current policy or noise if warming up
            action = agent.choose_action(obs)

            # Apply action to the environment
            next_obs, reward, terminated, truncated, info = env.step(action)
            done = terminated or truncated

            # Store experience in replay buffer
            agent.remember(obs, action, reward, next_obs, done)

            # Perform learning step (update networks)
            agent.learn()

            # Accumulate reward and update state
            score += reward
            obs = next_obs
            step_count += 1

        episode_duration = time.time() - episode_start_time

        # Log metrics to TensorBoard
        writer.add_scalar("Episode Duration", episode_duration, ep)
        writer.add_scalar("Score", score, ep)
        writer.add_scalar("Steps Survived", step_count, ep)
        writer.add_scalar("Avg Reward per Step", score / max(1, step_count), ep)

        print(f"Episode {ep}, Score: {score:.2f}, Steps: {step_count}")

        # Save model every 10 episodes
        if ep % 10 == 0:
            agent.save_models()
