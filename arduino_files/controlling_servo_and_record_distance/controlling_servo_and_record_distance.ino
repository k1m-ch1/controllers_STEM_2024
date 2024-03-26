#include <Servo.h>
#include <HCSR04.h>


const unsigned int sampleInterval = 1000;

HCSR04 hc(11, 12);// trig pin, echo pin

Servo myServo;

unsigned int currentDistance;
unsigned int count = 0;
int angleRange[2] = {80, 120};
unsigned long prevTime = millis();
unsigned long currentTime;

void isrServo(){
  currentDistance = hc.dist();//get the current distance
  Serial.print(currentDistance);
  myServo.write(angleRange[count%2]);
  Serial.print(" ,");
  Serial.print(count);
  Serial.print(" ,");
  Serial.println(angleRange[count%2]);
  count++;
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("code started");
  myServo.attach(9);
  Serial.println("servo attached");
}

void loop() {
  // put your main code here, to run repeatedly:
  currentTime = millis();
  if (currentTime - prevTime > sampleInterval){
    isrServo();
    prevTime = millis();
  }
}
