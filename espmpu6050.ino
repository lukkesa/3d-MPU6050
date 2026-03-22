#include <MPU6050_tockn.h>
#include <Wire.h>

MPU6050 mpu6050(Wire);

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);
  mpu6050.begin();
  mpu6050.calcGyroOffsets(false);
}

void loop() {
  mpu6050.update();

 //sends raw data tu serial
  Serial.print(mpu6050.getAngleX());
  Serial.print(",");
  Serial.print(mpu6050.getAngleY());
  Serial.print(",");
  Serial.println(mpu6050.getAngleZ());

  delay(20);
}
