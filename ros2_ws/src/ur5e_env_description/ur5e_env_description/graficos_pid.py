import matplotlib.pyplot as plt
import numpy as np

# ---- Dados manuais ----
tempos = [44.92, 43.69, 40.07, 42.30, 43.44]         # Tempo de equilíbrio (s)
returns = [64.6424, 60.0168, 69.1636, 66.8042, 63.4902]  # Sum r_t
avg_r_step = [0.2245, 0.1924, 0.2353, 0.2162, 0.2022]    # Média da reward por step

episodios = np.arange(1, 6)

# ---- 1) Tempo de equilíbrio ----
plt.figure()
plt.plot(episodios, tempos, marker='o', color='tab:blue', linewidth=2)
plt.ylim(0, 60)
plt.xticks(episodios)   # apenas 1,2,3,4,5
plt.grid(True)
plt.xlabel("Episode")
plt.ylabel("Time [s]")
plt.title("PID - Episode Duration")

# ---- 2) Episodic return ----
plt.figure()
plt.plot(episodios, returns, marker='o', color='tab:green', linewidth=2)
plt.ylim(0, 100)
plt.xticks(episodios)
plt.grid(True)
plt.xlabel("Episode")
plt.ylabel("Reward")
plt.title("PID - Acumulative Reward")

# ---- 3) Avg reward/step ----
plt.figure()
plt.plot(episodios, avg_r_step, marker='o', color='tab:red', linewidth=2)
plt.ylim(0, 0.3)
plt.xticks(episodios)
plt.grid(True)
plt.xlabel("Episode")
plt.ylabel("Average Reward")
plt.title("PID - Average Reward / Step")

plt.show()
