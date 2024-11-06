#include <Wire.h>
#include <Servo.h>

#define SLAVE_ADDRESS 3  // Slave address for Board 2

Servo m3;
int angle1;
int angle3 = 90;
int angle3_next;

void setup(){
  m3.attach(3);
  m3.write(angle3);
  Wire.begin(SLAVE_ADDRESS); // Join I2C bus as slave
  Wire.onReceive(receiveEvent); // Register receive event
  Wire.onRequest(requestEvent); // Register request event
  delay(2000);
}



void loop(){
  angle3 = m3.read();
  angle3_next = ceil(0.2*angle1)+ceil(0.8*angle3);
  m3.write(angle3_next);
  delay(1000);
}


void receiveEvent(int howMany) {
  int receivedValue;
  Wire.readBytes((char *)&receivedValue, sizeof(receivedValue)); // Read the value sent by master
  angle1 = receivedValue; // Store the received value
}

void requestEvent() {
  Wire.write((byte *)&angle3, sizeof(angle3)); // Send the current value back to the master
}