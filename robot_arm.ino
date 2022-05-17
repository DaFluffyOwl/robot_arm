#include <MPU6050_light.h>
#include <Wire.h>

// Stops the code from self destruction ¯_(ツ)/¯.
MPU6050 gyro(Wire);

int AD0 = 7; // Connect to the AD0 pin on GY521.
int angle = 0;

void setup() {

Wire.begin(); // Starts I2C communication hardware in Arduino to talk with the GY521 (MPU6050) using the I2C bus.
setup_gyro();
 
pinMode(AD0, OUTPUT);
digitalWrite(AD0, HIGH); // Sets address for the GY521 (HIGH -> 0x69, LOW -> 0x68). Each GY521 needs a different address.

Serial.begin(9600);

}

void loop() {
  get_angles(0x69, 50);

}


void setup_gryo(int index){
  gyro.begin(); // "Wakes up" the MPU6050 and sets both the gyroscope and accelerometer configurations.
  gyro.calcOffests(); // Calculate offsets to remove them.
  pinMode(index, OUTPUT);
  if(index = 1){
    digitalWrite(index, LOW);
  }
  else if(index = 2){
    digitalWrite(index, HIGH);
  }
  else{
    Serial.print("Invalid adress");
  }
}
void get_angles(int address, int Delay){
  gyro.setAddress(address); // Following code is sent only to the GY521 with address whatever
  gyro.update();
  Serial.println("X: "); //Updates data
  Serial.print(gyro.getAngleX()); // Retrieves raw data from the MPU6050 and preforms calculations to get the proper angle measurment.
  Serial.println("Y: ");
  Serial.println(gyro.getAngleY());
  Serial.println("Z: ");
  Serial.print(gyro.getAngleZ());
  delay(Delay);
}
