#include <Arduino.h>
#include <Servo.h>
namespace {
    constexpr int kServoBasePin = 6;
    constexpr int kServoShoulderPin = 3;
    constexpr int kServoElbowPin = 5;
    constexpr int kServoClawPin = 9;

    Servo servo_base;
    Servo servo_shoulder;
    Servo servo_elbow;
    Servo servo_claw;

    int joy1XValue = 0;
    int joy1YValue = 0;
    int joy2XValue = 0;
    int joy2YValue = 0;

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

    servo_base.write(90);
    servo_elbow.write(90);
    servo_shoulder.write(90);
    servo_claw.write(0);
}

void loop() {
    joy1XValue = analogRead(kJoy1XPin);
    joy1YValue = analogRead(kJoy1YPin);

    joy2XValue = analogRead(kJoy2XPin);
    joy2YValue = analogRead(kJoy2YPin);

    const int mappedBase = static_cast<int>(map(joy1YValue, 0, 1023, 180, 0));
    servo_base.write(mappedBase);
    const int mappedElbow = static_cast<int>(map(joy1XValue, 0, 1023, 0, 180));
    servo_elbow.write(mappedElbow);
    const int mappedShoulder = static_cast<int>(map(joy2XValue, 0, 1023, 0, 180));
    servo_shoulder.write(mappedShoulder);
// write your code here
}
