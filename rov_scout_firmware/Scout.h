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
    Scout(Servo& servo);
    void set_horizontal_motor(int16_t x, int16_t y);
    void set_vertical_motor(int16_t x, int16_t y);
    void set_manipulator_action(uint8_t action);
	void setCamera(Servo *camera);
    void update(int16_t lx, int16_t ly, int16_t rx, int16_t ry, uint8_t action, int8_t camera_action);
    bool is_updated();
    void apply_update();
	void camera_rotate();
private:
    Motor m_left;
    Motor m_right;
    Motor m_up_one;
    Motor m_up_two;
    Servo &m_manipulator;
	Servo *m_camera;

    int m_manipulator_state;
    int16_t m_lx;
    int16_t m_ly;
    int16_t m_rx;
    int16_t m_ry;
    uint8_t m_action;
	int8_t m_camera_action;
	int16_t m_camera_angle;
    bool m_updated;

    void regulator(int16_t power, int16_t error, Motor motor_one, Motor motor_two);
};


#endif //OVERWATER_FIRMWARE_SCOUT_H
