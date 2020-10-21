#include <Servo.h>

//Ultrasonic
int trigPin = 11; //Trig - green Jumper
int echoPin = 10; //Echo - yellow Jumper
int buka = 7;
int tutup = 6;

//servo
Servo palang; // create servo object to control a servo
int servoPinpalang = 3;
float jarak_kereta;

String statusnya = "buka";

void setup() {
  Serial.begin(115200);
  // put your setup code here, to run once:
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  palang.attach(servoPinpalang);
  palang.write(0);
  pinMode(buka, OUTPUT);
  pinMode(tutup, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  jarak_kereta = jarak();
  Serial.print("Jaraknya : ");
  Serial.println(jarak_kereta);
  if (jarak_kereta < 6) {
    if (statusnya == "buka") {
      palang.write(0);
      digitalWrite(buka, HIGH);
      digitalWrite(tutup, LOW);
      statusnya = "tutup";
      delay(50);
      digitalWrite(tutup, HIGH);
    }

  }
  if (jarak_kereta >= 6) {
    if (statusnya == "tutup") {
      palang.write(90);
      digitalWrite(buka, LOW);
      digitalWrite(tutup, HIGH);
      delay(50);
      digitalWrite(buka, HIGH);
      statusnya = "buka";
    }

  }
}

float jarak() {
  // Sensor dipicu oleh pulsa HIGH dari 10us atau lebih.
  // Berikan pulsa LOW pendek terlebih dahulu untuk memastikan pulsa HIGH bersih:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Baca sinyal dari sensor: pulsa HIGH yang
  // duration adalah waktu (dalam mikrodetik) dari pengirim
  // Dari ping untuk penerimaan Echo off dari sebuah objek.
  pinMode(echoPin, INPUT);
  long duration = pulseIn(echoPin, HIGH);
  // convert jarak kedalam cm dan meter
  long cm = (duration / 2) / 29.1;
  return cm;
}
