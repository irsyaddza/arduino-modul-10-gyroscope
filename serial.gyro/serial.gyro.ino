#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

void setup() {
  Serial.begin(9600);         // Mulai komunikasi serial
  Wire.begin();               // Mulai komunikasi I2C
  mpu.initialize();           // Inisialisasi sensor MPU6050

  if (mpu.testConnection()) {
    Serial.println("MPU6050 berhasil terhubung.");
  } else {
    Serial.println("MPU6050 tidak terhubung!");
    while (1);  // Hentikan jika tidak terhubung
  }
}

void loop() {
  // Variabel untuk menyimpan data sensor
  int16_t ax, ay, az;         // Data accelerometer
  int16_t gx, gy, gz;         // Data gyroscope

  // Baca data accelerometer dan gyroscope
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  // Tampilkan data accelerometer
  Serial.print("Accelerometer: ");
  Serial.print("X = "); Serial.print(ax);
  Serial.print(" | Y = "); Serial.print(ay);
  Serial.print(" | Z = "); Serial.println(az);

  // Tampilkan data gyroscope
  Serial.print("Gyroscope: ");
  Serial.print("X = "); Serial.print(gx);
  Serial.print(" | Y = "); Serial.print(gy);
  Serial.print(" | Z = "); Serial.println(gz);

  Serial.println("-----------------------------");
  delay(500);  // Tunggu 500ms sebelum pembacaan berikutnya
}

//no 1