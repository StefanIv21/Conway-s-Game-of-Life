# Conway's Game of Life
This C++ program, named "Game_of_life," is an implementation of Conway's Game of Life using the OpenGL and GLUT libraries. Conway's Game of Life is a cellular automaton that simulates the evolution of cells on a grid based on a set of simple rules. Here's a brief description of the key components and functionality of the program for your GitHub repository:

## Game of Life Logic:
  - The program simulates a grid of cells, where each cell can be either alive or dead.
  - It uses a double-buffered approach, maintaining two matrices (gameMatrix and tempMatrix) to calculate the next generation of cells without modifying the current generation.

## Game State Management:
 - The program has different game states: STARTING, GAME_CHOOSE, PROPAGATING, and LAST.
  - It starts in the STARTING state, where you can choose to start the simulation or quit.
 - In the GAME_CHOOSE state, you can draw live cells on the grid.
  - In the PROPAGATING state, the simulation evolves according to the Game of Life rules.
   - The LAST state is reached when the simulation ends, and it displays a message and an option to restart.

## User Interaction:
- Users can interact with the program using the keyboard and mouse:
- Press 'i' to advance the simulation by 10 generations.
 - Press 'Enter' to advance the simulation by one generation.
- Press 'Esc' to exit the program.
- In the GAME_CHOOSE state, you can click on grid cells to make them alive.
- In the LAST state, you can click the "RESTART" button to return to the STARTING state.

## Graphics and Visualization:
   - The program uses OpenGL and GLUT to create a graphical user interface.
   - It draws the grid, live cells, and various text messages on the screen.
   -  Colors and fonts are used to enhance the visual appeal.

## Main Function:
 - The main function initializes GLUT, sets up the window, and enters the main event loop.
- It also sets up callback functions for keyboard and mouse input.

## Compilation

- In case you dont have glut installed previously

        sudo apt-get install freeglut3-dev
- then

       g++ Game.cpp -lGL -lGLU -lglut

