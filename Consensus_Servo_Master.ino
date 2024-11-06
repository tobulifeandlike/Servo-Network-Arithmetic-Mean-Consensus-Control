#include <Servo.h>
#include<Wire.h>

#define SLAVE_1_ADDRESS 2  // Address for Slave 1 (Board 2)
#define SLAVE_2_ADDRESS 3  // Address for Slave 2 (Board 3)

Servo m1;
int angle1 = 30;
int angle1_next;
int angle2;
int angle3;

void setup(){
  Serial.begin(9600);
  Wire.begin();
  m1.attach(3);
  m1.write(angle1);
  delay(2000);
}



void loop(){
  angle1 = m1.read();
  angle1_next = ceil(0.6*angle1);
  
  Wire.beginTransmission(SLAVE_1_ADDRESS);
  Wire.write((byte*) &angle1, sizeof(angle1));
  Wire.endTransmission();
  	
  // Request value from Slave 1
  Wire.requestFrom(SLAVE_1_ADDRESS, sizeof(int));
  if (Wire.available() == sizeof(int)) {
    int receivedValue1;
    Wire.readBytes((char *)&receivedValue1, sizeof(receivedValue1));
    angle2 = receivedValue1;
    angle1_next += ceil(0.2*receivedValue1);
  }

  // Send values to Slave 2
  Wire.beginTransmission(SLAVE_2_ADDRESS);
  Wire.write((byte *)&angle1, sizeof(angle1));
  Wire.endTransmission();
  
  // Request value from Slave 2
  Wire.requestFrom(SLAVE_2_ADDRESS, sizeof(int));
  if (Wire.available() == sizeof(int)) {
    int receivedValue2;
    Wire.readBytes((char *)&receivedValue2, sizeof(receivedValue2));
    angle3 = receivedValue2;
    angle1_next += ceil(0.2*receivedValue2);
  }
  
  m1.write(angle1_next);
  Serial.println(angle1_next);
  delay(1000);
}