import os
import time
import numpy as np
from agent import Agent
from env2 import BalanceEnv
from torch.utils.tensorboard import SummaryWriter
import datetime

if __name__ == "__main__":
    # === TensorBoard writer ===
    now = datetime.datetime.now().strftime("%Y-%m-%d_%H-%M-%S")
    experiment_name = f"TD3_Test_{now}"
    writer = SummaryWriter(f"runs/{experiment_name}")

    # === Initialize environment ===
    env = BalanceEnv()
    input_dims = env.observation_space.shape
    n_actions = env.action_space.shape[0]

    # === Load TD3 agent ===
    agent = Agent(alpha=0.001, beta=0.001, input_dims=input_dims, tau=0.005,
                  env=env, gamma=0.99, update_actor_interval=2,
                  warmup=0, n_actions=n_actions, batch_size=128)

    # Load latest checkpoint (no "best" model is used)
    agent.load_models()

    # === Evaluation parameters ===
    n_eval_episodes = 20
    max_steps = 5000
    rms_windows = [1, 2, 5, 10, 20, 50]   # janelas em segundos

    def rms_until(values, times, limit):
        vals = [v for v, t in zip(values, times) if t < limit]
        if not vals:
            return np.nan
        return float(np.sqrt(np.mean(np.square(vals))))

    for ep in range(n_eval_episodes):
        obs, _ = env.reset()
        done = False
        score = 0.0
        step_count = 0
        start_time = time.time()

        # logs para RMS
        alpha_log, beta_log, t_log = [], [], []

        while not done and step_count < max_steps:
            # Ação determinística, igual ao treino (sem ruído)
            action = agent.choose_action(obs, validation=True)
            obs, reward, terminated, truncated, info = env.step(action)
            done = terminated or truncated

            score += reward
            step_count += 1

            # === Ângulos em GRAUS a partir do obs normalizado (±1 -> ±90°) ===
            try:
                alpha_deg = float(obs[0]) * env.obs_clip_deg
                beta_deg  = float(obs[1]) * env.obs_clip_deg
                alpha_log.append(alpha_deg)
                beta_log.append(beta_deg)
                t_log.append(time.time() - start_time)
            except Exception:
                # ignora se obs vier corrompido por algum motivo raro
                pass

        duration = time.time() - start_time

        # === Log evaluation metrics to TensorBoard ===
        writer.add_scalar("Test/Score", score, ep)
        writer.add_scalar("Test/Steps Survived", step_count, ep)
        writer.add_scalar("Test/Episode Duration", duration, ep)
        writer.add_scalar("Test/Avg Reward per Step", score / max(1, step_count), ep)

        # === RMS dos ângulos ===
        if alpha_log:
            rms_alpha = [rms_until(alpha_log, t_log, w) for w in rms_windows]
            rms_beta  = [rms_until(beta_log,  t_log, w) for w in rms_windows]
        else:
            rms_alpha = [np.nan] * len(rms_windows)
            rms_beta  = [np.nan] * len(rms_windows)

        print(f"[Test] Ep {ep+1}: Score={score:.2f}, Steps={step_count}, Duration={duration:.2f}s")
        fmt = lambda arr: "   ".join("nan" if not np.isfinite(x) else f"{x:.3f}" for x in arr)
        print(f"RMS alpha (deg):    {fmt(rms_alpha)}")
        print(f"RMS beta  (deg):    {fmt(rms_beta)}\n")

    writer.close()
