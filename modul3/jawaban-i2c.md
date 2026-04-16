# Jawaban Praktikum 3.6.4: Inter-Integrated Circuit (I2C)

## 1. Cara Kerja Komunikasi I2C Arduino ke LCD
I2C menggunakan dua kabel: **SDA (Serial Data)** dan **SCL (Serial Clock)**.
* **Master (Arduino):** Mengirimkan sinyal "Start" diikuti dengan **Alamat I2C** LCD (misal 0x27).
* **Addressing:** Hanya perangkat dengan alamat 0x27 yang akan merespons.
* **Data Transfer:** Arduino mengirimkan instruksi (seperti posisi kursor atau karakter teks) dalam bentuk paket 8-bit. Pin SCL mengatur detak sinkronisasi pengiriman setiap bit tersebut.
* **LCD I2C Adapter:** Modul PCF8574 di belakang LCD menerjemahkan data serial I2C menjadi data paralel agar dipahami oleh driver LCD HD44780.

---

## 2. Analisis Potensiometer (Pin Kiri vs Kanan)
Pin potensiometer berfungsi sebagai pembagi tegangan (*voltage divider*).
* **Jika Tertukar:** Secara fungsional tidak merusak alat. Namun, **arah putarannya akan terbalik**. 
* **Efek:** Biasanya putar kanan (searah jarum jam) meningkatkan nilai ADC. Jika tertukar, putar kanan justru akan menurunkan nilai ADC menuju 0.

---

## 3. Modifikasi Program (UART + I2C Terintegrasi)
Berikut kode untuk menampilkan data ke Serial Monitor dan LCD secara bersamaan:

```cpp
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Ganti alamat jika perlu (Ox27 / Ox20) 
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int pinPot = A0;

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
}

void loop() {

  int adc = analogRead(pinPot); // Membaca nilai ADC (0 - 1023)

  float volt = adc * 5.0 / 1023.0; // Konversi ADC ke tegangan (0–5V)

  int persen = map(adc, 0, 1023, 0, 100); // Konversi ADC ke persen (0–100%)

  int bar = map(adc, 0, 1023, 0, 16); // Mapping untuk bar LCD (0–16 karakter)

  // =========================
  // SERIAL MONITOR (UART)
  // =========================
  Serial.print("ADC: ");
  Serial.print(adc);
  Serial.print(" | Volt: ");
  Serial.print(volt);
  Serial.print(" V | Persen: ");
  Serial.print(persen);
  Serial.println("%");

  // =========================
  // LCD BARIS 1
  // =========================
  lcd.setCursor(0, 0); // posisi baris 0 kolom 0
  lcd.print("ADC:");
  lcd.print(adc);
  lcd.print(" ");
  lcd.print(persen);
  lcd.print("% ");

  // =========================
  // LCD BARIS 2 (BAR LEVEL)
  // =========================
  lcd.setCursor(0, 1); // posisi baris 1 kolom 0

  for (int i = 0; i < 16; i++) {
    if (i < bar) {
      lcd.print((char)255); // blok penuh (bar)
    } else {
      lcd.print(" "); // kosong
    }
  }

  delay(200); // jeda agar tampilan stabil
}
```

---

## 4. Tabel Pengamatan Pada Serial Monitor 
| ADC | Volt (V) | Persen (%) |
|-----|----------|------------|
| 1   | 0.00     | 0%         |
| 21  | 0.10     | 2%         |
| 49  | 0.24     | 5%         |
| 74  | 0.36     | 7%         |
| 96  | 0.47     | 9%         |