#include <MPU6050_light.h>
#include <Wire.h>
#include <Servo.h>

MPU6050 gyro1(Wire);
MPU6050 gyro2(Wire);

Servo servo1; int servo1_pin = 3;
Servo servo2; int servo2_pin = 5;

Servo servo3; int servo3_pin = 6;
Servo servo4; int servo4_pin = 9;

//Servo servo5; int servo5_pin = 10;

int Gyro2_pin = 2;
int Gyro1_pin = 8;

float* coord_ptr;
float* coord_ptr2;

void setup() {

  pinMode(Gyro2_pin, OUTPUT);
  pinMode(Gyro1_pin, OUTPUT);
  digitalWrite(Gyro2_pin, HIGH);
  digitalWrite(Gyro1_pin, LOW);

  gyro2.setAddress(0x69);

  Wire.begin();
  
  gyro1.begin();
  gyro1.calcOffsets();

  gyro2.begin();
  gyro2.calcOffsets();
  
  Serial.begin(9600);
  
}

void loop() {
  
  coord_ptr = AnglesGyro1(20);
  
  BottomArmAngle(*(coord_ptr));

  coord_ptr2 = AnglesGyro2(20);

  TopArmAngle(*(coord_ptr2)); 

  Serial.println(*(coord_ptr2));

  delay(10);  

}

void BottomArmAngle(int baseAngle){

  baseAngle = baseAngle;

  servo1.attach(servo1_pin);
  servo1.write(baseAngle);

  servo2.attach(servo2_pin);
  servo2.write(180-(baseAngle));

  delay(20);
    
}

void TopArmAngle(int TopAngle){

  TopAngle = TopAngle;

  servo3.attach(servo3_pin);
  servo3.write(TopAngle);

  servo4.attach(servo4_pin);
  servo4.write(180-(TopAngle));

  delay(20);
    
}

float* AnglesGyro1(int Delay) {
  gyro1.update();
  static float Gyro1array[3];
  Gyro1array[0] = gyro1.getAngleX();
  Gyro1array[1] = gyro1.getAngleY();
  Gyro1array[2] = gyro1.getAngleZ();
  delay(Delay);
  return Gyro1array;
}

float* AnglesGyro2(int Delay) {
  gyro2.update();
  static float Gyro2array[3];
  Gyro2array[0] = gyro2.getAngleX();
  Gyro2array[1] = gyro2.getAngleY();
  Gyro2array[2] = gyro2.getAngleZ();
  delay(Delay);
  return Gyro2array;
}
