#ifndef __robot_h__
#define __robot_h__

#include "direction.h"

class Room;

class Robot {
    static const struct pins {
        uint8_t RIGHT_MOTOR, RIGHT_DIR, LEFT_MOTOR, LEFT_DIR,
                LEFT_SENSOR, RIGHT_SENSOR, FRONT_SENSOR;
    } PINS;

    static const struct thresholds {
        uint16_t WALL, WALL_CLOSE, FRONT_WALL_CLOSE;
    } THRESHOLDS;

    static const uint8_t NUM_READINGS = 5;

    static const uint16_t CELL_STEPS = 280,
                          TURN_STEPS = 105,
                          STEP_DELAY = 1300;//4000,


    Direction facing;

    int left_readings[NUM_READINGS];
    int right_readings[NUM_READINGS];
    int front_readings[NUM_READINGS];

    uint8_t is_wall_left, is_wall_right, is_wall_front;
    uint8_t is_wall_left_close, is_wall_right_close, is_wall_front_close;


    inline void left_motor_forward(void) {
        digitalWrite(PINS.LEFT_DIR, LOW);
    }
    inline void left_motor_backward(void) {
        digitalWrite(PINS.LEFT_DIR, HIGH);
    }
    inline void right_motor_forward(void) {
        digitalWrite(PINS.RIGHT_DIR, HIGH);
    }
    inline void right_motor_backward(void) {
        digitalWrite(PINS.RIGHT_DIR, LOW);
    }

    void step_motors(int delay);

    void step_left(int delay);

    void step_right(int delay);

    void turn(Direction towards);


public:
    unsigned long update_readings(void);
    void init_pins(void);

    void move(Direction dir);

    void explore(Direction dir, Room *dest);


    void print_readings(void) {
        print_out("L: ");
        print_out(is_wall_left);
        print_out(is_wall_left_close);

        print_out(", F: ");
        print_out(is_wall_front);
        print_out(is_wall_front_close);

        print_out(", R: ");
        print_out(is_wall_right);
        print_out(is_wall_right_close);
        print_out('\n');
    }

    void test_move(void) {
        while (!is_wall_front_close) {
            move(Directions::NORTH);
        }
        move(Directions::EAST);
        move(Directions::EAST);
        while (!is_wall_front_close) {
            move(Directions::WEST);
        }
        move(Directions::SOUTH);
        move(Directions::SOUTH);
        turn(Directions::NORTH);
    }
};

#endif /* __robot_h__ */
