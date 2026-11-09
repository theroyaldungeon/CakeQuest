How to Run the Program

To run CakeQuest, Node.js, npm, CMake 3.20 or newer, a C++17-compatible compiler, and Ninja need to be installed on your computer.

First, clone the project repository from GitHub and navigate to the project directory using the following commands:

git clone https://github.com/theroyaldungeon/CakeQuest

cd CakeQuest

Next, install the required Node.js dependencies by running:

npm.cmd install

Make sure the recipe dataset is available at data/cleaned/200k.json. To obtain the dataset, download it from https://www.kaggle.com/datasets/wilmerarltstrmberg/recipe-dataset-over-2. Then, run clean_data.py from its location in the repository to generate the required 200k.json file.

Configure the C++ project using the following command:

cmake -S . -B build

Compile the C++ backend by running:

cmake --build build --target CakeQuest

Once the C++ backend has been compiled, start the Node.js backend server from the CakeQuest project directory using:

node server/server.js

The backend server runs on port 3001 and communicates with the C++ executable.

Next, open a second terminal in the CakeQuest project directory and start the frontend using:

npm.cmd run dev

Once the Vite development server has started, open the following URL in your web browser to access CakeQuest:

http://localhost:5173/

Both terminal sessions must remain running while using the application. The Node.js backend operates on port 3001, while the frontend operates on port 5173.

With the default Ninja configuration, the executable is generated at build/CakeQuest.exe. The executable path configured in server/server.js should match this location.