
function Filters({ filters, setFilters }) {
    return (
        <div className="filters">
            <h2>Filters</h2>

            <h3>Prep time</h3>

            <label>
                <input
                    type="checkbox"
                    checked={filters.shortPrepTime}
                    onChange={(e) =>
                        setFilters({
                            ...filters,
                            shortPrepTime: e.target.checked
                        })
                    }
                />
                Shortest to Longest Prep Time
            </label>

            <h3>Ingredients</h3>

            <label>
                <input
                    type="checkbox"
                    checked={filters.allIngredients}
                    onChange={(e) =>
                        setFilters({
                            ...filters,
                            allIngredients: e.target.checked
                        })
                    }
                />
                Matched all ingredients 
            </label>
        </div>
    );
}

export default Filters;
