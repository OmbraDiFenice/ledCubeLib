#include "ArduinoPainter.h"

#include <Arduino.h>

void ArduinoPainter::shiftOut(unsigned char data, ShiftMode shiftMode) const {
    ::shiftOut(OUTPUT_PIN, CLOCK_PIN, shiftMode == ShiftMode::LSB_FIRST ? LSBFIRST : MSBFIRST, data);
}

void ArduinoPainter::dataReady() const {
	digitalWrite(OUTPUT_READY_PIN, HIGH);
	digitalWrite(OUTPUT_READY_PIN, LOW);
}

void ArduinoPainter::initPaint() const {
    digitalWrite(OUTPUT_READY_PIN, LOW);
    digitalWrite(CLOCK_PIN, LOW);
}

void ArduinoPainter::wait(int milliseconds) const {
	delay(milliseconds);
}
