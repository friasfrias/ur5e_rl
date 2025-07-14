from launch import LaunchDescription
from launch_ros.actions import Node
import os
from ament_index_python.packages import get_package_share_directory
import xacro


def generate_launch_description():
    pkg_path = get_package_share_directory("ur5e_env_description")
    mjcf_path = os.path.join(pkg_path, "models", "ur5e_env.xml")
    urdf_path = os.path.join(pkg_path, "urdf", "ur5e.urdf.xacro")
    script_dir = os.path.join(pkg_path, "ur5e_env_description", "nodes")
    controllers_yaml = os.path.join(pkg_path, "config", "ur5e_controllers.yaml")

    # Processar o XACRO → URDF
    base_mappings = {
        "name": "ur5e",
        "ur_type": "ur5e",
        "prefix": "",
        "force_abs_paths": "false"
    }
    
    mappings1 = { **base_mappings, "with_ros2_control": "false" }
    robot_desc1 = xacro.process_file(urdf_path, mappings=mappings1).toxml()
    rsp = Node(
        package="robot_state_publisher",
        executable="robot_state_publisher",
        parameters=[{"robot_description": robot_desc1}],
        output="screen"
    )

    # 2) mujoco_ros2_control: com o bloco <ros2_control>
    mappings2 = { **base_mappings, "with_ros2_control": "true", "safety_limits":"true", "safety_pos_margin":"0.15" }
    robot_desc2 = xacro.process_file(urdf_path, mappings=mappings2).toxml()
    mujoco = Node(
        package="mujoco_ros2_control",
        executable="mujoco_ros2_control",
        parameters=[
            controllers_yaml,
            {"mujoco_model_path": mjcf_path, "gui": True},
            {"robot_description": robot_desc2},
        ],
        output="screen"
    )

    from launch.actions import ExecuteProcess

    spawner_jsb = ExecuteProcess(
    cmd=[
      "ros2", "run", "controller_manager", "spawner",
      "joint_state_broadcaster",
      "--controller-manager", "/controller_manager",
      "--param-file", controllers_yaml
    ],
    output="screen",
    )

    spawner_arm = ExecuteProcess(
    cmd=[
      "ros2", "run", "controller_manager", "spawner",
      "ur5e_controller",
      "--controller-manager", "/controller_manager",
      "--param-file", controllers_yaml
    ],
    output="screen",
    )
    
    # pid_matlab = ExecuteProcess(
    #     cmd=[os.path.join(script_dir, "pid_control_matlab.sh")],
    #     output="screen",
    #     shell=True
    # )

    main_node = Node(
        package="ur5e_env_description",
        executable="main",
        name="main_simulador",
        output="screen"
    )

    vision_node = Node(
        package="ur5e_env_description",
        executable="vision",
        name="visao_pid",
        output="screen",
        parameters=[
           {"calib_file": os.path.join(pkg_path, "config", "calib.npz")}]

    )

    return LaunchDescription([rsp, mujoco, spawner_jsb, spawner_arm, main_node, vision_node])
