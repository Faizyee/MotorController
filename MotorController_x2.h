#ifndef MotorController_x2_h
#define MotorController_x2_h

#include <Arduino.h>

class MotorController_x2 {
public:
    enum EventType {
        HorizontalLeft,
        HorizontalRight,
        VerticalUp,
        VerticalDown
    };

    MotorController_x2(int lenPin, int renPin, int lin1Pin, int lin2Pin, int rin1Pin, int rin2Pin);
    void begin(int minimum, int maximum);
    void setEvent(void (*event)(EventType, int, int));
    void loop(int UD_p, int LR_p);

private:
    int LEN, REN, LIN1, LIN2, RIN1, RIN2;
    void (*eventCallback)(EventType, int, int);
    int minValue;  // Minimum value for mapping
    int maxValue;  // Maximum value for mapping
    
    void stirAnalogX2(int UD_p, int LR_p);
};

#endif
