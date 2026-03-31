# Jawaban Praktikum 1.5.4 - Percabangan

## 1. Pada kondisi apa program masuk ke blok if?
Program akan masuk ke blok `if (timeDelay <= 200)` ketika nilai variabel `timeDelay` sudah mencapai angka 200 atau lebih kecil. Ini terjadi setelah beberapa kali iterasi di mana `timeDelay` dikurangi terus-menerus pada blok `else`.

---

## 2. Pada kondisi apa program masuk ke blok else?
Program masuk ke blok `else` selama kondisi pada `if` dan `else if` tidak terpenuhi. Dalam kode tersebut, ini berarti saat `timeDelay` masih bernilai lebih besar dari 500 (kondisi awal adalah 1000). Di blok ini, `timeDelay` dikurangi 200 setiap perulangan agar LED berkedip semakin cepat.

---

## 3. Apa fungsi dari perintah delay(timeDelay)?
Fungsi `delay(timeDelay)` digunakan untuk memberikan jeda waktu (dalam milidetik) agar program berhenti sejenak sebelum mengeksekusi baris kode berikutnya. Dalam konteks ini, ia menentukan durasi LED menyala (HIGH) dan mati (LOW), yang secara visual kita lihat sebagai kecepatan kedipan LED.

---

## 4. Modifikasi Program (cepat → sedang → mati)

### Kode Program
```cpp
const int ledPin = 13;   
int timeDelay = 200;     // Mulai dari cepat

void setup() { 
  pinMode(ledPin, OUTPUT); 
}

void loop() { 
  digitalWrite(ledPin, HIGH); 
  delay(timeDelay);      

  digitalWrite(ledPin, LOW);  
  delay(timeDelay);      

  if (timeDelay == 200) {     
    timeDelay = 500;          
  } 
  else if (timeDelay == 500) {  
    timeDelay = 1000;         
  } 
  else {  
    timeDelay = 0;            
  }

  if (timeDelay == 0) {
    digitalWrite(ledPin, LOW); 
    while(true);              
  }
}
```

---

### Penjelasan Kode
- Menentukan pin LED pada Arduino.
- Mengatur kecepatan awal LED.
- Mengatur pin sebagai output.
- Menyalakan dan mematikan LED.
- Mengatur delay untuk kecepatan LED.
- Mengubah kecepatan dari cepat → sedang → lambat → mati.
- Menghentikan program secara permanen.
