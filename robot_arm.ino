#include <MPU6050_light.h>
#include <Wire.h>
#include <Servo.h>

MPU6050 gyro1(Wire);
MPU6050 gyro2(Wire);

Servo servoX; int servoX_pin = 5;
Servo servoY; int servoY_pin = 3;
Servo servoY2; int servoY2_pin = 9;
Servo servoZ; int servoZ_pin = 6;

int Gyro2_pin = 2;
int Gyro1_pin = 4;

float* coord_ptr;
float* coord_ptr2;

void setup() {

  servoX.attach(servoX_pin);
  servoY.attach(servoY_pin);
  servoY2.attach(servoY2_pin);
  servoZ.attach(servoZ_pin);

  pinMode(Gyro2_pin, OUTPUT);
  pinMode(Gyro1_pin, OUTPUT);
  digitalWrite(Gyro2_pin, HIGH);
  digitalWrite(Gyro1_pin, LOW);

  gyro1.setAddress(0x68);

  gyro1.begin();
  gyro1.calcOffsets();

  gyro2.setAddress(0x69);

  gyro2.begin();
  gyro2.calcOffsets();

  Wire.begin();
  
  /*servoX.write(180);
  servoY.write(180);
  servoZ.write(180);
  delay(1000);
  servoX.write(0);
  servoY.write(0);
  servoZ.write(0);
  delay(1000);*/
  Serial.begin(9600);
  
}

void loop() {
  
  coord_ptr = AnglesGyro1(20);

  coord_ptr2 = AnglesGyro2(20); 

  servoY.write(*(coord_ptr2));
  servoY2.write(180 - *(coord_ptr2));
  servoX.write(*(coord_ptr2+2));
  servoZ.write(*(coord_ptr));
  //Serial.println(*coord_ptr);
}

float* AnglesGyro1(int Delay) {
  gyro1.update();
  static float Gyro_array[3];
  Gyro_array[0] = gyro1.getAngleX();
  Gyro_array[1] = gyro1.getAngleY();
  Gyro_array[2] = gyro1.getAngleZ();
  delay(Delay);
  return Gyro_array;
}

float* AnglesGyro2(int Delay) {
  gyro2.update();
  static float Gyro_array[3];
  Gyro_array[0] = gyro2.getAngleX();
  Gyro_array[1] = gyro2.getAngleY();
  Gyro_array[2] = gyro2.getAngleZ();
  delay(Delay);
  return Gyro_array;
}
