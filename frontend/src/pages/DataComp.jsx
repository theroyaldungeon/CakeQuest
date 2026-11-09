
import { useState } from 'react';
import { useNavigate } from 'react-router-dom';
import buildTimeChart from '../assets/charts/build_time.png';
import lookupTimeChart from '../assets/charts/lookup_time.png';
import memoryUsageChart from '../assets/charts/memory_usage.png';

function DataComp() {

    const navigate = useNavigate();

    // Tracks which comparison page is currently displayed
    const [currentPage, setCurrentPage] = useState(0);

    // Titles for each page
    const pageTitles = [
        "Hash-Based Inverted Index",
        "B-Tree Index",
        "Min Heap",
        "Efficiency Comparison"
    ];

    return (
        <div className="comparison-page">

            {/* HEADER */}
            <div className="comparison-header">

                <h1>CakeQuest</h1>

                <button onClick={() => navigate('/search')}>
                    ← Search
                </button>

            </div>


            {/* MAIN TITLE */}
            <div className="comparison-title">


                <p>
                    Data structures for recipe searches.
                </p>

            </div>


            {/* PAGE CONTENT */}
            <div className="comparison-content">

                <h2>{pageTitles[currentPage]}</h2>


                {/*Hash page info */}
                {currentPage === 0 && (

                    <div className="structure-description">

                        <div className="algorithm-visual">
                            Hash Index Diagram
                        </div>

                        <p>
                            blah blah information.
                        </p>

                        <p>
                            blah blah more infor.
                        </p>

                        <p>
                            blah blah evenn more cool info.
                        </p>

                    </div>

                )}


                {/* B tree Page */}
                {currentPage === 1 && (

                    <div className="structure-description">

                        <div className="algorithm-visual">
                            B-Tree Diagram
                        </div>

                        <p>
                            blah blah information
                        </p>

                        <p>
                            blah blah even more info
                        </p>

                        <p>
                            blah blah last info
                        </p>

                    </div>

                )}


                {/* min heap*/}
                {currentPage === 2 && (

                    <div className="structure-description">

                        <div className="algorithm-visual">
                            Min Heap Diagram
                        </div>

                        <p>
                            blah blah k largest elements
                        </p>

                        <p>
                           blah blah more info
                        </p>

                    </div>

                )}


                {/* efficicency */}
                {currentPage === 3 && (

                    <div className="efficiency-view">

                        <h3>Performance Comparison</h3>

                        <div className="efficiency-placeholder">

                            <h3>Build Time</h3>


                            <img
                                className="efficiency-chart"
                                src={buildTimeChart}
                                alt="Build time of the B-tree and hash index"
                            />

                        </div>

                        <div className="efficiency-placeholder">

                            <h3>Lookup Time</h3>

                            <img
                                className="efficiency chart"
                                src={lookupTimeChart}
                                alt = "Lookup time of B-tree and hash index"
                            />


                        </div>

                        <div className="efficiency-placeholder">

                            <h3>Memory Usage</h3>

                            <img
                                className="efficiency-chart"
                                src={memoryUsageChart}
                                alt="Memory usage of the B-tree and hash index"
                            />

                        </div>

                    </div>

                )}

            </div>


            {/* PREVIOUS AND NEXT BUTTONS */}
            <div className="comparison-navigation">

                <button
                    onClick={() => setCurrentPage(currentPage - 1)}
                    disabled={currentPage === 0}
                >
                    ← Previous
                </button>

                <p>
                    Page {currentPage + 1} of {pageTitles.length}
                </p>

                <button
                    onClick={() => setCurrentPage(currentPage + 1)}
                    disabled={currentPage === pageTitles.length - 1}
                >
                    Next →
                </button>

            </div>

        </div>
    );
}

export default DataComp;
