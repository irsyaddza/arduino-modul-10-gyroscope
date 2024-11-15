# 🕹️ IMPLEMENTASI SENSOR GYROSCOPE PADA ARDUINO UNO
![Arduino](https://img.shields.io/badge/Arduino-00979D?style=for-the-badge&logo=Arduino&logoColor=white)
![Sensors](https://img.shields.io/badge/Sensor-Gyroscope-blue?style=for-the-badge)
![Versi](https://img.shields.io/badge/Versi-1.0-green?style=for-the-badge)

## 📋 Gambaran Proyek
Sistem berbasis Arduino yang memanfaatkan sensor giroskop untuk mendeteksi pergerakan dan rotasi. Menyediakan umpan balik visual, audio, dan pemantauan serial melalui beragam mode operasi yang dikendalikan oleh tombol tekan.

### 🔧 Komponen yang Digunakan
- Board Arduino
- Sensor Giroskop
- Layar LCD (I2C)
- Push Button
- LED
- Buzzer

### Software
1. **Library yang Diperlukan**
   ```cpp
   #include <Wire.h>
   #include <LiquidCrystal_I2C.h>
   #include <MPU6050.h>
   ```
   
## 📊 Detail Mode

### Mode 1: Pemantauan
- Pengukuran giroskop kontinu
- Refresh rate: 500ms
- Format LCD: "Kecepatan Sudut: XXX °/s"
- Output serial: "Angular Velocity: XXX °/s"

### Mode 2: Peringatan
- Ambang batas default: 45 °/s
- Pola buzzer: Terus-menerus
- Pesan peringatan di LCD
- Log kejadian di serial

### Mode 3: Visualisasi LED
- Pemetaan PWM: 0-255
- Hubungan terbalik dengan kecepatan
- Efek redup halus
- Tampilan kecepatan real-time
