# maze-robot
Arduino code for a maze-solving robot. 

Uses depth-first search to solve a maze. It is iterative (non-recursive) because Arduinos don't have enough stack memory for a recursive dfs.

# useage
Open maze_robot.ino with the arduino IDE to upload to an arduino.

# tests/extras
From the terminal, run `$ make` and `$ ./test`
This will run a simulation of the maze solving and print the progress to the terminal:

![alt text](https://github.com/filipbystricky/maze-robot/blob/master/screenshots/simulation.png)
