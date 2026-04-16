# Jawaban Praktikum 3.5.4: Komunikasi Serial (UART)

## 1. Proses dari Input Keyboard hingga LED Menyala/Mati
Alur komunikasi data terjadi sebagai berikut:
1. **Input:** User mengetik karakter (misal '1') di Serial Monitor pada komputer.
2. **Transmisi:** Data dikonversi menjadi sinyal digital serial dan dikirim melalui kabel USB ke chip USB-to-Serial pada Arduino.
3. **Penerimaan (UART):** Pin RX pada mikrokontroler menerima bit-bit data tersebut. Data disimpan sementara di dalam *Hardware Serial Buffer*.
4. **Processing:** Fungsi `Serial.read()` mengambil karakter dari buffer. Struktur `if (data == '1')` memeriksa nilai tersebut.
5. **Output:** Jika cocok, instruksi `digitalWrite(PIN_LED, HIGH)` mengirim tegangan ke pin 13 (atau pin 8 sesuai wiring), sehingga LED menyala.

---

## 2. Fungsi `Serial.available()`
* **Tujuan:** Mengecek apakah ada data yang masuk ke buffer serial. Fungsi ini mengembalikan jumlah byte yang siap dibaca.
* **Jika Dihilangkan:** Program akan terus mengeksekusi `Serial.read()` di setiap iterasi `loop()`. Karena `read()` mengembalikan -1 jika buffer kosong, variabel `data` akan berisi karakter sampah atau nilai yang salah, menyebabkan Serial Monitor dipenuhi pesan "Perintah tidak dikenal" secara terus-menerus.

---

## 3. Modifikasi Program (Fitur Blink)
Berikut adalah kode yang dimodifikasi agar LED berkedip saat menerima input '2'.

```cpp
const int PIN_LED = 13;
// Cek apakah ada data dari komputer // Baca 1 karakter
char mode = '0';
// Variabel untuk menyimpan mode saat ini (default mati)

void setup() {
  Serial.begin(9600);
  Serial.println("Ketik '1' untuk menyalakan LED, '0' untuk mematikan LED, '2' untuk BLINK"); 
  pinMode (PIN_LED, OUTPUT);
}

void loop() {
  // Mengecek apakah ada data yang masuk dari Serial Monitor
  if (Serial.available() > 0) {
    char data = Serial.read(); // Membaca 1 karakter dari input serial

    // Jika input valid (bukan ENTER)
    if (data != '\n' && data != '\r') {
      mode = data;  // Simpan perintah ke variabel mode

      // Memberikan feedback ke user
      if (mode == '1') {
        Serial.println("LED ON");
      } 
      else if (mode == '0') {
        Serial.println("LED OFF");
      } 
      else if (mode == '2') {
        Serial.println("LED BLINK");
      } 
      else {
        Serial.println("Perintah tidak dikenal");
      }
    }
  }

  // Menjalankan aksi berdasarkan mode terakhir
  if (mode == '1') {
    digitalWrite(PIN_LED, HIGH); // Menyalakan LED
  } 
  else if (mode == '0') {
    digitalWrite(PIN_LED, LOW); // Mematikan LED
  } 
  else if (mode == '2') {
    digitalWrite(PIN_LED, HIGH); // LED nyala
    delay(500); // Tunggu 500 ms
    digitalWrite(PIN_LED, LOW); // LED mati
    delay(500); // Tunggu 500 ms
  }
}
```

---

## 4. Perbedaan `delay()` vs `millis()`
* `delay()` **(Blocking):** Menghentikan seluruh eksekusi program. Jika LED sedang delay 1 detik, Arduino tidak bisa membaca input serial baru sampai waktu selesai. Ini membuat sistem tidak responsif.

* `millis()` **(Non-blocking):** Menggunakan waktu internal sejak program berjalan. Arduino bisa terus mengecek input serial sambil tetap mengatur waktu kedipan LED. Rekomendasi: Gunakan `millis()` agar sistem tetap bisa menerima perintah "Stop" atau "Off" kapan saja.