import os
import gym
import time
import mujoco
import numpy as np
from torch.utils.tensorboard import SummaryWritter
import robosuite as suite
from robosuite.wrappers import GymWrapper
from networks import CriticNetwork, ActorNetwork
from buffer import ReplayBuffer
from td3_torch import Agent

if __name__ == "__main__":

    if not os.path.exists("tmp/td3"):
        os.makedir("tmp/td3")

    env_name = "Door"

    env = suite.make(
        env_name,
        robots=["Panda"],
        controllerconfig=...,
        has_renderer = False,
        use_camera_obs = False,
        horizon = 300,
        reward_shaping = True,
        control_frq = 20,
    )

    env = GymWrapper(env)

    actor_learing_rate = 0.001
    critic_learning_rate = 0.001
    batch_size = 128
    layer1_size = 256
    layer2_size = 128
      
    agent = Agent(actor_learning_rate=actor_learing_rate, critic_learning_rate=critic_learning_rate, tau=0.005, input_dims=env.observation_space.shape,
                  env=env, n_actions=env.action_space.shape[0], layer1_size=layer1_size, layer2_size=layer2_size, batch_size=batch_size)
    
    writter= SummaryWritter('logs')
    n_games = 10000
    best_score = 0

    episode_identifier = f"0 - actor_learning_rate={actor_learing_rate} critic_learning_rate={critic_learning_rate} layer1_size={layer1_size} layer2_size={layer2_size}"

    agent.load_models()

    for i in range(n_games):
        observation = env.reset()
        done = False
        score = 0

        while not done:

            action =  agent.choose_action(observation)
            next_observation, reward, done, info = env.step()
            score += reward
            agent.remember(observation, action, reward, next_observation, done)
            agent.learn()
            observation = next_observation

        writter.add_scalar(f"Score - {episode_identifier}", score, global_step=i)

        if (i%10): 
            agent.save_models()

        print(f"Episode: {i} Score: {score}")
