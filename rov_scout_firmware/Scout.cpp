//
// Created by zinjk on 09.10.2017.
//

#include <Arduino.h>
#include "Scout.h"

#define GRAB 1
#define RELEASE 2

Scout::Scout(): m_left(2, 3), m_right(4, 5), m_up_one(6, 7), m_up_two(8, 9), m_manipulator_state(0)
{
    m_manipulator.attach(45);
    m_manipulator.write(m_manipulator_state);
    m_left.setPower(0);
    m_right.setPower(0);
    m_up_one.setPower(0);
    m_up_two.setPower(0);
    m_updated = false;
}
void Scout::set_horizontal_motor(int8_t x, int8_t y) {
    x -= 128; y -= 127;
    x *= -1; y *= -1;
    regulator(y, x, m_right, m_left);
}
void Scout::set_vertical_motor(int8_t x, int8_t y) {
    x -= 128; y -= 127;
    x *= -1; y *= -1;
    regulator(y, x, m_up_one, m_up_two);
}
void Scout::set_manipulator_action(uint8_t action) {
    if (action == GRAB) {
        if (m_manipulator_state > 0) {
            m_manipulator_state -= 1;
        }
    }
    if (action == RELEASE) {
        if (m_manipulator_state < 180) {
            m_manipulator_state += 1;
        }
    }
    m_manipulator.write(m_manipulator_state);
}

void Scout::regulator(int8_t power, int8_t error, Motor motor_one, Motor motor_two) {
    power /= 1.28;
    error /= 1.28;
    motor_one.setPower(power - error);
    motor_two.setPower(power + error);
    return;
}

void Scout::update(int8_t lx, int8_t ly, int8_t rx, int8_t ry, uint8_t action) {
    m_lx = lx; m_rx = rx;
    m_ly = ly; m_ry = ry;
    m_action = action;
    m_updated = true;
}

bool Scout::is_updated() {
    return m_updated;
}

void Scout::apply_update() {
    set_horizontal_motor(m_lx, m_ly);
    set_vertical_motor(m_rx, m_ry);
    set_manipulator_action(m_action);
    m_updated = false;
}