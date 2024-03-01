#include <Arduino.h>
#include <Servo.h>
#include <ArduPID.h>
#include <SerialRecord.h>

namespace {
    SerialRecord writer(3);

    constexpr int kServoBasePin = 6;
    constexpr int kServoShoulderPin = 3;
    constexpr int kServoElbowPin = 5;
    //constexpr int kServoClawPin = 9;

    ArduPID controllerBase;
    ArduPID controllerShoulder;
    ArduPID controllerElbow;

    double setPoint_Base;
    double setPoint_Shoulder;
    double setPoint_Elbow;

    double output_Base;
    double output_Shoulder;
    double output_Elbow;

    double input_Base;
    double input_Shoulder;
    double input_Elbow;

    Servo servo_base;
    Servo servo_shoulder;
    Servo servo_elbow;

    constexpr int kJoy1XPin = A0;
    constexpr int kJoy1YPin = A1;
    constexpr int kJoy2XPin = A2;
    constexpr int kJoy2YPin = A3;
}

void setup() {
    Serial.begin(9600);
    writer.setFieldName(0, "input_Base");
    writer.setFieldName(1, "setPoint_Base");
    writer.setFieldName(2, "output_Base");

    servo_base.attach(kServoBasePin);
    servo_shoulder.attach(kServoShoulderPin);
    servo_elbow.attach(kServoElbowPin);
    //servo_claw.attach(kServoClawPin);

    controllerBase.begin(&input_Base, &output_Base, &setPoint_Base, 1, 0, 0);
    controllerShoulder.begin(&input_Shoulder, &output_Shoulder, &setPoint_Shoulder, 1, 0, 0);
    controllerElbow.begin(&input_Elbow, &output_Elbow, &setPoint_Elbow, 1, 0, 0);

    controllerBase.setOutputLimits(0, 180);
    controllerShoulder.setOutputLimits(0, 180);
    controllerElbow.setOutputLimits(0, 180);

    controllerBase.start();
    controllerShoulder.start();
    controllerElbow.start();
}

void loop() {
    input_Base = servo_base.read();
    setPoint_Base = map(analogRead(kJoy1XPin), 0, 1023, 180, 0);
    writer[0] = input_Base;
    writer[1] = setPoint_Base;
    writer[2] = output_Base;
    writer.send();
    controllerBase.compute();
    servo_base.write(output_Base);
    delay(100);
}
