//
// Created by zinjk on 09.10.2017.
//

#include <Arduino.h>
#include "Scout.h"

#define GRAB 1
#define RELEASE 2
//				ПИНЫ МОТОРОВ
Scout::Scout(Servo& servo) : m_left(6, 7), m_right(8, 9), m_up_one(2, 3), m_up_two(4, 5), m_manipulator_state(90), m_manipulator(servo), m_camera_angle(100), m_camera_action(0)
{
    m_left.setPower(100);
    m_right.setPower(0);
    m_up_one.setPower(0);
    m_up_two.setPower(0);
	m_camera->write(100);
    m_updated = false;
}

void Scout::set_horizontal_motor(int16_t x, int16_t y) {
    x -= 128; y -= 127;
    x *= -1; y *= -1;
    regulator(y, x, m_right, m_left);
}

void Scout::set_vertical_motor(int16_t x, int16_t y) {
    x -= 128; y -= 127;
    x *= -1; y *= -1;
    regulator(y, x, m_up_one, m_up_two);
}

void Scout::set_manipulator_action(uint8_t action) {
    int old = m_manipulator_state;
    if (action == GRAB) {
        if (m_manipulator_state > 100) {
            m_manipulator_state -= 2;
        }
    }
    if (action == RELEASE) {
        if (m_manipulator_state < 145) {
            m_manipulator_state += 2;
        }
    }

    if(old != m_manipulator_state) {
      m_manipulator.write(m_manipulator_state);
    }
    
   
}

void Scout::setCamera(Servo *camera)
{
	m_camera = camera;
}

void Scout::regulator(int16_t power, int16_t error, Motor motor_one, Motor motor_two) {
    power /= 1.28;
    error /= 1.28;
    motor_one.setPower(power - error);
    motor_two.setPower(power + error);
    return;
}

void Scout::update(int16_t lx, int16_t ly, int16_t rx, int16_t ry, uint8_t action, int8_t camera_action) {
    m_lx = lx; m_rx = rx;
    m_ly = ly; m_ry = ry;
	m_camera_action = camera_action;
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
	camera_rotate();
    m_updated = false;
}

void Scout::camera_rotate()
{
	int32_t diff = 0;
	if (m_camera_action == 1) {
		diff = 1;
	}
	if (m_camera_action == -1) {
		diff = -1;
	}

	m_camera_angle = constrain(m_camera_angle + diff, 0, 180);
	m_camera->write(m_camera_angle);

}
