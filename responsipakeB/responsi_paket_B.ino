#include <Servo.h>

Servo myservo;

const int btnPin = 2;
const int ledPin = 8;
const int servoPin = 9;

bool lastUpState = HIGH;
int pos = 0;

void setup() {

  pinMode(btnPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  myservo.attach(servoPin);

  Serial.begin(9600);

}

void loop() {
  bool upState = digitalRead(btnPin);

  if(lastUpState == HIGH && upState == LOW)
  {
    digitalWrite(ledPin, HIGH);
    myservo.write(90);
    Serial.print("DRS: ACTIVE");
  }

  Serial.print("DRS: CLOSED");
  delay(1000);

  lastUpState = upState;
}