import os
import gym
import time
import mujoco
import numpy as np
from torch.utils.tensorboard import SummaryWritter
import robosuite as suite
from robosuite.wrappers import GymWrapper

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
        render_camera = "frontview",
        has_offscreen_renderer=True,
        reward_shaping = True,
        control_frq = 20,
    )

    env = GymWrapper(env)
