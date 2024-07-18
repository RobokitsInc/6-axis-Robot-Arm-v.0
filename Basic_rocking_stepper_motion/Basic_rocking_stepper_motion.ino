#define X_stepPin 2
#define X_dirPin 5 
 
// place the cnc shield on the arduino
// put the stepper driver on the x-axis (remove all unused drivers, failure to do this will fry all drivers)
// plug in the stepper driver, red at the top
// plug in the arduino to your computer 
// run this arduino file
// before plugging in the power supply, make sure it reads 12 V
// turn off power supply, connect it to cnc board and power it on
// That's it! the motors should be running in one direction, stop for 1/10 of a sec and rotate the other way

void setup() {
  // Sets the two pins as Outputs
  pinMode(X_stepPin,OUTPUT); 
  pinMode(X_dirPin,OUTPUT); 

}

void loop() {
  digitalWrite(X_dirPin,HIGH);
  // Enables the motor to move in a particular direction
  // Makes 200 pulses for making one full cycle rotation
  for(int x = 0; x < 1000; x++) {
    digitalWrite(X_stepPin,HIGH); 
    delayMicroseconds(500);    // by changing this time delay between the steps we can change the rotation speed
    digitalWrite(X_stepPin,LOW); 
    delayMicroseconds(500); 
  }
  delay(100); // One second delay
  
  digitalWrite(X_dirPin,LOW); 
//Changes the rotations direction
// Makes 400 pulses for making two full cycle rotation
  for(int x = 0; x < 1000; x++) {
    digitalWrite(X_stepPin,HIGH);
    delayMicroseconds(500);
    digitalWrite(X_stepPin,LOW);
    delayMicroseconds(500);
  }
  delay(100);
}
