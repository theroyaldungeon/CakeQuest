
function RecipeCard({ recipe, onClick }) {
    return (
        <div className="recipe-card">

            <div className="recipe-card-info">
                <h3>{recipe.title}</h3>

                <p>
                    {recipe.ingredients?.length || 0} ingredients
                </p>
            </div>

            <button onClick={() => onClick(recipe)}>
                View Recipe
            </button>

        </div>
    );
}

export default RecipeCard;
