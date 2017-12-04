/*
 Name:		rov_scout_firmware.ino
 Created:	04.12.2017 17:03:13
 Author:	zinjk
*/
#include <Servo.h>
#include <Arduino.h>
#include "crc.h"
#include "Scout.h"

#define EMPTY_COMMAND 0

#define START_HIGH_BYTE 0xFE
#define START_LOW_BYTE 0xAE

#define START_HIGH_BYTE_COMMAND 0
#define START_LOW_BYTE_COMMAND 1
#define HORIZONTAL_MOTOR_Y_COMMAND 2
#define HORIZONTAL_MOTOR_X_COMMAND 3
#define VERTICAL_MOTOR_Y_COMMAND 4
#define VERTICAL_MOTOR_X_COMMAND 5
#define MANIPULATOR_COMMAND 6
#define CRC_COMMAND 7
#define COMMAND_BUFFER_SIZE 8


Scout robot;
void setup() {
	Serial.begin(115200);
	Serial2.begin(115200);
}
void loop() {
	if (robot.is_updated()) {
		robot.apply_update();
	}
}

void serialEvent2() {
	uint8_t buffer[COMMAND_BUFFER_SIZE] = { EMPTY_COMMAND };
	while (Serial2.available()) {
		Serial2.readBytes(buffer, COMMAND_BUFFER_SIZE);
	}

	if ((buffer[START_HIGH_BYTE_COMMAND] == START_HIGH_BYTE)
		&& (buffer[START_LOW_BYTE_COMMAND] == START_LOW_BYTE)) {
		uint8_t pcrc = crc::calculate_crc(buffer, COMMAND_BUFFER_SIZE - 1);

		if (buffer[CRC_COMMAND] == pcrc) {
			robot.update(buffer[HORIZONTAL_MOTOR_X_COMMAND], 
				buffer[HORIZONTAL_MOTOR_Y_COMMAND],
				buffer[VERTICAL_MOTOR_X_COMMAND], 
				buffer[VERTICAL_MOTOR_Y_COMMAND],
				buffer[MANIPULATOR_COMMAND]);
		}
	}
}
