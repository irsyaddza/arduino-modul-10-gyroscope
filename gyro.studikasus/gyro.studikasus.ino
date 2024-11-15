#include <Wire.h>
#include <MPU6050.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);  // Alamat LCD, sesuaikan sesuai dengan LCD Anda
MPU6050 mpu;

const int buttonPin = 7;  // Pin push button
const int buzzerPin = 8;  // Pin buzzer
const int ledPin = 9;     // Pin LED untuk PWM

int buttonState = 0;
int lastButtonState = 0;
int mode = 0;
int threshold = 10000;  // Batas nilai gyroscope untuk peringatan (disesuaikan)
int16_t gx, gy, gz;     // Data gyroscope

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);

  lcd.init();
  lcd.backlight();

  Serial.begin(9600);
  Wire.begin();
  mpu.initialize();

  if (mpu.testConnection()) {
    Serial.println("MPU6050 Terhubung.");
  } else {
    Serial.println("MPU6050 Gagal Terhubung!");
    while (1)
      ;
  }
}

void loop() {
  // Baca status tombol
  buttonState = digitalRead(buttonPin);

  // Ubah mode setiap kali tombol ditekan
  if (buttonState != lastButtonState) {
    if (buttonState == HIGH) {
      mode++;
      if (mode > 3) mode = 1;  // Kembali ke mode 1 setelah mode 3
      delay(500);              // Debounce
    }
  }
  lastButtonState = buttonState;

  // Baca data dari gyroscope
  mpu.getRotation(&gx, &gy, &gz);

  switch (mode) {
    case 1:
      // Mode 1: Tampilkan data gyroscope di LCD dan Serial Monitor
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Gyro X: ");
      lcd.print(gx);
      lcd.setCursor(0, 1);
      lcd.print("Gyro Y: ");
      lcd.print(gy);
      Serial.print("Mode 1 - Gyro X: ");
      Serial.print(gx);
      Serial.print(" | Gyro Y: ");
      Serial.print(gy);
      Serial.print(" | Gyro Z: ");
      Serial.println(gz);
      delay(500);
      break;

    case 2:
      // Mode 2: Aktifkan buzzer jika nilai gyroscope melebihi threshold
      if (abs(gx) > threshold || abs(gy) > threshold || abs(gz) > threshold) {
        digitalWrite(buzzerPin, HIGH);  // Aktifkan buzzer
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Warning!");
        lcd.setCursor(0, 1);
        lcd.print("Gyro Over Limit");
        Serial.println("Mode 2 - Warning! Gyro Over Limit");
      } else {
        digitalWrite(buzzerPin, LOW);  // Matikan buzzer
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Gyro Normal");
        lcd.setCursor(0, 1);
        lcd.print("X: ");
        lcd.print(gx);
        lcd.print(" Y: ");
        lcd.print(gy);
        Serial.print("Mode 2 - Gyro X: ");
        Serial.print(gx);
        Serial.print(" | Gyro Y: ");
        Serial.print(gy);
        Serial.print(" | Gyro Z: ");
        Serial.println(gz);
      }
      delay(500);
      break;

    case 3:
      // Mode 3: Gunakan nilai gyroscope untuk kontrol LED PWM
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("LED PWM: ");
      int ledPWM = map(abs(gx), 0, 32768, 0, 255);  // Map nilai gyroscope ke nilai PWM
      analogWrite(ledPin, ledPWM);
      lcd.setCursor(0, 1);
      lcd.print("Gyro X: ");
      lcd.print(gx);
      Serial.print("Mode 3 - LED PWM Value: ");
      Serial.println(ledPWM);
      delay(500);
      break;
  }
}