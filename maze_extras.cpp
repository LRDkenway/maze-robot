#include "maze.h"
#include "robot.h"

/*
 * Given an array of the four directions, randomizes the order of the directions
 *
 * Parameters:
 *	- directions: an array of Direction enums of size 4
 *
 * Returns:
 *	- nothing - the array should be shuffled in place
 */
static void shuffle_array(Direction directions[]) {
	int i, r, temp;
	for (i = 0; i < 4; i++) {
		//random number from i to 3, inclusive
		r = random(i, 4);
		//swap
		temp = directions[i];
		directions[i] = directions[r];
		directions[r] = temp;
	}
}

int Maze::get_rand_neighbor(uint8_t *room_i) {
	static Direction directions[4] = {0, 1, 2, 3};

	uint8_t room_row = *room_i / NUM_COLS,
	        room_col = *room_i % NUM_COLS;

	shuffle_array(directions);

	for (uint8_t i = 0; i < 4; i++) {
		Direction dir = directions[i];
		uint8_t next_row = room_row + Y_INCR[dir],
		        next_col = room_col + X_INCR[dir],
		        neighbor_i = get_index(next_row, next_col);

		if (is_in_range(next_row, next_col) && !rooms[neighbor_i].is_visited()) {

			rooms[*room_i].mark_open(dir);
			rooms[neighbor_i].mark_open(Directions::opposite(dir));

			*room_i = neighbor_i;
			return 1;
		}
	}
	return 0;
}

void Maze::drunken_walk(uint8_t room_i) {

	uint8_t path[NUM_ROWS * NUM_COLS];
	uint8_t last = 0;

	clear_visited();

	while (1) {
		rooms[room_i].mark_visited();

		path[last++] = room_i; //push the current room onto the path

		if (last == (NUM_ROWS * NUM_COLS) - 1) {
			print_out("OUT OF BOUNDS IN DRUNKEN WALK!!!\n");
			return;
		}

		//backtrack until there are unvisited neighbors
		while (!get_rand_neighbor(&room_i)) {
			if (last > 0) {
				room_i = path[--last]; //backtrack
			} else {
				//can't backtrack anymore, so done
				clear_visited();
				return;
			}
		}
	}
}

void Maze::print(uint8_t robot_i, uint8_t goal_room_i) {
	static const char arrows[] = {'^', '>', 'v', '<'};
	print_out('\n');
	//top
	for (uint8_t i = 0; i < NUM_COLS; i++) {
		print_out(rooms[get_index(0, i)].is_open(Directions::NORTH) ? ".   " : ".___");
	}
	print_out(".\n");

	for (uint8_t j = 0; j < NUM_ROWS; j++) {
		//middle and bottom

		for (uint8_t i = 0; i < NUM_COLS; i++) {
			uint8_t room = get_index(j, i);

			print_out(rooms[room].is_open(Directions::WEST) ? "  " : "| ");

			if (room == goal_room_i) {
				print_out('x');
			} else if (room == robot_i) {
				print_out('o');
			} else if (rooms[room].is_solution()) {
				print_out(arrows[rooms[room].get_next()]);
			} else if (rooms[room].is_visited()) {
				print_out('.');
			} else {
				print_out(' ');
			}
			print_out(' ');

			if (i == NUM_COLS - 1 && !rooms[room].is_open(Directions::EAST)) {
				print_out('|');
			}
		}
		print_out('\n');

		for (uint8_t i = 0; i < NUM_COLS; i++) {
			uint8_t room = get_index(j, i);

			print_out(rooms[room].is_open(Directions::WEST) ? '.' : '|');
			print_out(rooms[room].is_open(Directions::SOUTH) ? "   " : "___");

			if (i == NUM_COLS - 1 && !rooms[room].is_open(Directions::EAST)) {
				print_out('|');
			}
		}
		print_out('\n');
	}
}

void Maze::print_info(uint8_t goal_row, uint8_t goal_col) {
	print(0, get_index(goal_row, goal_col));
	print_out("maze size: ");
	print_out(sizeof(Maze));
	print_out("\nstack size: ");
	print_out(sizeof(uint32_t) * STACK_SIZE);

	print_out("\nrobot size: ");
	print_out(sizeof(Robot));

	print_out("\nroom size: ");
	print_out(sizeof(Room));

	print_out('\n');
}
