import os
import time
import numpy as np
from agent import Agent
from env import BalanceEnv
from torch.utils.tensorboard import SummaryWriter
import datetime

if __name__ == "__main__":
    # === TensorBoard writer ===
    now = datetime.datetime.now().strftime("%Y-%m-%d_%H-%M-%S")
    experiment_name = f"TD3_Test_{now}"
    writer = SummaryWriter(f"runs/{experiment_name}")

    # === Initialize environment ===
    env = BalanceEnv()
    input_dims = env.observation_space.shape
    n_actions = env.action_space.shape[0]

    # === Load TD3 agent ===
    agent = Agent(alpha=0.001, beta=0.001, input_dims=input_dims, tau=0.005,
                  env=env, gamma=0.99, update_actor_interval=2,
                  warmup=0, n_actions=n_actions, batch_size=128)

    # Load latest checkpoint (no "best" model is used)
    agent.load_models()

    # === Evaluation parameters ===
    n_eval_episodes = 20
    max_steps = 1000

    for ep in range(n_eval_episodes):
        obs, info = env.reset()
        done = False
        score = 0
        step_count = 0
        start_time = time.time()

        while not done and step_count < max_steps:
            # Use deterministic action from the actor (no noise)
            action = agent.actor.forward(agent.to_tensor(obs)).cpu().detach().numpy()
            obs, reward, terminated, truncated, info = env.step(action)
            done = terminated or truncated

            score += reward
            step_count += 1

        duration = time.time() - start_time

        # === Log evaluation metrics to TensorBoard ===
        writer.add_scalar("Test/Score", score, ep)
        writer.add_scalar("Test/Steps Survived", step_count, ep)
        writer.add_scalar("Test/Episode Duration", duration, ep)
        writer.add_scalar("Test/Avg Reward per Step", score / max(1, step_count), ep)

        print(f"[Test] Ep {ep}: Score={score:.2f}, Steps={step_count}, Duration={duration:.2f}s")
    
    writer.close()
