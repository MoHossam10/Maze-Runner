#include "AFMotor.h"
#define IRSensorR A0
#define IRSensorF A3
AF_DCMotor motorR (2);
AF_DCMotor motorL (1);
int velocity = 255;
int velocityR = 0;
int velocityL = 0;
int IRSensorStatus_R, IRSensorStatus_Old_R = 0;
int IRSensorStatus_F, IRSensorStatus_Old_F = 0;
int cmd;
void setup() {
  Serial.begin(9600);
  Serial.setTimeout(5);
  pinMode (IRSensorR, INPUT);
  pinMode (IRSensorF, INPUT);
}
void loop() {
  /////////////// IR Sensor //////////////////////////////////////////////////
  velocityR = 0.8 * velocity;
  velocityL = 1 * velocity;
  IRSensorStatus_R = digitalRead (IRSensorR);
  IRSensorStatus_F = digitalRead (IRSensorF);
  if (IRSensorStatus_F == 0 && IRSensorStatus_R == 0)
  {
    motorR.setSpeed(0);
    motorL.setSpeed(0);
    motorL.run(RELEASE);
    motorR.run(RELEASE);
    motorR.setSpeed(velocityR);
    motorL.setSpeed(velocityL);
    motorL.run(BACKWARD);
    motorR.run(BACKWARD);
    delay(250);
    motorR.setSpeed(0);
    motorL.setSpeed(0);
    motorL.run(RELEASE);
    motorR.run(RELEASE);
    delay(100);
    motorR.setSpeed(velocityR);
    motorL.setSpeed(velocityL);
    motorL.run(BACKWARD);
    motorR.run(FORWARD);
    delay(250);
  }
  if (IRSensorStatus_F == 0 && IRSensorStatus_R == 1)
  {
    motorR.setSpeed(velocityR);
    motorL.setSpeed(velocityL);
    motorL.run(BACKWARD);
    motorR.run(BACKWARD);

  }
  if (IRSensorStatus_F == 1 && IRSensorStatus_R == 0)
  {
    motorR.setSpeed(velocityR);
    motorL.setSpeed(velocityL);
    motorL.run(FORWARD);
    motorR.run(FORWARD);

  }
  if (IRSensorStatus_R == 1 && IRSensorStatus_F == 1)
  {
    motorR.setSpeed(0);
    motorL.setSpeed(0);
    motorL.run(RELEASE);
    motorR.run(RELEASE);
    motorR.setSpeed(velocityR);
    motorL.setSpeed(velocityL);
    motorL.run(BACKWARD);
    motorR.run(BACKWARD);
    delay(100);
    motorR.setSpeed(0);
    motorL.setSpeed(0);
    motorL.run(RELEASE);
    motorR.run(RELEASE);
    delay(100);
    motorR.setSpeed(velocityR);
    motorL.setSpeed(velocityL);
    motorL.run(FORWARD);
    motorR.run(BACKWARD);
    delay(100);
  }
  /////////////// Serial Commands //////////////////////////////////////////////////
  if (Serial.available() > 0)
  {
    cmd = Serial.read();
    if (cmd == 'F' )
    {
      delay(30);
      motorR.setSpeed(velocityR);
      motorL.setSpeed(velocityL);
      motorR.run(FORWARD);
      motorL.run(FORWARD);
    }
    else if (cmd == 'B')
    {
      delay(30);
      motorR.setSpeed(velocityR);
      motorL.setSpeed(velocityL);
      motorR.run(BACKWARD);
      motorL.run(BACKWARD);
    }
    else if (cmd == 'R')
    {
      delay(30);
      motorR.setSpeed(velocityR);
      motorL.setSpeed(velocityL);
      motorR.run(BACKWARD);
      motorL.run(FORWARD);
    }
    else if (cmd == 'L')
    {
      delay(30);
      motorR.setSpeed(velocityR);
      motorL.setSpeed(velocityL);
      motorL.run(BACKWARD);
      motorR.run(FORWARD);
    }
    else if (cmd == 'S')
    {
      motorR.setSpeed(0);
      motorL.setSpeed(0);
      motorL.run(RELEASE);
      motorR.run(RELEASE);
    }
    else     if (cmd == 'V' )
    {
      Serial.print("\n\rEnter velocity (0-255):");
      while (Serial.available() == 0) {};
      velocity = Serial.parseInt();
      Serial.print("\n\rVelocity = ");
      Serial.println(velocity);

    }
    else
    {}
  }
}
