#!/usr/bin/env python3
import sys
import mujoco
from mujoco import viewer

def main():
    if len(sys.argv) != 2:
        print(f"Uso: {sys.argv[0]} ros2_ws/src/ur5e_env_description/models/ur5e_env.xml")
        sys.exit(1)
    xml_path = sys.argv[1]
    # Carrega o modelo e os dados de simulação
    model = mujoco.MjModel.from_xml_path(xml_path)
    data  = mujoco.MjData(model)
    # Abre o viewer interativo
    viewer.launch(model, data)

if __name__ == "__main__":
    main()
