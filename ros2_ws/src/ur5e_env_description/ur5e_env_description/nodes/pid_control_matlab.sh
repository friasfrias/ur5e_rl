#!/usr/bin/env bash

# Vai para a pasta onde está o ficheiro .m, se necessário
cd ~/ros2_ws/src/ur5e_env_description/matlab

# Corre o script .m no MATLAB sem GUI (modo batch)
matlab -batch "pidControlNode.m"
