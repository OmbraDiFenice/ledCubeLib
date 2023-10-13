#include "ArduinoAnimator.h"

#include <Arduino.h>

ArduinoAnimator::ArduinoAnimator(unsigned int outputReadyPin, unsigned int outputPin, unsigned int clockPin) : _painter(outputReadyPin, outputPin, clockPin) {
	pinMode(clockPin, OUTPUT);
	pinMode(outputPin, OUTPUT);
	pinMode(outputReadyPin, OUTPUT);

	digitalWrite(outputReadyPin, LOW);
	digitalWrite(clockPin, LOW);
}

const Painter& ArduinoAnimator::getPainter() const {
    return _painter;
}
