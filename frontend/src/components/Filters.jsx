
function Filters({
    filters,
    setFilters,
    searchMethod,
    setSearchMethod
}) {

    // Update filter settings
    function handleFilterChange(filterName) {
        setFilters(prev => ({
            ...prev,
            [filterName]: !prev[filterName]
        }));
    }

    return (
        <div className="filters">

            <h2>Filters</h2>

            <h3>Search Method</h3>

            <div className="search-method-buttons">

                <button
                    className={searchMethod === "btree" ? "active" : ""}
                    onClick={() => setSearchMethod("btree")}
                >
                    B-Tree
                </button>

                <button
                    className={searchMethod === "hash" ? "active" : ""}
                    onClick={() => setSearchMethod("hash")}
                >
                    Hash Table
                </button>

            </div>

            <h3>Prep Time</h3>

            <label>
                <input
                    type="checkbox"
                    checked={filters.shortPrepTime}
                    onChange={() => handleFilterChange("shortPrepTime")}
                />
                30 minutes or less
            </label>

            <h3>Ingredients</h3>

            <label>
                <input
                    type="checkbox"
                    checked={filters.allIngredients}
                    onChange={() => handleFilterChange("allIngredients")}
                />
                All ingredients available
            </label>

        </div>
    );
}

export default Filters;
