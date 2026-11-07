import pandas as pd
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent   # repo root
RAW = ROOT / "data" / "raw" / "recipes_data.csv"
OUT = ROOT / "data" / "cleaned"

# Small sample for when coding
df = pd.read_csv(RAW, nrows=500)
df.to_json(OUT / "sample_recipes.json", orient="records", indent=4)
print("Created sample_recipes.json, recipes:", len(df))

# 200k for testing and recording
df = pd.read_csv(RAW, nrows=200000)
df.to_json(OUT / "200k.json", orient="records", indent=None)
print("Created 200k.json, recipes:", len(df))