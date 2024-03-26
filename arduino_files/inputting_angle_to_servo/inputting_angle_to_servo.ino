#include <Servo.h>

Servo myServo;
int desiredAngle = 90;
int currentAngle = desiredAngle;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  myServo.attach(9);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0){
    desiredAngle = Serial.parseInt();
  }
  if (desiredAngle > currentAngle){
    currentAngle ++;
  }
  else if (desiredAngle < currentAngle){
    currentAngle --;
  }
  myServo.write(currentAngle);
  delay(10);
}
