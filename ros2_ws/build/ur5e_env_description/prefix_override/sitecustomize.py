import sys
if sys.prefix == '/usr':
    sys.real_prefix = sys.prefix
    sys.prefix = sys.exec_prefix = '/home/tomas/ur5e_rl/ros2_ws/install/ur5e_env_description'
