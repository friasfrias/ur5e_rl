import re
import glob
from pathlib import Path
import pandas as pd
import matplotlib.pyplot as plt

base = Path.home() / "Downloads"
outdir = base / "plots_tensorboard"
outdir.mkdir(exist_ok=True)

num_to_label = {
    0: "Eval, Episode Reward",
    1: "Eval, Steps",
    2: "Train, Average Reward",
    3: "Train, Episode Time",
    4: "Train, Episode Reward",
    5: "Train, Steps",
}

paths = glob.glob(str(base / "TD3_Training_Model_Main*.csv"))

pat_num = re.compile(r"\((\d+)\)\.csv$")

files = []
for p in paths:
    p = Path(p)
    m = pat_num.search(p.name)
    if m:
        n = int(m.group(1))              # ...Main(1).csv → 1, etc.
    else:
        n = 0                            # ...Main.csv (sem parênteses) → 0
    if n in num_to_label:
        files.append((n, p))

files.sort(key=lambda x: x[0])

if not files:
    raise SystemExit("Não encontrei CSVs com nomes esperados (Main.csv até Main(5).csv).")

for n, csv_path in files:
    label = num_to_label[n]
    df = pd.read_csv(csv_path)

    # escolhe colunas com fallback correto (Series, não strings)
    x = df["Step"] if "Step" in df.columns else df.iloc[:, 0]
    y = df["Value"] if "Value" in df.columns else df.iloc[:, -1]

    # garante numérico e remove NaNs silenciosamente
    x = pd.to_numeric(x, errors="coerce")
    y = pd.to_numeric(y, errors="coerce")
    mask = x.notna() & y.notna()

    plt.figure(figsize=(7, 5))
    plt.plot(x[mask], y[mask], label=label)
    plt.xlabel("Step")
    plt.ylabel(label)
    plt.title(label)
    plt.grid(True)
    plt.legend()

    fname = label.replace(",", "").replace(" ", "_").lower() + ".png"
    plt.savefig(outdir / fname, dpi=300, bbox_inches="tight")
    plt.close()

print(f"Gráficos guardados em: {outdir.resolve()}")
