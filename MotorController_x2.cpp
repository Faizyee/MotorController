#include "MotorController_x2.h"

MotorController_x2::MotorController_x2(int lenPin, int renPin, int lin1Pin, int lin2Pin, int rin1Pin, int rin2Pin) {
    LEN = lenPin;
    REN = renPin;
    LIN1 = lin1Pin;
    LIN2 = lin2Pin;
    RIN1 = rin1Pin;
    RIN2 = rin2Pin;
    eventCallback = nullptr;
    minValue = 0;  // Default minimum
    maxValue = 255; // Default maximum
}

void MotorController_x2::begin(int minimum, int maximum) {
    pinMode(LEN, OUTPUT);
    pinMode(REN, OUTPUT);
    pinMode(LIN1, OUTPUT);
    pinMode(LIN2, OUTPUT);
    pinMode(RIN1, OUTPUT);
    pinMode(RIN2, OUTPUT);
    minValue = minimum;  // Set minimum value
    maxValue = maximum;  // Set maximum value
}

void MotorController_x2::setEvent(void (*event)(EventType, int, int)) {
    eventCallback = event;
}

void MotorController_x2::loop(int UD_p, int LR_p) {
    stirAnalogX2(UD_p, LR_p);
}

void MotorController_x2::stirAnalogX2(int UD_p, int LR_p) {
    int UD_speed = abs(map(UD_p, minValue, maxValue, -255.00, 255.00));
    int LR_speed = abs(UD_speed - (UD_speed * (abs(map(LR_p, minValue, maxValue, -100.00, 100.00)) / 100.00)));

    // Handle horizontal movement
    if (LR_p < (minValue + maxValue) / 2 - ((abs(minValue) + abs(maxValue)) * 0.004)) {  // Analog Right Horizontal
        analogWrite(LEN, LR_speed);
        analogWrite(REN, UD_speed);
        if (eventCallback) eventCallback(HorizontalLeft, LR_speed, UD_speed);
    } else if (LR_p > (minValue + maxValue) / 2 + ((abs(minValue) + abs(maxValue)) * 0.004)) {
        analogWrite(LEN, UD_speed);
        analogWrite(REN, LR_speed);
        if (eventCallback) eventCallback(HorizontalRight, UD_speed, LR_speed);
    } else {
        analogWrite(LEN, UD_speed);
        analogWrite(REN, UD_speed);
    }

    // Handle vertical movement
    if (UD_p < ((minValue + maxValue) / 2) - ((abs(minValue) + abs(maxValue)) * 0.004)) {  // Analog Left Vertical
        digitalWrite(LIN1, LOW);
        digitalWrite(LIN2, HIGH);
        digitalWrite(RIN1, LOW);
        digitalWrite(RIN2, HIGH);
        if (eventCallback) eventCallback(VerticalUp, 0, 0);
    } else if (UD_p > (minValue + maxValue) / 2 + ((abs(minValue) + abs(maxValue)) * 0.004)) {
        digitalWrite(LIN1, HIGH);
        digitalWrite(LIN2, LOW);
        digitalWrite(RIN1, HIGH);
        digitalWrite(RIN2, LOW);
        if (eventCallback) eventCallback(VerticalDown, 0, 0);
    } else {
        digitalWrite(LIN1, LOW);
        digitalWrite(LIN2, LOW);
        digitalWrite(RIN1, LOW);
        digitalWrite(RIN2, LOW);
    }
}
