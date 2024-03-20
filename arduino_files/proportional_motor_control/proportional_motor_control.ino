#include <TimerOne.h>

#define IN1 4
#define IN2 5
#define EN 3
#define INTERRUPT_PIN 2 //definition of IN1, IN2, EN , digital interrupt pins

unsigned int pwmOutput = 0;
unsigned int startTime = millis();
unsigned int count = 0;
unsigned int sampleRate = 5;
unsigned int setPoint = 0; //speed in RPM
int prevError = 0;
long long accumError = 0;
const float kp = 1;
const float kd = 0.1;
const float ki = 5;
int dt = 1000/sampleRate;
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
  int error = setPoint - rpm;
  accumError += error;
  int output = kp * error + kd * (error - prevError)/dt + (ki * accumError/(millis()-startTime));
  // Serial.print("Setpoint: ");
  Serial.print(setPoint);
  Serial.print(", ");
  Serial.print(mappedOutput);
  Serial.print(", rpm: ");
  Serial.print(", ");
  Serial.println(rpm);
  count = 0;
  prevError = error;
  Timer1.attachInterrupt(printCount);
}

void increaseCount(){
  count++;
}
