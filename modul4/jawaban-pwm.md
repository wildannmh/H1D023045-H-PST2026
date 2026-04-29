# Jawaban Praktikum 4B: Pulse Width Modulation (PWM)

## 1. Jelaskan mengapa LED dapat diatur kecerahannya menggunakan fungsi `analogWrite()`!
LED dapat diatur kecerahannya karena fungsi `analogWrite()` menggunakan teknik **PWM (Pulse Width Modulation)**. PWM bekerja dengan cara memutus dan menyambungkan aliran listrik (ON-OFF) dengan frekuensi yang sangat cepat sehingga tidak tertangkap oleh mata manusia. Dengan mengatur *Duty Cycle* (perbandingan waktu ON terhadap total satu periode), tegangan rata-rata yang diterima LED berubah. Semakin besar *duty cycle*-nya, semakin lama LED dalam kondisi ON, sehingga terlihat lebih terang.

---

## 2. Apa hubungan antara nilai ADC (0–1023) dan nilai PWM (0–255)?
Hubungannya adalah **linearitas dengan skala 4:1**. 
- ADC pada Arduino Uno memiliki resolusi 10-bit (0-1023).
- PWM pada Arduino Uno memiliki resolusi 8-bit (0-255).
Untuk memetakan nilai input menjadi output yang sebanding, nilai ADC harus dibagi 4 (atau dipetakan menggunakan fungsi `map`). Artinya, setiap kenaikan 4 satuan pada ADC akan menaikkan 1 satuan pada nilai PWM.

---

## 3. Modifikasi Program (Rentang PWM 50 - 200)
Berikut adalah logika untuk membatasi kecerahan LED pada rentang sedang:

```cpp
// ===================== PEMROSESAN DATA (SCALING) =====================
  // Ubah nilai ADC (0–1023) menjadi nilai PWM (50–200) modifikasi
  pwm = map(nilaiADC,
            0,   // isi nilai minimum ADC
            1023,   // isi nilai maksimum ADC
            50,   // isi PWM minimum
            200);  // isi PWM maksimum

  // ===================== OUTPUT PWM =====================
  // Kirim sinyal PWM ke LED (mengatur kecerahan)
  analogWrite(ledPin, pwm); // isi dengan variabel PWM
```

**Penjelasan:**
Pada modifikasi ini, parameter output pada fungsi map() diatur ke 50 (sebagai batas redup minimum) dan 200 (sebagai batas terang maksimum). Hasilnya, meskipun potensiometer diputar hingga mentok ke kiri atau kanan, LED tidak akan pernah mati total (min 50) dan tidak akan mencapai kecerahan maksimalnya (max 200), menjaga intensitas cahaya tetap di rentang menengah.
