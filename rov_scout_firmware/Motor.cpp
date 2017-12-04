//
// Created by zinjk on 09.10.2017.
//

#include "Motor.h"
#include <Arduino.h>

Motor::Motor(uint8_t _pin_1, uint8_t _pin_2): m_pinOne(_pin_1), m_pinTwo(_pin_2) {
    pinMode(m_pinOne, OUTPUT);
    pinMode(m_pinTwo, OUTPUT);
}
void Motor::setPower(int8_t power_to_set) {
    uint8_t power = 0;
    if(power_to_set >= 0) {
        power = (uint8_t)power_to_set * 2.55;

        analogWrite(m_pinOne, power);
        analogWrite(m_pinTwo, 0);
    } else {
        power = (uint8_t)-power_to_set * 2.55;
        analogWrite(m_pinOne, 0);
        analogWrite(m_pinTwo, power);
    }
}