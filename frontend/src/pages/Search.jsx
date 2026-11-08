
import { useNavigate } from "react-router-dom";
import { useState } from "react";
import RecipeCard from "../components/RecipeCard.jsx";
import Filters from "../components/Filters.jsx";

function Search() {
    const navigate = useNavigate();

    const [ingredientInput, setIngredientInput] = useState("");
    const [recipes, setRecipes] = useState([]);
    const [error, setError] = useState("");
    const [loading, setLoading] = useState(false);

    // Filter settings
    const [filters, setFilters] = useState({
        shortPrepTime: false,
        allIngredients: false
    });

    function openRecipe(recipe) {
        navigate("/recipe", {
            state: { recipe: recipe }
        });
    }

    async function handleSearch() {
        const ingredients = ingredientInput
            .split(",")
            .map(item => item.trim())
            .filter(item => item.length > 0);

        if (ingredients.length === 0) {
            setError("Please enter at least one ingredient.");
            return;
        }

        setLoading(true);
        setError("");
        setRecipes([]);

        try {
            const response = await fetch("http://localhost:3001/api/search", {
                method: "POST",
                headers: {
                    "Content-Type": "application/json"
                },
                body: JSON.stringify({
                ingredients,
                allIngredients: filters.allIngredients
            })
            });

            const data = await response.json();

            if (!response.ok) {
                throw new Error(data.error || "Search failed.");
            }

            setRecipes(data.recipes || []);

        } catch (err) {
            setError(err.message);
        } finally {
            setLoading(false);
        }
    }

    // Apply selected filters to recipes
    const filteredRecipes = recipes.filter(recipe => {
        // Prep time filter
        if (
            filters.shortPrepTime &&
            (recipe.prepTime == null || recipe.prepTime > 30)
        ) {
            return false;
        }

        // Ingredient matching will be handled by the backend.
        // Currently, the backend uses exact ingredient matching.

        return true;
    });

    return (
        <div className="search-page">

            <div className="search-header">
                <h1>CakeQuest</h1>

                <button onClick={() => navigate("/comparison")}>
                    📈
                </button>
            </div>

            <div className="search-welcome">
                <h1>Start your baking quest today!</h1>
                <p>What recipe are you looking for?</p>
            </div>

            <div className="search-bar">
                <input
                    type="text"
                    placeholder="Enter ingredients separated by commas"
                    value={ingredientInput}
                    onChange={(e) => setIngredientInput(e.target.value)}
                    onKeyDown={(e) => {
                        if (e.key === "Enter") handleSearch();
                    }}
                />

                <button onClick={handleSearch} disabled={loading}>
                    {loading ? "Searching..." : "Search"}
                </button>
            </div>

            {error && <p className="error-message">{error}</p>}

            <div className="search-content">

                <div className="pending-results">
                    <h2>Search Results ({filteredRecipes.length})</h2>

                    {loading && <p>Searching for recipes...</p>}

                    {filteredRecipes.length === 0 && !loading && !error && (
                        <p>No recipes found. Try different ingredients or filters.</p>
                    )}

                    {filteredRecipes.map(recipe => (
                        <RecipeCard
                            key={recipe.id}
                            recipe={recipe}
                            onClick={openRecipe}
                        />
                    ))}
                </div>

                <Filters
                    filters={filters}
                    setFilters={setFilters}
                />

            </div>
        </div>
    );
}

export default Search;
