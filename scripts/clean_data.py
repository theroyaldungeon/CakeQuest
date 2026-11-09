import pandas as pd

<<<<<<< HEAD
df = pd.read_csv("C:/Users/maldo/CLionProjects/BakingBad/data/raw/recipes_data.csv")
=======
df = pd.read_csv("data/raw/recipes_data.csv")
>>>>>>> temp-Connection-of-Front-end-to-backened,-still-minor-filtering-errors

# sample = df.head(500)
# sample.to_json ("C:/Users/maldo/CLionProjects/BakingBad/data/cleaned/sample_recipes.json", orient = "records", indent=4)

# print("Created sample_recipes.json")
# print("Recipes:", len(sample))

sample = df.head(200000)
<<<<<<< HEAD
sample.to_json ("C:/Users/maldo/CLionProjects/BakingBad/data/cleaned/200k.json", orient = "records", indent=4)
=======
sample.to_json ("data/cleaned/200k.json", orient = "records", indent=4)
>>>>>>> temp-Connection-of-Front-end-to-backened,-still-minor-filtering-errors

print("Created 200k.json")
print("Recipes:", len(sample))