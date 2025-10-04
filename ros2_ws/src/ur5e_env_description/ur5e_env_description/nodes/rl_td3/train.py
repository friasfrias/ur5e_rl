import os
import time
import datetime
import random
import numpy as np
import torch
from torch.utils.tensorboard import SummaryWriter

from env2 import BalanceEnv
from agent import Agent

def set_seed(seed=42):
    random.seed(seed)
    np.random.seed(seed)
    torch.manual_seed(seed)
    torch.cuda.manual_seed_all(seed)
    torch.backends.cudnn.benchmark = True

def evaluate(env: BalanceEnv, agent: Agent, max_steps=5000):
    """ Rollout sem ruído (validation=True) para medir performance. """
    obs, _ = env.reset()
    score, steps = 0.0, 0
    terminated = truncated = False
    with torch.no_grad():
        while not (terminated or truncated) and steps < max_steps:
            action = agent.choose_action(obs, validation=True)
            obs, reward, terminated, truncated, _ = env.step(action)
            score += reward
            steps += 1
    return score, steps

if __name__ == '__main__':
    set_seed(42)

    os.makedirs("tmp/td3", exist_ok=True)

    run_dir = f"runs/TD3/Training_Model/Main"
    writer = SummaryWriter(run_dir)

    # 👉 treinar sem render para reduzir latência/jitter
    env = BalanceEnv(render_window=True)
    input_dims = env.observation_space.shape
    n_actions  = env.action_space.shape[0]

    # Hparams
    alpha, beta, tau = 1e-3, 1e-3, 5e-3
    gamma, batch_size, warmup = 0.99, 256, 1000
    update_actor_interval = 2
    max_episodes, max_steps = 50000, 5000
    eval_every, save_every = 100, 50   # menos checkpoints “ruído”

    agent = Agent(alpha=alpha, beta=beta, input_dims=input_dims, tau=tau,
                  env=env, gamma=gamma, update_actor_interval=update_actor_interval,
                  warmup=warmup, n_actions=n_actions, batch_size=batch_size)

    writer.add_text(
        "Hyperparameters",
        f"alpha={alpha}, beta={beta}, tau={tau}, gamma={gamma}, "
        f"warmup={warmup}, batch_size={batch_size}, "
        f"update_actor_interval={update_actor_interval}, "
        f"max_steps={max_steps}, eval_every={eval_every}"
    )

    best_eval = -np.inf

    try:
        for ep in range(max_episodes):
            obs, _ = env.reset()
            score, step = 0.0, 0
            terminated = truncated = False
            start_time = time.time()

            while not (terminated or truncated) and step < max_steps:
                action = agent.choose_action(obs)  # com ruído
                next_obs, reward, terminated, truncated, _ = env.step(action)

                # trata time-limit como não-terminal no target
                done_no_timeout = bool(terminated and not truncated)
                # se o teu Agent.remember espera (done) único:
                agent.remember(obs, action, reward, next_obs, terminated, truncated)

                # se o teu Agent.remember original exigia (terminated, truncated),
                # troca a linha acima por:
                # agent.remember(obs, action, reward, next_obs, terminated, truncated)

                agent.learn()

                score += reward
                obs = next_obs
                step += 1

            duration = time.time() - start_time

            # Logs
            writer.add_scalar("Train/Episode_Reward", score, ep)
            writer.add_scalar("Train/Steps", step, ep)
            writer.add_scalar("Train/Episode_Time", duration, ep)
            if step > 0:
                writer.add_scalar("Train/Average_Reward", score / step, ep)

            print(f"[TRAIN] Ep {ep:06d} | score {score:.3f} | steps {step} | {duration:.2f}s")

            # Avaliação periódica (sem ruído)
            if (ep + 1) % eval_every == 0:
                eval_score, eval_steps = evaluate(env, agent, max_steps=max_steps)
                writer.add_scalar("Evaluate/Episode_Reward", eval_score, ep)
                writer.add_scalar("Evaluate/Steps", eval_steps, ep)
                print(f"[EVAL]  Ep {ep:06d} | score {eval_score:.3f} | steps {eval_steps}")
                if eval_score > best_eval:
                    best_eval = eval_score
                    agent.save_models()
                    print(f"[CKPT] Novo melhor eval: {best_eval:.3f} — modelos guardados.")

            # Checkpoints regulares
            if (ep + 1) % save_every == 0:
                agent.save_models()

    except KeyboardInterrupt:
        print("\n[TRAIN] Interrompido. A guardar último checkpoint...")
        agent.save_models()
    finally:
        writer.close()
        try:
            env.close()
        except Exception:
            pass
