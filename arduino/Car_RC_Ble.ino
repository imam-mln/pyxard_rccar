// Import library yang dibutuhkan
#include <SoftwareSerial.h>
SoftwareSerial HC05(0, 1); // (TX, RX)

// Menyimpan pin ke dalam variable
const int ena = 5;
const int in1 = 6;
const int in2 = 7;
const int in3 = 8;
const int in4 = 9; // motor B (kanan)
const int enb = 10; // motor B (kanan)

void setup() {
  // Memulai Bluetooth HC05 & Serial
  HC05.begin(9600);
  Serial.begin(9600);
  // Inisialisasi pin
  pinMode(ena,OUTPUT);
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  pinMode(enb,OUTPUT);
}

void loop() {
  if(HC05.available() > 0) {
    // Menyimpan data dari bluetooth
    char receive = HC05.read();
    // Jika data yang dikiri "S" maka Berhenti (Stop)
    if(receive == 'S') {
      motorRight(0, 0, 0);
      motorLeft(0, 0, 0);
    }
    // Jika data yang dikiri "F" maka Maju (Forward)
    if(receive=='F') {
      motorRight(1, 0, 100);
      motorLeft(1, 0, 100);
    }
    // Jika data yang dikiri "B" maka Mundur (Backward)
    if(receive=='B') { 
      motorRight(0, 1, 100);
      motorLeft(0, 1, 100);
    }
    // Jika data yang dikiri "R" maka Belok Kanan (Right)
    if(receive=='R') {
      motorRight(1, 0, 100);
      motorLeft(0, 0, 100);
    }
    // Jika data yang dikiri "L" maka Belok Kiri (Left)
    if(receive=='L') {
      motorRight(0, 0, 100);
      motorLeft(1, 0, 100);
    }
  }
  delay(25);
}

// Function untuk menggerakan motor kanan
int motorRight(int forward, int backward, int speed) {
  digitalWrite(in1, forward);
  digitalWrite(in2, backward);
  analogWrite(ena, speed);
}

// Function untuk menggerakan motor kiri
int motorLeft(int forward, int backward, int speed) {
  digitalWrite(in3, forward);
  digitalWrite(in4, backward);
  analogWrite(enb, speed);
}

