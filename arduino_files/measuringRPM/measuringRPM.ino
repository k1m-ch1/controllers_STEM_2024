#define IN1 4
#define IN2 5
#define EN 3
#define INTERRUPT_PIN 2 //definition of IN1, IN2, EN , digital interrupt pins

unsigned int pwmOutput = 0;
unsigned int prevTime = millis();
unsigned int count = 0;
void setup() {
  Serial.begin(115200); //initializing the serial monitor
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(EN, OUTPUT); //setting IN1, IN2, EN as output
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW); //spinning the motor in one direction
  analogWrite(EN, pwmOutput); //setting the pwm output (initially 0)
  attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), increaseCount , RISING); // only trigger interrupt on RISING edge
  
}

void loop() {
  if (Serial.available() > 0){
    pwmOutput = Serial.parseInt();
    analogWrite(EN, pwmOutput); // if are bytes in the serial buffer, parse int and write it to the EN pin
  }
  if (millis() - prevTime > 1000){
    Serial.print("PWM: ");
    Serial.print(pwmOutput);
    Serial.print("count per second: ");
    Serial.println(count);
    count = 0;
    prevTime = millis();    
  }
}

void increaseCount(){
  count++;
}
