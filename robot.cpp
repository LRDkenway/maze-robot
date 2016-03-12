#include "direction.h"
#include "robot.h"
#include "room.h"

const Robot::pins Robot::PINS = {2, 3, 4, 5, 0, 1, 2};
const Robot::thresholds Robot::THRESHOLDS = {200, 300, 250};

void Robot::step_motors(unsigned int delay) {
    unsigned long delta;

    digitalWrite(PINS.RIGHT_MOTOR, HIGH);
    digitalWrite(PINS.LEFT_MOTOR, HIGH);

    delta = update_readings();
    if (delta < delay) {
        delayMicroseconds(delay - delta);
    }

    digitalWrite(PINS.RIGHT_MOTOR, LOW);
    digitalWrite(PINS.LEFT_MOTOR, LOW);

    delta = update_readings();
    if (delta < delay) {
        delayMicroseconds(delay - delta);
    }
}

void Robot::step_left(unsigned int delay) {
    digitalWrite(PINS.LEFT_MOTOR, HIGH);
    update_readings();
    delayMicroseconds(delay);
    digitalWrite(PINS.LEFT_MOTOR, LOW);
    update_readings();
    delayMicroseconds(delay);
}

void Robot::step_right(unsigned int delay) {
    digitalWrite(PINS.RIGHT_MOTOR, HIGH);
    update_readings();
    delayMicroseconds(delay);
    digitalWrite(PINS.RIGHT_MOTOR, LOW);
    update_readings();
    delayMicroseconds(delay);
}

void Robot::turn(Direction towards) {
    uint16_t steps = TURN_STEPS;

    if (towards == Directions::left(facing)) {
        left_motor_backward();
        right_motor_forward();
    } else if (towards == Directions::right(facing)) {
        left_motor_forward();
        right_motor_backward();
    } else if (towards == Directions::opposite(facing)) {
        left_motor_forward();
        right_motor_backward();
        steps *= 2;
    } else {
        return; //don't need to turn because already facing the right way
    }

    for (uint16_t i = 0; i < steps; i++) {
        step_motors(STEP_DELAY);
    }

    facing = towards;
}

void Robot::move(Direction dir) {
    turn(dir);

    left_motor_forward();
    right_motor_forward();


    for (uint16_t i = 0; i < CELL_STEPS; i++) {
        if (is_wall_front_close) {
            return;
        }
        if (is_wall_left_close) {
            step_left(STEP_DELAY / 2);
        } else if (is_wall_right_close) {
            step_right(STEP_DELAY / 2);
        }
        step_motors(STEP_DELAY);
    }
}

void Robot::explore(Direction dir, Room *dest) {
    move(dir);

    dest->set_open(Directions::left(facing), is_wall_left);
    dest->set_open(Directions::right(facing), is_wall_right);
    dest->set_open(facing, is_wall_front);
}

static void shift_right(int arr[], const uint8_t len) {
    for (uint8_t i = len - 1; i > 0; i--) {
        arr[i] = arr[i - 1];
    }
}

static int avg(const int arr[], const uint8_t len) {
    int sum = 0;
    for (uint8_t i = 0; i < len; i++) {
        sum += arr[i];
    }
    return sum / len;
}

unsigned long Robot::update_readings(void) {
    unsigned long start = micros();

    shift_right(left_readings, NUM_READINGS);
    shift_right(right_readings, NUM_READINGS);
    shift_right(front_readings, NUM_READINGS);

    //take a reading
    left_readings[0] = analogRead(PINS.LEFT_SENSOR);
    right_readings[0] = analogRead(PINS.RIGHT_SENSOR);
    front_readings[0] = analogRead(PINS.FRONT_SENSOR);

    int left_avg = avg(left_readings, NUM_READINGS),
        right_avg = avg(right_readings, NUM_READINGS),
        front_avg = avg(front_readings, NUM_READINGS);

    is_wall_left = left_avg > THRESHOLDS.WALL;
    is_wall_right = right_avg > THRESHOLDS.WALL;
    is_wall_front = front_avg > THRESHOLDS.WALL;

    is_wall_left_close = left_avg > THRESHOLDS.WALL_CLOSE;
    is_wall_right_close = right_avg > THRESHOLDS.WALL_CLOSE;
    is_wall_front_close = front_avg > THRESHOLDS.FRONT_WALL_CLOSE;

    return micros() - start;
}

void Robot::init_pins(void) {
    pinMode(PINS.LEFT_MOTOR, OUTPUT);
    pinMode(PINS.LEFT_DIR, OUTPUT);
    pinMode(PINS.RIGHT_MOTOR, OUTPUT);
    pinMode(PINS.RIGHT_DIR, OUTPUT);
}
