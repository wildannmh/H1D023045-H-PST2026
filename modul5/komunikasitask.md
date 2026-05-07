# Jawaban Praktikum 5.6.4: Komunikasi Task

## 1. Apakah kedua task berjalan secara bersamaan atau bergantian? Jelaskan mekanismenya!
Kedua task (`read_data` dan `display`) berjalan secara **bergantian** menggunakan mekanisme antrean (*Queue*).

**Mekanismenya:**
Task `read_data` bertugas sebagai *Producer* yang mengirimkan data ke dalam Queue menggunakan `xQueueSend`. Sementara itu, task `display` bertugas sebagai *Consumer* yang menunggu data menggunakan `xQueueReceive`. Jika Queue kosong, task `display` akan masuk ke status *Blocked* (menunggu), memberikan kesempatan bagi task `read_data` untuk berjalan. Setelah data tersedia, scheduler akan membangunkan task `display` untuk memproses data tersebut.

---

## 2. Apakah program ini berpotensi mengalami race condition? Jelaskan!
**Tidak.** Program ini relatif aman dari *race condition* karena menggunakan **Queue** bawaan FreeRTOS. 
Queue di FreeRTOS dirancang secara *thread-safe*. Artinya, mekanisme internal FreeRTOS sudah menangani sinkronisasi sehingga dua task tidak dapat mengakses atau memodifikasi memori Queue pada saat yang bersamaan secara tidak teratur. Setiap akses ke data dalam antrean dilindungi oleh sistem *critical section* di dalam kernel.

---

## 3. Modifikasi program dengan sensor DHT sesungguhnya
Untuk membuat data menjadi dinamis, kita perlu mengintegrasikan library `DHT.h`. Berikut adalah potongan kodenya:

```cpp
//tambahkan dht
#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT22 //di wokwi pakai dht22
DHT dht(DHTPIN, DHTTYPE);

void read_data(void *pvParameters) {
  struct readings x;
  dht.begin();
  for(;;) {
    x.temp = dht.readTemperature();
    x.h = dht.readHumidity();
    
    // Kirim data hanya jika pembacaan valid
    if (!isnan(x.temp) && !isnan(x.h)) {
      xQueueSend(my_queue, &x, portMAX_DELAY);
    }
    vTaskDelay(2000 / portTICK_PERIOD_MS); // Pembacaan sensor setiap 2 detik
  }
}
```