#include "DHT.h" 
#include <SPI.h> 
#include <SD.h>
#include <Wire.h>
#include "RTClib.h"

#define DHTPIN 2 // pin yang digunakan untuk input data dari sensor dht 11
#define DHTTYPE DHT11 // kalian bisa mengganti DHT11 dengan DHT 22 / DHT 21, tergantung sensor yang kalian gunakan
DHT dht(DHTPIN, DHTTYPE);
File myFile;
RTC_DS3231 rtc;
char daysOfTheWeek[7][12] = {"Ahad", "Senin", "Selasa", "Rabu", "Kamis", "Jum'at", "Sabtu"};

void setup() 
{
 Serial.begin(9600);
 Serial.println("Data Logger Starting . . . !");
 dht.begin();
 delay(1000);
 Serial.println("Membuka Micro SD . . .");
 delay(1000);
 if (!SD.begin(4)) 
 {
 Serial.println("Gagal Membuka Micro SD!");
 return;
 }
 Serial.println("Berhasil Membuka Micro SD");
 delay(1000);
 Serial.println("Memerikasa Koneksi RTC . . .");
 delay(1000);
 if (! rtc.begin()) 
 {
 Serial.println("RTC tidak ditemukan");
 return;
 }
 Serial.println("Koneksi RTC Berhasil");

 if (rtc.lostPower()) 
 {
 Serial.println("Sett time RTC");
 rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));//sett waktu RTC sesuai waktu di PC saat uploud sketch
 }
 
 
}

void loop() 
{
 DateTime now = rtc.now();
 delay(2000);
 float h = dht.readHumidity();
 float t = dht.readTemperature(); // baca temperatur dalam celcius, jika ingin mengganti fahrenheit kalian bisa menggunakan float f = dht.readTemperature(true);
 

 // cek apakah koneksi dht 11 benar, jika salah print error
 if (isnan(h) || isnan(t))
 {
 Serial.println("Failed to read from DHT sensor!");
 return;
 }

 // Kirim data ke SD card 
 myFile = SD.open("logger.txt", FILE_WRITE); //Membuka File test.txt
 if (myFile) // jika file tersedia tulis data
 {
 Serial.print(now.year(), DEC);
 Serial.print('/');
 Serial.print(now.month(), DEC);
 Serial.print('/');
 Serial.print(now.day(), DEC);
 Serial.print(" (");
 Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
 Serial.print(") ");
 Serial.print(now.hour(), DEC);
 Serial.print(':');
 Serial.print(now.minute(), DEC);
 Serial.print(':');
 Serial.print(now.second(), DEC); 
 Serial.print(" Kelembapan: ");
 Serial.print(h);
 Serial.print(" %\t");
 Serial.print("Temperature: ");
 Serial.println(t); // menampilkan temperatur di serial monitor
 
 myFile.print(now.year(), DEC);
 myFile.print('/');
 myFile.print(now.month(), DEC);
 myFile.print('/');
 myFile.print(now.day(), DEC);
 myFile.print(" (");
 myFile.print(daysOfTheWeek[now.dayOfTheWeek()]);
 myFile.print(") ");
 myFile.print(now.hour(), DEC);
 myFile.print(':');
 myFile.print(now.minute(), DEC);
 myFile.print(':');
 myFile.print(now.second(), DEC); 
 myFile.print(" Kelembapan: ");
 myFile.print(h);
 myFile.print(" %\t");
 myFile.print("Temperature: ");
 myFile.println(t); // menulis data temperatur di MicroSD
 myFile.close();
 }
 else 
 {
 Serial.println("gagal membuka test.txt"); // jika gagal print error
 }
 delay(2000); //memberi jeda 5 detik, karena proses pengiriman data berlangsung selama 3 detik, jadi total 5 detik
}
