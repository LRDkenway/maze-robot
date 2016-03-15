#include "maze.h"
#include "robot.h"
#include "direction.h"

Maze maze;
Robot robot;

void setup() {
    Serial.begin(9600);
    randomSeed(analogRead(0));

    robot.init_pins();

}

void loop() {
    robot.test_move();
}
