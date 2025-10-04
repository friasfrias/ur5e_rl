import os
import time
from datetime import datetime
import torch
from torch.utils.tensorboard import SummaryWriter
from env import BalanceEnv
from agent import DQNAgent

episodes = 20000
max_episode_steps = 10000
hidden_layer = 128
learning_rate = 0.0001
gamma = 0.99
batch_size = 64
epsilon_start = 1
epsilon_end = 0.1
epsilon_decay = 0.995
warmup = 5000
buffer_capacity = 100000
tau = 0.005


# Criação do ambiente
env = BalanceEnv()

agent = DQNAgent(env, n_observations=env.observation_space.shape[0], n_actions=env.action_space.n, hidden_layer=hidden_layer,
              lr=learning_rate, warmup=warmup, buffer_capacity= buffer_capacity, batch_size=batch_size, epsilon_start=epsilon_start,
              epsilon_end=epsilon_end, gamma=gamma, tau=tau)

agent.test()

env.close()