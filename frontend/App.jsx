import { BrowserRouter, Routes, Route } from 'react-router-dom';

import Homepage from './src/pages/Homepage.jsx'; //first page to load
import Search from './src/pages/Search.jsx'; //next page after entering the site
import DataComp from './src/pages/DataComp.jsx'; //where our data structures are compared
import Recipe from './src/pages/Recipe.jsx';

import './App.css';

function App() {
    return (
    <BrowserRouter>
        <Routes>
            <Route path="/" element ={<Homepage />} />
            <Route path="/search" element = {<Search />} />
            <Route path ="/comparison" element ={<DataComp />} />
            <Route path="/recipe" element={<Recipe />} />
        </Routes>
    </BrowserRouter>
    );
}




export default App;