import { useNavigate } from "react-router-dom";

function Search() {

    const navigate = useNavigate();

    return (
        <div className="search-page">
            <div className="search-header">
                <h1>CakeQuest</h1>

                <button onClick={() => navigate('/comparison')}>
                    📈
                </button>
            </div>

        <div className="search-welcome">
            <h1>Start your baking quest today!</h1>
            <p> What recipe are you looking for? </p>
        </div>

        <div className="search-bar">
            <input
                type="text"
                placeholder="Enter your ingredients here"
            />
            <button>Search</button>
        </div>

        <div className="search-content">
            <div className="pending-results">
                <h2>Pending Recipes</h2>
                <p>Strawberry Shortcake</p>
            </div>

            <div className="filters">
                <h2>Filters</h2>

                <h3> Prep time</h3>
                <p> 30 minutes or less</p>

                <h3> Ingredients</h3>
                <p>All ingredients available</p>
            </div>
        </div>
    </div>

    );
}

export default Search;