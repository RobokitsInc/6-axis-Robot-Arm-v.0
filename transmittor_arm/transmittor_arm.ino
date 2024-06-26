//Libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// Joystick Variables
int joyX1 = 0;
int joyY1 = 1;
int joyX2 = 2;
int joyY2 = 3;

// radio digital pins
#define CE 7
#define CSN 8

//transmittor object
RF24 radio(CE, CSN);

const byte address[6] = "00001";

void setup() {
  Serial.begin(9600);
  //initializing transmittor  
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void loop() {
  // Read the values from the joysticks
  double valX1 = analogRead(joyX1);  // X axis of the first joystick
  double valY1 = analogRead(joyY1);  // Y axis of the first joystick
  double valX2 = analogRead(joyX2);  // X axis of the second joystick
  double valY2 = analogRead(joyY2);  // Y axis of the second joystick

   // Create an array to store the values
  double data[4];
  data[0] = valX1;
  data[1] = valY1;
  data[2] = valX2;
  data[3] = valY2;

  Serial.println(data[0]);
  // Send the data to the receiver
  radio.write(&data, sizeof(data));

}