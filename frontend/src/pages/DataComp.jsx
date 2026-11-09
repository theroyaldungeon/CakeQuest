import { useNavigate } from 'react-router-dom';
import buildTimeChart from '../assets/charts/build_time.png';
import lookupTimeChart from '../assets/charts/lookup_time.png';
import memoryUsageChart from '../assets/charts/memory_usage.png';

function DataComp() {

    const navigate = useNavigate();

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

                <h2>Efficiency Comparison</h2>

                {/* efficicency */}
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
                            className="efficiency-chart"
                            src={lookupTimeChart}
                            alt="Lookup time of the B-tree and hash index"
                            style={{ width: '100%', maxWidth: '400px', display: 'block', margin: '15px auto 0' }}
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

            </div>

        </div>
    );
}

export default DataComp;