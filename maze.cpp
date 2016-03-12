#include "maze.h"
#include "robot.h"

#ifdef VERBOSE_DFS

#ifdef TEST
#include <unistd.h>
#define print_state(room_i, goal_room_i) print(room_i, goal_room_i); usleep(100000)
#else
#define print_state(room_i, goal_room_i) print(room_i, goal_room_i)
#endif

#else /* VERBOSE_DFS */
//neutralize the print statements
#define print_state(room_i, goal_room_i)
#endif /* VERBOSE_DFS */

const uint8_t Maze::X_INCR[] = {0, 1, 0, -1};
const uint8_t Maze::Y_INCR[] = { -1, 0, 1, 0};

extern Robot robot;

uint8_t Maze::move(const uint8_t room_i, const Direction dir) {
    robot.move(dir);
    return get_index((room_i / NUM_COLS) + Y_INCR[dir], (room_i % NUM_COLS) + X_INCR[dir]);
}

int Maze::get_neighbor(const uint8_t room_i, Direction *neighbor) {
    uint8_t room_row = room_i / NUM_COLS,
            room_col = room_i % NUM_COLS;
    for (Direction dir = 0; dir < 4; dir++) {
        if (rooms[room_i].is_open(dir)) {
            uint8_t next_row = room_row + Y_INCR[dir],
                    next_col = room_col + X_INCR[dir];

            if (is_in_range(next_row, next_col)
                    && !rooms[get_index(next_row, next_col)].is_visited()) {

                *neighbor = dir;
                return 1;
            }
        }
    }
    return 0;
}

int Maze::dfs(uint8_t room_i, const uint8_t goal_room_i) {
    DirStack moves;

    Direction dir, neighbor;

    clear_visited();

    while (1) {
        if (room_i == goal_room_i) {
            //backtrack
            while (moves.is_nonempty()) {
                dir = moves.pop();
                room_i = move(room_i, Directions::opposite(dir));
                rooms[room_i].set_next(dir);
                rooms[room_i].mark_solution();

                print_state(room_i, goal_room_i);
            }
            return 1;
        }
        rooms[room_i].mark_visited();

        //backtrack until there are unvisited neighbors
        while (!get_neighbor(room_i, &neighbor)) {
            if (moves.is_nonempty()) {
                room_i = move(room_i, Directions::opposite(moves.pop()));
                print_state(room_i, get_index(NUM_ROWS / 2, NUM_COLS / 2));
            } else {
                //can't backtrack anymore, so no solution was found
                return 0;
            }
        }

        //found an unvisited neighbor
        moves.push(neighbor); //store the move on the move stack
        room_i = move(room_i, neighbor);
        print_state(room_i, get_index(NUM_ROWS / 2, NUM_COLS / 2));
    }
}

void Maze::clear_visited(void) {
    const uint16_t num_rooms = NUM_ROWS * NUM_COLS;
    for (uint16_t i = 0; i < num_rooms; i++) {
        rooms[i].mark_unvisited();
    }
}

