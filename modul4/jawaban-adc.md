# Jawaban Praktikum 4A: Analog to Digital Converter (ADC)

## 1. Apa fungsi perintah `analogRead()` pada rangkaian praktikum ini?
Fungsi `analogRead()` digunakan untuk membaca tegangan input analog dari pin tertentu (dalam hal ini pin A0 yang terhubung ke potensiometer). Mikrokontroler Arduino Uno memiliki ADC 10-bit, sehingga fungsi ini mengubah tegangan input (0V - 5V) menjadi nilai digital diskrit dalam rentang **0 hingga 1023**. Nilai inilah yang kemudian digunakan oleh program untuk menentukan posisi servo.

---

## 2. Mengapa diperlukan fungsi `map()` dalam program tersebut?
Fungsi `map()` diperlukan karena adanya perbedaan rentang (resolusi) antara input ADC dan output kendali servo:
- **Input ADC:** Memiliki rentang nilai 0 sampai 1023.
- **Output Servo:** Library `Servo.h` menggunakan derajat sudut dengan rentang 0 sampai 180.

Fungsi `map()` melakukan penskalaan linear sehingga nilai potensiometer yang dibaca dapat dikonversi secara proporsional ke sudut servo yang sesuai.

---

## 3. Modifikasi Program (Rentang 30° - 150°)
Berikut adalah potongan kode pada bagian yang di modifikasi:

```cpp
// ===================== KONVERSI DATA =====================
  // Ubah nilai ADC menjadi sudut servo (30–150 derajat) modifikasi
  pos = map(val,
             0,   // isi nilai minimum ADC
             1023,   // isi nilai maksimum ADC
             30,   // isi sudut minimum servo
             150);  // isi sudut maksimum servo

  // ===================== OUTPUT SERVO =====================
  // Gerakkan servo sesuai hasil mapping
  myservo.write(pos); // isi dengan variabel sudut
```
**Penjelasan:**
Dengan mengubah parameter target pada fungsi map() dari (0, 180) menjadi (30, 150), maka saat potensiometer berada di titik minimum (0), servo akan berada di posisi 30°. Saat potensiometer di titik maksimum (1023), servo akan berada di posisi 150°. Ini berguna untuk membatasi gerak mekanik agar tidak menabrak pembatas atau sesuai kebutuhan desain sistem.
