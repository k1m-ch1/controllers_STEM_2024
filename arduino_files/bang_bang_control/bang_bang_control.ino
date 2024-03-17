#include <TimerOne.h>

#define IN1 4
#define IN2 5
#define EN 3
#define INTERRUPT_PIN 2 //definition of IN1, IN2, EN , digital interrupt pins

unsigned int pwmOutput = 0;
unsigned int startTime = millis();
unsigned int count = 0;
unsigned int sampleRate = 20;
unsigned int setPoint = 0; //speed in RPM
void setup() {
  Serial.begin(115200); //initializing the serial monitor
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(EN, OUTPUT); //setting IN1, IN2, EN as output
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW); //spinning the motor in one direction
  analogWrite(EN, pwmOutput); //setting the pwm output (initially 0)
  attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), increaseCount , RISING); // only trigger interrupt on RISING edge
  
  Timer1.initialize(1000000/sampleRate);
  Timer1.attachInterrupt(printCount);
  
}

void loop() {
  if (Serial.available() > 0){
    setPoint = Serial.parseInt();
  }
}

void printCount(){
  Timer1.detachInterrupt();
  int rpm = (count*sampleRate)*3;
  if (rpm < setPoint){
    digitalWrite(EN, HIGH);
  }
  else{
    digitalWrite(EN, LOW);
  }
  // Serial.print("Setpoint: ");
  Serial.print(setPoint);
  Serial.print(", ");
  // Serial.print(", State: ");
  Serial.print(rpm < setPoint);
  // Serial.print(", rpm: ");
  Serial.print(", ");
  Serial.println(rpm);
  count = 0;
  Timer1.attachInterrupt(printCount);
}

void increaseCount(){
  count++;
}
