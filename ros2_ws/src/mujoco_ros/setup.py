from setuptools import setup
from glob import glob
import os

package_name = 'mujoco_ros'

asset_files = []
for (dirpath, _, filenames) in os.walk('assets'):
    for f in filenames:
        # preserva a estrutura de pastas após 'assets/'
        rel_dir = os.path.relpath(dirpath, 'assets')
        rel_file = os.path.join(rel_dir, f) if rel_dir != '.' else f
        asset_files.append((os.path.join('share', package_name, 'assets', rel_dir), 
                            [os.path.join(dirpath, f)]))

setup(
    name=package_name,
    version='0.1.0',
    packages=[package_name],
    data_files=[
        ('share/ament_index/resource_index/packages', ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
        # adiciona cada ficheiro mantendo hierarquia
        *asset_files,
    ],
    
    install_requires=[
        'setuptools',
        'mujoco',  # ou 'mujoco' se estiveres a usar a API oficial
        'glfw',
        'numpy',
        'opencv-python',
    ],
    zip_safe=True,
    maintainer='Tomás Ferreira',
    maintainer_email='tf@uc.pt',
    description='Bridge between ROS 2 and MuJoCo environment with RealSense overlay',
    license='Apache-2.0',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'mujoco_rl = mujoco_ros.mujoco_rl:main',
            'wind_cam = mujoco_ros.wind_cam:main',
            'home_position = mujoco_ros.home_position:main',
        ],
    },
)

