//
// Created by zinjk on 09.10.2017.
//

#ifndef OVERWATER_FIRMWARE_SCOUT_H
#define OVERWATER_FIRMWARE_SCOUT_H

#include "Motor.h"
#include <Servo.h>
#include <stdint.h>
class Scout {
public:
    Scout();
    void set_horizontal_motor(int8_t x, int8_t y);
    void set_vertical_motor(int8_t x, int8_t y);
    void set_manipulator_action(uint8_t action);
    void update(int8_t lx, int8_t ly, int8_t rx, int8_t ry, uint8_t action);
    bool is_updated();
    void apply_update();
private:
    Motor m_left;
    Motor m_right;
    Motor m_up_one;
    Motor m_up_two;
    Servo m_manipulator;

    int m_manipulator_state;
    int8_t m_lx;
    int8_t m_ly;
    int8_t m_rx;
    int8_t m_ry;
    uint8_t m_action;
    bool m_updated;

    void regulator(int8_t power, int8_t error, Motor motor_one, Motor motor_two);
};


#endif //OVERWATER_FIRMWARE_SCOUT_H
