// Libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// radio pins
#define CE 7
#define CSN 8

RF24 radio(CE, CSN); // reciever object

// radio address
const byte address[6] = "00001";

void setup() {
 
  // set baud rate for serial communication
  Serial.begin(9600);
 
  // Initialize reciever 
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void loop() {
  // Create an array to store the received values
  float data[4];

  if (radio.available()) {
    // Read the data into the array
    radio.read(&data, sizeof(data));
    Serial.write((byte*)data, sizeof(data));
  }
}