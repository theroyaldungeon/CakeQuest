import pandas as pd

df = pd.read_csv("C:/Users/maldo/CLionProjects/BakingBad/data/raw/recipes_data.csv")

sample = df.head(500)
sample.to_json (
    "C:/Users/maldo/CLionProjects/BakingBad/data/cleaned/sample_recipes.json", orient = "records", indent=4
)

print("Created sample_recipes.json")
print("Recipes:", len(sample))