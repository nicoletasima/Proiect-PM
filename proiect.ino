#include <AFMotor.h>
#include <NewPing.h>
#include <Servo.h>

#define ECHO A0
#define TRIGGER A1
#define MAX_DISTANCE 300
#define IR A5

AF_DCMotor motor1(1, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR34_1KHZ);

NewPing ultrasonic(TRIGGER, ECHO, MAX_DISTANCE);

Servo servomotor;

String command;

void setup() {
  Serial.begin(9600);
  servomotor.attach(10);
  servomotor.write(90);
  pinMode(IR, INPUT);

}

void loop() {
  // int distance = ultrasonic.ping_cm();
  // Serial.println(distance);
  // int IR_sensor = digitalRead(IR);
  // Serial.println(IR_sensor);
  
  if (Serial.available() > 0) {
    command = "";
    delay(2);
    command = Serial.readString();
    delay(2);
  }
  
  if (command == "left") {
    left();
  }

  if (command == "right") {
    right();
  }

  if (command == "stop") {
    Stop();
  }

  while (command == "forward") {
    forward();
  }

  while (command == "back") {
    backward();
  }

}

void forward() {
  int distance = ultrasonic.ping_cm();

  if (distance < 10) {
    Stop();
    command = "";
  } else {
    motor1.setSpeed(255);
    motor1.run(BACKWARD);
    motor3.setSpeed(255);
    motor3.run(FORWARD);
  }
}

void backward() {
  int IR_sensor = digitalRead(IR);
  Serial.println(IR_sensor);
  if (IR_sensor == LOW) {
    Stop();
    command = "";
  } else {
    motor1.setSpeed(255);
    motor1.run(FORWARD);
    motor3.setSpeed(255);
    motor3.run(BACKWARD);
  }
}

void right() {
  servomotor.write(0);
  delay(500);
  servomotor.write(90);
  delay(500);
  motor1.run(FORWARD);
  motor1.setSpeed(255);
  motor3.run(FORWARD);
  motor3.setSpeed(255);
  delay(400);
  motor1.run(RELEASE);
  motor3.run(RELEASE);
  command = "";
}

void left() {
  servomotor.write(180);
  delay(500);
  servomotor.write(90);
  delay(500);
  motor1.run(BACKWARD);
  motor1.setSpeed(255);
  motor3.run(BACKWARD);
  motor3.setSpeed(255);
  delay(400);
  motor1.run(RELEASE);
  motor3.run(RELEASE);
  command = "";
}

void Stop() {
  motor1.run(RELEASE);
  motor3.run(RELEASE);
}
