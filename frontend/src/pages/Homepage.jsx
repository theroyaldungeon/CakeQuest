import {useNavigate} from 'react-router-dom';

function Homepage() {

    const navigate = useNavigate();
    return (
        <div className="homepage">
            <div className="homepage-content">
                <h1> Welcome to CakeQuest!</h1>
                
                <p> Go on a baking adventure with your pantry ingredients</p>
            
                <h2> What to expect</h2>

            <div className="homepage-middle">

                <ul>
                    <li>Have a Smooth Journey Finding the Right Recipe</li>
                    <li> Use a simplistic filtering system</li>
                    <li>Results in seconds!</li>
                </ul>

                <div className="homepage-image">
                    🍰
                </div>
            </div>

            <button onClick={() => navigate('/search')}>
                Enter the Site
            </button>
            </div>
        </div>
    );
}

export default Homepage;