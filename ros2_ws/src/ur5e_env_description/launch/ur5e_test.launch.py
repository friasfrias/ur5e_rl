from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import ExecuteProcess
import os
import xacro
from ament_index_python.packages import get_package_share_directory

def generate_launch_description():
    pkg = get_package_share_directory("ur5e_env_description")
    urdf = os.path.join(pkg, "urdf", "ur5e.urdf.xacro")
    script_dir = os.path.join(pkg, "nodes")
    controllers_yaml = os.path.join(pkg, "config", "ur5e_controllers.yaml")

    # 1) URDF (sem ros2_control)
    mappings = {
      "name": "ur5e", "ur_type": "ur5e",
      "prefix": "", "force_abs_paths": "false",
      "with_ros2_control": "false"
    }
    robot_desc = xacro.process_file(urdf, mappings=mappings).toxml()
    rsp = Node(
      package="robot_state_publisher",
      executable="robot_state_publisher",
      parameters=[{"robot_description": robot_desc}],
      output="screen"
    )

    # 2) o teu simulador MuJoCo em Python
    main_sim = Node(
      package="ur5e_env_description",
      executable="main",       # o teu main.py
      name="main_simulador",
      output="screen"
    )

    # 3) a tua pipeline de visão
    vision = Node(
      package="ur5e_env_description",
      executable="vision",
      name="visao_pid",
      parameters=[{
        "calib_file": os.path.join(pkg,"config","calib.npz"),
        "nx":5, "ny":21, "square_size":0.007, "width":0.042
      }],
      output="screen"
    )

    # 4) o teu MATLAB PID
    pid_matlab = ExecuteProcess(
      cmd=[os.path.join(script_dir,"pid_control_matlab.sh")],
      output="screen", shell=True
    )

    return LaunchDescription([
      rsp,
      main_sim,
      vision,
      pid_matlab
    ])
