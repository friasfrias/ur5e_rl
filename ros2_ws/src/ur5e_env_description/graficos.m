import re
import glob
from pathlib import Path
import pandas as pd
import matplotlib.pyplot as plt

# Caminho para a pasta Downloads do teu utilizador
base = Path.home() / "Downloads"
outdir = base / "plots_tensorboard"
outdir.mkdir(exist_ok=True)

# Mapeamento do número no nome do ficheiro para o título do gráfico
num_to_label = {
    4: "Eval, Episode Score",
    5: "Eval, Steps",
    6: "Train, Avg reward",
    7: "Train, Episode Duration",
    8: "Train, Episode Score",
    9: "Train, Steps",
}

# Procurar todos os CSVs que vêm com nome tipo "...(4).csv"
paths = glob.glob(str(base / "TD3_Training_Model_40k*.csv"))

pat = re.compile(r"\((\d+)\)\.csv$")

files = []
for p in paths:
    m = pat.search(p)
    if m:
        n = int(m.group(1))
        if n in num_to_label:
            files.append((n, Path(p)))
files.sort(key=lambda x: x[0])

if not files:
    raise SystemExit("Não encontrei CSVs com (4).csv até (9).csv")

for n, csv_path in files:
    label = num_to_label[n]

    df = pd.read_csv(csv_path)
    x = df.get("Step", df.columns[0])
    y = df.get("Value", df.columns[-1])

    plt.figure(figsize=(7, 5))
    plt.plot(x, y, label=label)
    plt.xlabel("Step")
    plt.ylabel(label)
    plt.title(label)
    plt.grid(True)
    plt.legend()

    fname = label.replace(",", "").replace(" ", "_").lower() + ".png"
    plt.savefig(outdir / fname, dpi=300, bbox_inches="tight")
    plt.close()

print(f"Gráficos guardados em: {outdir.resolve()}")
