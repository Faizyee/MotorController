#include <MotorController_x2.h>

MotorController_x2 motorController(9, 10, 11, 12, 5, 6);  // Replace with your actual pin numbers

void eventHandler(MotorController_x2::EventType eventType, int speed1, int speed2) {
    switch (eventType) {
        case MotorController_x2::HorizontalLeft:
            Serial.print("Moving Left: LR Speed: ");
            Serial.print(speed1);
            Serial.print(" | UD Speed: ");
            Serial.println(speed2);
            break;
        case MotorController_x2::HorizontalRight:
            Serial.print("Moving Right: LR Speed: ");
            Serial.print(speed1);
            Serial.print(" | UD Speed: ");
            Serial.println(speed2);
            break;
        case MotorController_x2::VerticalUp:
            Serial.println("Moving Up");
            break;
        case MotorController_x2::VerticalDown:
            Serial.println("Moving Down");
            break;
    }
}

void setup() {
    Serial.begin(9600);
    motorController.begin(0, 255);  // Set minimum and maximum values
    motorController.setEvent(eventHandler);  // Set the single event handler
}

void loop() {
    int UD_p = analogRead(A0);  // Replace with your actual input pin
    int LR_p = analogRead(A1);  // Replace with your actual input pin
    motorController.loop(UD_p, LR_p);
}
