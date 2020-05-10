/*
 * Smart Irrigation System with Arduino
 * A project by
 * - Aditya Raj, 17BCI0095
 * - SNSN Datta, 17BCI0139
 */

#include <DHT.h>

#define DHTAPIN A0
#define DHTTYPE DHT11
#define MHAPIN A2
//#define LDRAPIN A4
#define MOTORPIN 2

DHT dht(DHTAPIN, DHTTYPE);

int dht_value = 0;
int mh_value = 0;
//int ldr_value = 0;
bool flag = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  dht.begin();
  pinMode(DHTAPIN, INPUT_PULLUP);
  pinMode(MHAPIN, INPUT_PULLUP);
  //pinMode(LDRAPIN, INPUT_PULLUP);
  pinMode(MOTORPIN, OUTPUT);
}

void dht_loop(float h, float tc) {
  if(h < 25.00) {
    digitalWrite(MOTORPIN, HIGH);
    flag = true;
  }
  else {
    digitalWrite(MOTORPIN, LOW);
    flag = false;
  }
  if(h < 50.00 && tc > 45.00) {
    digitalWrite(MOTORPIN, HIGH);
    flag = true;
  }
  else {
    digitalWrite(MOTORPIN, LOW);
    flag = false;
  }
}

void mh_loop(int moisture) {
  if(moisture < 25) {
    digitalWrite(MOTORPIN, HIGH);
    flag = true;
  }
  else {
    digitalWrite(MOTORPIN, LOW);
    flag = false;
  }
}

/*void ldr_loop(int ldr_value) {
  if(ldr_value > 700) {
    digitalWrite(MOTORPIN, HIGH);
    delay(3000);
    digitalWrite(MOTORPIN, LOW);
    flag = false;
  }
  else {
    digitalWrite(MOTORPIN, LOW);
    flag = false;
  }
  delay(5000);
}*/

void loop() {
  // put your main code here, to run repeatedly:
  dht_value = analogRead(DHTAPIN);
  float h = dht.readHumidity();
  float tc = dht.readTemperature();
  float tf = dht.readTemperature(true); //as Fahrenheit
  mh_value = analogRead(MHAPIN);
  int moisture = map(mh_value, 1025, 245, 0, 100);
  //ldr_value = analogRead(LDRAPIN);
  bool result1 = false, result2 = false;
  Serial.print("\nHumidity: ");
  Serial.print(h);
  Serial.println("%");
  Serial.print("Temperature: ");
  Serial.print(tc); 
  Serial.print("C\t");
  Serial.print(tf); 
  Serial.println("F");
  Serial.print("Moisture value: ");
  Serial.print(moisture);
  Serial.println("%");
  //Serial.print("LDR value: ");
  //Serial.println(ldr_value);
  dht_loop(h, tc);
  mh_loop(moisture);
  /*if(flag == false) {
    ldr_loop(ldr_value);
  }*/
  delay(2000);
}
