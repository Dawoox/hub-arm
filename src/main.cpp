#include <Arduino.h>
#include <Servo.h>
#include <ArduPID.h>

namespace {
    const int smoothFactor_Base = 10;
    const int smoothFactor_Shoulder = 2;
    const int smoothFactor_Elbow = 5;

    constexpr int kServoBasePin = 6;
    constexpr int kServoShoulderPin = 3;
    constexpr int kServoElbowPin = 5;
    constexpr int kServoClawPin = 9;

    Servo servo_base;
    Servo servo_shoulder;
    Servo servo_elbow;
    Servo servo_claw;

    float joy1XValue = 0;
    float joy1YValue = 0;
    float joy2XValue = 0;
    float joy2YValue = 0;

    constexpr int kJoy1XPin = A0;
    constexpr int kJoy1YPin = A1;
    constexpr int kJoy2XPin = A2;
    constexpr int kJoy2YPin = A3;
}

void setup() {
    servo_base.attach(kServoBasePin);
    servo_shoulder.attach(kServoShoulderPin);
    servo_elbow.attach(kServoElbowPin);
    servo_claw.attach(kServoClawPin);
}

void loop() {
    joy1XValue = analogRead(kJoy1XPin);
    joy1YValue = analogRead(kJoy1YPin);

    joy2XValue = analogRead(kJoy2XPin);
    joy2YValue = analogRead(kJoy2YPin);

    const int mappedBase = static_cast<int>(map(joy1YValue, 0, 1023, 180, 0));
    const int currentBase = static_cast<int>(servo_base.read());
    if (abs(mappedBase - currentBase) > smoothFactor_Base) {
        int target = currentBase + (mappedBase < currentBase ? - smoothFactor_Base : smoothFactor_Base);
        target = constrain(target, 0, 180);
        servo_base.write(target);
    } else {
        servo_base.write(mappedBase);
    }

    const int mappedElbow = static_cast<int>(map(joy1XValue, 0, 1023, 0, 180));
    const int currentElbow = static_cast<int>(servo_elbow.read());
    if (abs(mappedElbow - currentElbow) > smoothFactor_Elbow) {
        int target = currentElbow + (mappedElbow < currentElbow ? - smoothFactor_Elbow : smoothFactor_Elbow);
        target = constrain(target, 0, 180);
        servo_elbow.write(target);
    } else {
        servo_elbow.write(mappedElbow);
    }

    const int mappedShoulder = static_cast<int>(map(joy2XValue, 0, 1023, 0, 180));
    const int currentShoulder = static_cast<int>(servo_shoulder.read());
    if (abs(mappedShoulder - currentShoulder) > smoothFactor_Shoulder) {
        int target = currentShoulder + (mappedShoulder < currentShoulder ? - smoothFactor_Shoulder : smoothFactor_Shoulder);
        target = constrain(target, 0, 180);
        servo_shoulder.write(target);
    } else {
        servo_shoulder.write(mappedShoulder);
    }

    const int mappedCraw = static_cast<int>(map(joy2YValue, 0, 1023, 0, 180));
    const int currentCraw = static_cast<int>(servo_claw.read());
    if (abs(mappedCraw - currentCraw) > 10) {
        int target = currentCraw + (mappedCraw < currentCraw ? -10 : 10);
        target = constrain(target, 0, 180);
        servo_claw.write(target);
    } else {
        servo_claw.write(mappedShoulder);
    }

    delay(50);
}
