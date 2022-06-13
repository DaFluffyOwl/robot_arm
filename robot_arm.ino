#include <MPU6050_light.h>
#include <Wire.h>
#include <Servo.h>

MPU6050 gyro1(Wire);
MPU6050 gyro2(Wire);

Servo servoX; int servoX_pin = 5;
Servo servoY; int servoY_pin = 3;
Servo servoY2; int servoY2_pin = 9;
Servo servoZ; int servoZ_pin = 6;

int MAX_Y = 170;
int MIN_Y = 35;
const int y_const = 30;

int bufferY = 0;
int bufferX = 0;
int bufferZ = 0;

int Gyro2_pin = 11;
int Gyro1_pin = 4;

float* coord_ptr;
float* coord_ptr2;

void setup() {

  servoX.attach(servoX_pin);
  servoY.attach(servoY_pin);
  servoY2.attach(servoY2_pin);
  servoZ.attach(servoZ_pin);

  pinMode(Gyro1_pin, OUTPUT);
  digitalWrite(Gyro1_pin, LOW);

  gyro1.setAddress(0x68);

  gyro1.begin();
  gyro1.calcOffsets(0, 0);

  pinMode(Gyro2_pin, OUTPUT);
  digitalWrite(Gyro2_pin, HIGH);

  gyro2.setAddress(0x69);

  gyro2.begin();
  gyro2.calcOffsets(0, 0);

  Wire.begin();
  Serial.begin(9600);

}

void loop() {

  coord_ptr = AnglesGyro1(10);
  coord_ptr2 = AnglesGyro2(10);

  if(bufferY - *coord_ptr2 < 200){
    if(*coord_ptr2 > MAX_Y){
      servoY.write(MAX_Y + y_const);
      servoY2.write(180 - MAX_Y - y_const);
    }
    else if(*coord_ptr2 < MIN_Y){
      servoY.write(MIN_Y + y_const);
      servoY2.write(180 - MIN_Y - y_const);
    }
    else{
      servoY.write(*(coord_ptr2) + y_const);
      servoY2.write(180 - *(coord_ptr2) - y_const);
    }
    bufferY = *coord_ptr2;
  }
  else{
    servoY.write(bufferY + y_const);
    servoY2.write(180 - bufferY - y_const);
  }

  float mapped_X = 0;
  if(*(coord_ptr2 + 2) < 0){
    mapped_X = -1 * *(coord_ptr2 + 2);
  }
  else{
    mapped_X = *(coord_ptr2 + 2);
  }
  if(bufferX - mapped_X < 200){
    servoX.write(mapped_X);
    bufferX = mapped_X;
    Serial.println(mapped_X);
  } else {
    servoX.write(bufferX);
    Serial.println(bufferX);
  }

  if(bufferZ - *(coord_ptr) < 200){
    servoZ.write(*(coord_ptr));
    bufferZ = *(coord_ptr);
  } else {
    servoZ.write(bufferZ);
  }

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
