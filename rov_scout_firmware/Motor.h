//
// Created by zinjk on 09.10.2017.
//

#ifndef OVERWATER_FIRMWARE_MOTOR_H
#define OVERWATER_FIRMWARE_MOTOR_H

#include <stdint.h>
class Motor {
public:
    Motor(uint8_t _pin_1, uint8_t _pin_2);
    void setPower(int8_t power);
private:
    uint8_t m_pinOne;
    uint8_t m_pinTwo;
};


#endif //OVERWATER_FIRMWARE_MOTOR_H
