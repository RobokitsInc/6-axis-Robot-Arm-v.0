// Libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// Servo Constants
#define SERVO_FREQ 50 // Servo frequency in Hz
#define SERVO_MIN 90 // Minimum pulse width in counts
#define SERVO_MAX 480 // Maximum pulse width in counts

// servo variables
const int servoCount = 4;
int servoPins[servoCount] = {1, 2, 12, 14};
float servoAngle[servoCount];
float servoSpeed = 1; 

// radio constants
#define CE 7
#define CSN 8

// Objects
Adafruit_PWMServoDriver pca = Adafruit_PWMServoDriver(); // PCA9685 object
RF24 radio(CE,CSN);

const byte address[6] = "00001";

void setup() {
  // Initialize PCA9685 module
  pca.begin();
  pca.setPWMFreq(SERVO_FREQ);

  // set servos to 90 degrees
  for (int i = 0; i < servoCount; i++) {
    servoAngle[i] = 90;
    pca.setPWM(servoPins[i], 0, map(servoAngle[i], 0, 180, SERVO_MIN, SERVO_MAX));
  }

  // initialize reciever
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void loop() {

  // store recieved data in an array
  float data[4];

  // check if data is available
  if (radio.available()) {
    
    // recieve data
    radio.read(&data, sizeof(data));

    // Assign the values to the corresponding variables
    float valX1 = data[0];
    float valY1 = data[1];
    float valX2 = data[2];
    float valY2 = data[3];

    // adjust recieved values to servo speed
    float adjX1 = map(valX1, 0, 1020, -servoSpeed, servoSpeed);
    float adjY1 = map(valY1, 0, 1020, -servoSpeed, servoSpeed);
    float adjX2 = map(valX2, 0, 1020, -servoSpeed, servoSpeed);
    float adjY2 = map(valY2, 0, 1020, -servoSpeed, servoSpeed);

    Serial.println(servoAngle[0]);

    // increment servo angle 
    servoAngle[0] += adjX1;  // bottom of the arm
    servoAngle[1] -= adjX1; 
    servoAngle[2] += adjY1; // mid section
    servoAngle[3] -= adjY1;

    // constrain servo angles from 0 to 180
    for (int i = 0; i < servoCount; i++) {
      servoAngle[i] = constrain(servoAngle[i], 0, 180);
    }

    // assign the angles to the servos
    for (int i = 0; i < servoCount; i++) {
      pca.setPWM(servoPins[i], 0, map(servoAngle[i], 0, 180, SERVO_MIN, SERVO_MAX));
    }
  }
}