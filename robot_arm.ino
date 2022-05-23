#include <MPU6050_light.h>
#include <Wire.h>
#include <Servo.h>

// Stops the code from self destruction ¯_(ツ)/¯.
MPU6050 gyro(Wire);
int servoX_pin = 10;
Servo servoX;

int AD0 = 2; // Connect to the AD0 pin on GY521.
int angle = 0;

float* coord_ptr;
void setup() {

  Wire.begin(); // Starts I2C communication hardware in Arduino to talk with the GY521 (MPU6050) using the I2C bus.
  setup_gyro(1);

  //pinMode(AD0, OUTPUT);
  //digitalWrite(AD0, HIGH); // Sets address for the GY521 (HIGH -> 0x69, LOW -> 0x68). Each GY521 needs a different address.
  servoX.attach(servoX_pin);
  Serial.begin(9600);

}

void loop() {
  coord_ptr = get_angles(0x68, 50);
  Serial.print("X: "); //Updates data
  Serial.print(*coord_ptr); // Retrieves raw data from the MPU6050 and preforms calculations to get the proper angle measurment.
  Serial.print("  Y: ");
  Serial.print(*(coord_ptr + 1));
  Serial.print("  Z: ");
  Serial.println(*(coord_ptr + 2));
  servoX.write(*coord_ptr);
}


void setup_gyro(int index) {
  gyro.begin(); // "Wakes up" the MPU6050 and sets both the gyroscope and accelerometer configurations.
  gyro.calcOffsets(); // Calculate offsets to remove them.
  pinMode(index, OUTPUT);
  if (index == 1) {
    digitalWrite(3, LOW);
  }
  else if (index == 2) {
    digitalWrite(index, HIGH);
  }
  else {
    Serial.print("Invalid adress");
  }
}
float* get_angles(int address, int Delay) {
  gyro.setAddress(address); // Following code is sent only to the GY521 with address whatever
  gyro.update();
  static float coord[3];
  coord[0] = gyro.getAngleX();
  coord[1] = gyro.getAngleY();
  coord[2] = gyro.getAngleZ();
  delay(Delay);
  return coord;
}
