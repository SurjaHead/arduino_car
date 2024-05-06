#include <Servo.h>
#include <AFMotor.h>
// #include <SoftwareSerial.h>
#define Echo A0
#define Trig A1
#define motor 10
#define Speed 500
#define spoint 103
char value;
int distance;
int Left;
int Right;
int L = 0;
int R = 0;
int L1 = 0;
int R1 = 0;
Servo servo;
AF_DCMotor M1(1);
AF_DCMotor M2(2);
AF_DCMotor M3(3);
AF_DCMotor M4(4);
// SoftwareSerial BTSerial(0,1);

// enum Direction { STOP, MOVE_FORWARD, MOVE_BACKWARD, LEFT, RIGHT };
// Direction currentDirection = STOP;

void setup() {
  Serial.begin(9600);
  // BTSerial.begin(9600);
  servo.attach(10);
  M1.setSpeed(Speed);
  M2.setSpeed(Speed);
  M3.setSpeed(Speed);
  M4.setSpeed(Speed);
}

void loop() {
  if (Serial.available() > 0) {
    char command = Serial.read();
    Serial.println(command);
    Serial.println("hi");

    // Handle key press
    if (command == 'w') {
      forward();
    } else if (command == 's') {
      backward();
    } else if (command == 'a') {
      left();
    } else if (command == 'd') {
      right();
    }
    else {
    // If no key is pressed, stop the car
    Stop();
    }
  }
  // if (Serial.available()) {
  //   Serial.write(bluetoothSerial.read());
  // }
}

// void applyDirection() {
//   switch (currentDirection) {
//     case STOP:
//       Stop();
//       break;
//     case MOVE_FORWARD:
//       forward();
//       break;
//     case MOVE_BACKWARD:
//       backward();
//       break;
//     case LEFT:
//       left();
//       break;
//     case RIGHT:
//       right();
//       break;
//   }
// }


void Obstacle() {
  distance = ultrasonic();
  if (distance <= 12) {
    Stop();
    backward();
    delay(100);
    Stop();
    L = leftsee();
    servo.write(spoint);
    delay(800);
    R = rightsee();
    servo.write(spoint);
    if (L < R) {
      right();
      delay(500);
      Stop();
      delay(200);
    } else if (L > R) {
      left();
      delay(500);
      Stop();
      delay(200);
    }
  } else {
    forward();
  }
}

void forward() {
  M1.run(FORWARD);
  M2.run(FORWARD);
  M3.run(FORWARD);
  M4.run(FORWARD);
}
void backward() {
  M1.run(BACKWARD);
  M2.run(BACKWARD);
  M3.run(BACKWARD);
  M4.run(BACKWARD);
}
void right() {
  M1.run(BACKWARD);
  M2.run(BACKWARD);
  M3.run(FORWARD);
  M4.run(FORWARD);
}
void left() {
  M1.run(FORWARD);
  M2.run(FORWARD);
  M3.run(BACKWARD);
  M4.run(BACKWARD);
}
void Stop() {
  M1.run(RELEASE);
  M2.run(RELEASE);
  M3.run(RELEASE);
  M4.run(RELEASE);
}

int rightsee() {
  servo.write(20);
  delay(800);
  Left = ultrasonic();
  return Left;
}
int leftsee() {
  servo.write(180);
  delay(800);
  Right = ultrasonic();
  return Right;
}

int ultrasonic() {
  digitalWrite(Trig, LOW);
  delayMicroseconds(4);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);
  long t = pulseIn(Echo, HIGH);
  long cm = t / 29 / 2; //time convert distance
  return cm;
}