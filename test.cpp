#ifdef TEST

#include <stdlib.h>
#include "maze.h"
#include "robot.h"
#include "direction.h"

Maze test_maze;
Robot robot;

int main() {
	srand(time(NULL));

	test_maze.generate(1, 1);
	test_maze.solve(0, 0, NUM_ROWS / 2, NUM_COLS / 2);
	test_maze.print_info(NUM_ROWS / 2, NUM_COLS / 2);
}

#endif /* TEST */
