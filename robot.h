#ifndef __robot_h__
#define __robot_h__

#include <stdint.h>
#include "direction.h"

class Room;

class Robot {
    struct PINS {
        static const uint8_t RIGHT_MOTOR = 2,
                             RIGHT_DIR = 3,
                             LEFT_MOTOR = 4,
                             LEFT_DIR = 5,
                             LEFT_SENSOR = 0,
                             RIGHT_SENSOR = 1,
                             FRONT_SENSOR = 2;
    };

    struct THRESHOLDS {
        static const int16_t WALL = 200, WALL_CLOSE = 300, FRONT_WALL_CLOSE = 250;
    };

    struct STEPS {
        static const uint16_t CELL = 280, TURN = 105, DELAY = 1300; //microseconds
    };

    class Readings {
        static const uint8_t NUM_READINGS = 5;
        int left_readings[NUM_READINGS];
        int right_readings[NUM_READINGS];
        int front_readings[NUM_READINGS];
    public:
        uint8_t is_wall_left, is_wall_right, is_wall_front;
        uint8_t is_wall_left_close, is_wall_right_close, is_wall_front_close;
        unsigned long update(void);
    } readings;

    Direction facing;

    inline void left_motor_forward(void) {
        digitalWrite(PINS::LEFT_DIR, LOW);
    }
    inline void left_motor_backward(void) {
        digitalWrite(PINS::LEFT_DIR, HIGH);
    }
    inline void right_motor_forward(void) {
        digitalWrite(PINS::RIGHT_DIR, HIGH);
    }
    inline void right_motor_backward(void) {
        digitalWrite(PINS::RIGHT_DIR, LOW);
    }

    void step_motors(unsigned int delay);

    void step_left(unsigned int delay);

    void step_right(unsigned int delay);

    void turn(Direction towards);

public:
    unsigned long update_readings(void);
    void init_pins(void);

    void move(Direction dir);

    void explore(Direction dir, Room *dest);

    void print_readings(void) {
        print_out("L: ");
        print_out(readings.is_wall_left);
        print_out(readings.is_wall_left_close);

        print_out(", F: ");
        print_out(readings.is_wall_front);
        print_out(readings.is_wall_front_close);

        print_out(", R: ");
        print_out(readings.is_wall_right);
        print_out(readings.is_wall_right_close);
        print_out('\n');
    }

    void test_move(void) {
        while (!readings.is_wall_front_close) {
            move(Directions::NORTH);
        }
        move(Directions::EAST);
        move(Directions::EAST);
        while (!readings.is_wall_front_close) {
            move(Directions::WEST);
        }
        move(Directions::SOUTH);
        move(Directions::SOUTH);
        turn(Directions::NORTH);
    }
};

#endif /* __robot_h__ */
