#include <SPI.h>
#include <SD.h>
File myFile; 

void setup() 
{ // Buka KomunikasiSerial 
 Serial.begin(9600); 
 while (!Serial) // tunggu sampai serial terbuka, jika tidak menggunakan serial baris ini bisa dihapus saja 
 { 
 ; 
 } 
 Serial.println("membuka micro sd...");
 
 if (!SD.begin(4)) 
 { 
 Serial.println("initialization failed!"); 
 return;
 }
 
 // Buka File 
 myFile = SD.open("logger.txt"); 
 
 if (myFile)
 { Serial.println("logger.txt");
 
 // tunggu sampai file siap dibuka 
 while(myFile.available()) 
 { 
 Serial.write(myFile.read()); 
 }
 
 // menampilkan data ke serial monitor 
 Serial.println("berhasil menampilkan"); 
 myFile.close(); // tutup file 
 } 
 else 
 { 
 // jika gagal membuka print error 
 Serial.println("gagal membuka test.txt");
 } 
} 

void loop() 
 { 
 // nothing happens after setup 
 }
