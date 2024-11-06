#include <Wire.h>
#include <Servo.h>

#define SLAVE_ADDRESS 2  // Slave address for Board 2

Servo m2;

int angle1;
int angle2 = 120;
int angle2_next;

void setup(){
  m2.attach(3);
  m2.write(angle2);
  Wire.begin(SLAVE_ADDRESS); // Join I2C bus as slave
  Wire.onReceive(receiveEvent); // Register receive event
  Wire.onRequest(requestEvent); // Register request event
  delay(2000);
}



void loop(){
  angle2 = m2.read();
  angle2_next = ceil(0.2*angle1)+ceil(0.8*angle2);
  m2.write(angle2_next);
  delay(1000);
}

void receiveEvent(int howMany) {
  int receivedValue;
  Wire.readBytes((char *)&receivedValue, sizeof(receivedValue)); // Read the value sent by master
  angle1 = receivedValue; // Store the received value
}

void requestEvent() {
  Wire.write((byte *)&angle2, sizeof(angle2)); // Send the current value back to the master
}