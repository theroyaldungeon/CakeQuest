import { BrowserRouter, Routes, Route } from 'react-router-dom';

import Homepage from './pages/Homepage.jsx'; //first page to load
import Search from './pages/Search.jsx'; //next page after entering the site
import DataComp from './pages/DataComp.jsx'; //where our data structures are compared
import './App.css';

function App() {
    return (
    <BrowserRouter>
        <Routes>
            <Route path="/" element ={<Homepage />} />
            <Route path="/search" element = {<Search />} />
            <Route path ="/comparison" element ={<DataComp />} />
        </Routes>
    </BrowserRouter>
    );
}




export default App;