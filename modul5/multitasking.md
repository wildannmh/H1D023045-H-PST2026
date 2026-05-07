# Jawaban Praktikum 5.5.4: Multitasking

## 1. Apakah ketiga task berjalan secara bersamaan atau bergantian? Jelaskan mekanismenya!
Secara teknis, pada mikrokontroller dengan *single-core* seperti Arduino Uno (ATmega328P), ketiga task berjalan secara **bergantian** namun dalam waktu yang sangat cepat sehingga terlihat seolah-olah berjalan secara bersamaan (*concurrent*).

**Mekanismenya:**
FreeRTOS menggunakan sistem **Preemptive Scheduling**. Scheduler akan memberikan jatah waktu (*time-slicing*) kepada setiap task berdasarkan prioritasnya. Ketika satu task sedang berada dalam kondisi `vTaskDelay`, scheduler akan mengalihkan CPU untuk mengerjakan task lain yang sedang dalam status *Ready*. Proses perpindahan antar task ini disebut dengan *Context Switching*.

---

## 2. Bagaimana cara menambahkan task keempat? Jelaskan langkahnya!
Untuk menambahkan task keempat dilakukan dengan cara seperti berikut:
1.  **Deklarasi Fungsi Task:** Buat prototipe fungsi di bagian atas program, misalnya: `void TaskBaru( void *pvParameters );`.
2.  **Implementasi Fungsi:** Buat definisi fungsi task tersebut dengan loop `while(1)` di dalamnya dan pastikan menggunakan `vTaskDelay` agar tidak memonopoli CPU.
3.  **Registrasi Task:** Panggil fungsi `xTaskCreate()` di dalam `void setup()` untuk memasukkan task tersebut ke dalam scheduler.
    Contoh: 
    ```cpp
    xTaskCreate(TaskBaru, "Task4", 128, NULL, 1, NULL);
    ```

---

## 3. Modifikasi program dengan menambah sensor potensiometer untuk mengontrol kecepatan LED
Berikut adalah logika modifikasi kode untuk membaca nilai potensiometer dan menggunakannya sebagai parameter delay:

```cpp
#include <Arduino_FreeRTOS.h>

void TaskBlink1(void *pvParameters);
void TaskBlink2(void *pvParameters);
void Taskprint(void *pvParameters);

//pin potensiometer
const int potPin = A0;

//variabel global
int delayLed1 = 200;
int delayLed2 = 300;

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

  xTaskCreate(
    TaskBlink1,
    "task1",
    128,
    NULL,
    1,
    NULL
  );

  xTaskCreate(
    TaskBlink2,
    "task2",
    128,
    NULL,
    1,
    NULL
  );

  xTaskCreate(
    Taskprint,
    "task3",
    128,
    NULL,
    1,
    NULL
  );

  vTaskStartScheduler();
}

void loop() {
}

void TaskBlink1(void *pvParameters) {
  pinMode(8, OUTPUT);

  while (1) {
    // membaca nilai potensiometer
    int potValue = analogRead(potPin);

    // mengubah nilai menjadi delay
    delayLed1 = map(potValue, 0, 1023, 50, 1000);

    Serial.print("Task1 Delay : ");
    Serial.println(delayLed1);

    digitalWrite(8, HIGH);
    vTaskDelay(delayLed1  / portTICK_PERIOD_MS);

    digitalWrite(8, LOW);
    vTaskDelay(delayLed1  / portTICK_PERIOD_MS);
  }
}

void TaskBlink2(void *pvParameters) {
  pinMode(7, OUTPUT);

  while (1) {
    // membaca nilai potensiometer
    int potValue = analogRead(potPin);

    // mengubah nilai menjadi delay
    delayLed2 = map(potValue, 0, 1023, 100, 1500);

    Serial.print("Task2 Delay : ");
    Serial.println(delayLed2);

    digitalWrite(7, HIGH);
    vTaskDelay(delayLed2 / portTICK_PERIOD_MS);

    digitalWrite(7, LOW);
    vTaskDelay(delayLed2 / portTICK_PERIOD_MS);
  }
}

void Taskprint(void *pvParameters) {
  int counter = 0;

  while (1) {
    counter++;

    Serial.println(counter);

    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}
```