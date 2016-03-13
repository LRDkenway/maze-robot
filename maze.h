#ifndef __maze_h__
#define __maze_h__

#include <stdint.h>
#include "constants.h"
#include "direction.h"
#include "room.h"

class Robot;

class Maze {

#if (NUM_ROWS * NUM_COLS) <= 256
    typedef uint8_t RoomIndex;
#else
    typedef uint16_t RoomIndex;
#endif

    static const uint8_t X_INCR[4]; //= {0, 1, 0, -1};
    static const uint8_t Y_INCR[4]; //= { -1, 0, 1, 0};

    Room rooms[NUM_ROWS * NUM_COLS];

    static inline RoomIndex get_index(const uint8_t row, const uint8_t col) {
        return row * NUM_COLS + col;
    }

    static inline int is_in_range(const uint8_t row, const uint8_t col) {
        return (row >= 0 && row < NUM_ROWS) && (col >= 0 && col < NUM_COLS);
    }

    RoomIndex move(const RoomIndex room_i, const Direction dir);

    int get_neighbor(const RoomIndex room_i, Direction *neighbor);

    int dfs(RoomIndex room_i, const RoomIndex goal_room_i);

    void clear_visited(void);

    int get_rand_neighbor(RoomIndex *room_i);
    void drunken_walk(RoomIndex room_i);
    void print(RoomIndex robot_i, RoomIndex goal_room_i);

public:
    inline int solve(const uint8_t start_row, const uint8_t start_col,
                     const uint8_t goal_row, const uint8_t goal_col) {
        return dfs(get_index(start_row, start_col), get_index(goal_row, goal_col));
    }

    inline void generate(const uint8_t start_row, const uint8_t start_col) {
        drunken_walk(get_index(start_row, start_col));
    }

    void print_info(const uint8_t goal_row, const uint8_t goal_col);
};

#endif /* __maze_h__ */
