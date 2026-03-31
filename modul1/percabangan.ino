const int ledPin = 13;     // Menentukan pin LED pada pin digital 13
int timeDelay = 1000;     // Delay awal (LED berkedip lambat)

void setup() { 
  pinMode(ledPin, OUTPUT);   // Mengatur pin LED sebagai output
}

void loop() { 
  // Menyalakan LED
  digitalWrite(ledPin, HIGH);  
  delay(timeDelay);           // Menunggu sesuai nilai delay (LED ON)

  // Mematikan LED
  digitalWrite(ledPin, LOW);  
  delay(timeDelay);           // Menunggu sesuai nilai delay (LED OFF)

  // Percabangan untuk mengatur perubahan kecepatan LED
  if (timeDelay <= 200) {     
    // Jika delay sudah sangat kecil (LED sangat cepat)
    timeDelay = 500;          
    // Ubah menjadi kecepatan sedang

  } else if (timeDelay <= 500) {  
    // Jika delay berada pada kecepatan sedang
    timeDelay = 0;            
    // Ubah menjadi mati (tidak berkedip)

  } else {  
    // Jika LED masih dalam kondisi lambat
    timeDelay -= 200;         
    // Kurangi delay agar LED semakin cepat
  }

  // Kondisi untuk menghentikan program
  if (timeDelay == 0) {
    digitalWrite(ledPin, LOW); // Pastikan LED benar-benar mati
    while(true);               // Menghentikan program secara permanen
  }
}