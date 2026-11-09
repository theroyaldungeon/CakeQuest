
import { useLocation, useNavigate } from "react-router-dom";

function Recipe() {
    const location = useLocation();
    const navigate = useNavigate();

    const recipe = location.state?.recipe;

    if (!recipe) {
        return (
            <div className="recipe-page">
                <h1>No recipe selected</h1>
                <button onClick={() => navigate("/search")}>
                    Back to Search
                </button>
            </div>
        );
    }

    return (
        <div className="recipe-page">

            <button
                className="recipe-back-button"
                onClick={() => navigate("/search", {
                    state: {
                        searchState: location.state?.searchState
                    }
                })}
            >
                ← Back to Search
            </button>

            <div className="recipe-header">
                <h1>{recipe.title}</h1>

                <p className="recipe-time">
                    Estimated Prep Time: {
                        recipe.prepTime !== undefined &&
                        recipe.prepTime !== null
                            ? `${recipe.prepTime} minutes`
                            : "Time unavailable"
                    }
                </p>
            </div>

            <div className="recipe-information">

                <section className="recipe-ingredients">
                    <h2>Ingredients</h2>

                    <ul>
                        {recipe.ingredients?.map((ingredient, index) => (
                            <li key={index}>{ingredient}</li>
                        ))}
                    </ul>
                </section>

                <section className="recipe-directions">
                    <h2>Directions</h2>

                    <ul>
                        {recipe.directions?.map((direction, index) => (
                            <li key={index}>{direction}</li>
                        ))}
                    </ul>
                </section>

            </div>


        </div>
    );
}

export default Recipe;
