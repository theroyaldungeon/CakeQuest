import json
import sys
from pathlib import Path

import pandas as pd

ROOT = Path(__file__).resolve().parent.parent   # repo root
RAW = ROOT / "data" / "raw" / "recipes_data.csv"
OUT = ROOT / "data" / "cleaned" / "ner_200k.json"

n = int(sys.argv[1]) if len(sys.argv) > 1 else 200000

df = pd.read_csv(RAW, usecols=["NER"], nrows=n)

lists = []
for value in df["NER"]:
    # NER is stored as a JSON array inside a string, e.g. '["milk", "sugar"]'
    lists.append(json.loads(value) if isinstance(value, str) else [])

OUT.parent.mkdir(parents=True, exist_ok=True)
with open(OUT, "w", encoding="utf-8") as f:
    json.dump(lists, f, separators=(",", ":"))   # compact

print("Created", OUT.name, "with", len(lists), "recipes")