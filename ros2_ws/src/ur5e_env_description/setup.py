from setuptools import setup, find_packages
import os

package_name = 'ur5e_env_description'

def package_files(directory):
    paths = []
    for (path, _, filenames) in os.walk(directory):
        for filename in filenames:
            filepath = os.path.join(path, filename)
            install_path = os.path.join('share', package_name, path)  # ← mantém subpastas
            paths.append((install_path, [filepath]))
    return paths

model_files = package_files('models')
urdf_files = package_files('urdf')


setup(
    name=package_name,  # mantém underscore aqui
    version='0.0.0',
    packages=find_packages(),
    data_files=[
        ('share/' + package_name + '/launch', ['launch/ur5e_env.launch.py','launch/ur5e_test.launch.py','launch/ur5e_pid.launch.py']),
        ('share/' + package_name + '/config', ['config/ur5e_controllers.yaml','config/calib.npz']),
        ('share/' + package_name, ['package.xml']),
        ('share/' + package_name + '/ur5e_env_description/nodes', ['ur5e_env_description/nodes/pid_control_matlab.sh'])
    ] + model_files + urdf_files,
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='Tomás',
    maintainer_email='tomas@example.com',
    description='Simulação e controlo PID do UR5e com visão',
    license='MIT',
    entry_points={
        'console_scripts': [
            'main = ur5e_env_description.nodes.main_cam:main',
            'vision = ur5e_env_description.nodes.vision:main',
            'test = ur5e_env_description.test_pid:main',
        ],
    },
)
