#include <MPU6050_light.h>
#include <Wire.h>
#include <Servo.h>

// Stops the code from self destruction ¯_(ツ)/¯.
MPU6050 gyro1(Wire);
MPU6050 gyro2(Wire);
//int servoX_pin = 10;
//Servo servoX;

float* coord_ptr;
float* coord_ptr2;

void setup() {

  Wire.begin(); // Starts I2C communication hardware in Arduino to talk with the GY521 (MPU6050) using the I2C bus.
  setup_gyro1();
  setup_gyro2();
  
  //servoX.attach(servoX_pin);
  Serial.begin(9600);

}

void loop() {
  coord_ptr = get_angles1(0x68, 50);
  Serial.print("X: "); //Updates data
  Serial.print(*coord_ptr); // Retrieves raw data from the MPU6050 and preforms calculations to get the proper angle measurment.
  /*Serial.print("  Y: ");
  Serial.print(*(coord_ptr + 1));
  Serial.print("  Z: ");
  Serial.println(*(coord_ptr + 2));*/
  //servoX.write(*coord_ptr);
  coord_ptr2 = get_angles2(0x69, 50);
  Serial.print("  X2: ");
  Serial.println(*coord_ptr2);
}

/* ------- SETUP ------- */
void setup_gyro1() {
  gyro1.begin(); // "Wakes up" the MPU6050 and sets both the gyroscope and accelerometer configurations.
  gyro1.calcOffsets(); // Calculate offsets to remove them.
  pinMode(3, OUTPUT);
  digitalWrite(3, LOW);
}
void setup_gyro2() {
  gyro2.begin();
  gyro2.calcOffsets();
  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);
}

/* ------- GET ANGLES ------- */
float* get_angles1(int address, int Delay) {
  gyro1.setAddress(0x68); // Following code is sent only to the GY521 with address whatever
  gyro1.update();
  static float coord[3];
  coord[0] = gyro1.getAngleX();
  coord[1] = gyro1.getAngleY();
  coord[2] = gyro1.getAngleZ();
  delay(Delay);
  return coord;
}

float* get_angles2(int address, int Delay) {
  gyro2.setAddress(0x69);
  gyro2.update();
  static float coord[3];
  coord[0] = gyro2.getAngleX();
  coord[1] = gyro2.getAngleY();
  coord[2] = gyro2.getAngleZ();
  delay(Delay);
  return coord;
}
