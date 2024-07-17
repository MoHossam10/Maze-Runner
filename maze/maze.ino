#include "AFMotor.h"
#define IRSensorR A0
#define IRSensorF A3
AF_DCMotor motorR (2);
AF_DCMotor motorL (1);
int IRSensorStatus_R, IRSensorStatus_Old_R = 0;
int IRSensorStatus_F, IRSensorStatus_Old_F = 0;
int cmd;

void setup () {
  Serial.begin(9600);
  Serial.setTimeout(5);
  pinMode (IRSensorR, INPUT);
  pinMode (IRSensorF, INPUT);
}
  
void loop() {
  ////////////////////// IR Sensor //////////////////////////////////////////////////
  int IRSensorStatus_R = digitalRead (IRSensorR) ; 
  int IRSensorStatus_F = digitalRead (IRSensorF) ;
  // if (IRSensorStatus_F == 0 && IRSensorStatus_F != IRSensorStatus_Old_F)
  if (IRSensorStatus_F == 0 )
  {
    Serial.println("F Wall Detected.");
    IRSensorStatus_Old_F = IRSensorStatus_F;
    motorR.setSpeed(64);
    motorL.setSpeed(64);
    motorR.run(FORWARD);
    motorL.run(BACKWARD);
  }
  else
  {
    if (IRSensorStatus_R == 0 && IRSensorStatus_R != IRSensorStatus_Old_R)
    //if (IRSensorStatus_R == 0)
    {
      Serial.println("R Wall Detected.");
      IRSensorStatus_Old_R = IRSensorStatus_R;
      motorR.setSpeed (128);
      motorL.setSpeed (128);
      motorR.run(FORWARD);
      motorL.run(FORWARD);
    }
    else if (IRSensorStatus_R == 1 && IRSensorStatus_R != IRSensorStatus_Old_R)
    // else if (IRSensorStatus_R == 1)
    {
      Serial.println("R Empty space Detected.");
      IRSensorStatus_Old_R = IRSensorStatus_R;
      motorR.setSpeed(64);
      motorL.setSpeed(64);
      motorR.run(BACKWARD);
      motorL.run(FORWARD);
    }
    
    /*else if (IRSensorStatus_R == 1 && IRSensorStatus_L == 1)
    {
      Serial.println("F/R Empty space Detected.");
      motorR.setSpeed(44);
      motorL.setSpeed(64);
      motorR.run(BACKWARD);
      motorL.run(FORWARD);
    }*/
     else
     {}
  }

  ///////////////////////////// Serial Commands ///////////////////////////////////////
  if (Serial.available() > 0)
  {
    cmd = Serial.read();
  }
  if (cmd == 'F')
  {
    delay(30);
    motorR.setSpeed(64);
    motorL.setSpeed(64);
    motorR.run(FORWARD);
    motorL.run(FORWARD);
  }

  else if (cmd == 'B')
  {
    delay(30);
    motorR.setSpeed(64);
    motorL.setSpeed(64);
    motorR.run(BACKWARD);
    motorL.run(BACKWARD);
  }
  else if (cmd == 'R')
  {
    delay(30);
    motorR.setSpeed(64);
    motorL.setSpeed(64);
    motorR.run(BACKWARD);
    motorL.run(FORWARD);
  }
  else if (cmd == 'L')
  {
    delay(30);
    motorR.setSpeed(64);
    motorL.setSpeed(64);
    motorL.run(BACKWARD);
    motorR.run(FORWARD);
  }
  else if (cmd == 'S')
  {
    delay(30);
    motorR.setSpeed(0);
    motorL.setSpeed(0);
    motorR.run(RELEASE);
    motorL.run(RELEASE);
  }
  else
  {}
}
