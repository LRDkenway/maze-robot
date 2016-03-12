#include "maze.h"
#include "robot.h"
#include "direction.h"

Maze maze;
Robot robot;

void setup() {
    Serial.begin(9600);
    randomSeed(analogRead(0));

    robot.init_pins();


    // maze.generate(0, 0);
    // maze.print_info(NUM_ROWS / 2, NUM_COLS / 2);
    // maze.solve(0, 0, NUM_ROWS / 2, NUM_COLS / 2);
    // maze.print_info(NUM_ROWS / 2, NUM_COLS / 2);

    // robot.move(NORTH);
    // robot.move(WEST);
    // robot.move(EAST);
    // robot.move(NORTH);

}

void loop() {
    // print_out(robot.update_readings());
    // print_out('\n');
    // robot.print_readings();
    // robot.move(NORTH);
    robot.test_move();
}
