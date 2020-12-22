#include <Arduino.h>

// Setar entradas e saídas:
const int sensorsecundaria = 2;
const int sensorpedestre = 3;

const int Led1PrincipalVermelho =  6; 
const int Led2PrincipalAmarelo =  7;
const int Led3PrincipalVerde =  8;     

const int Led4SecundariaVermelho =  9;
const int Led5SecundariaAmarelo =  10;
const int Led6SecundariaVerde =  11;

const int Led7PedestreVermelho =  12; 
const int Led8PedestreVerde =  13;

void setup() {
  // put your setup code here, to run once:
  
// Inicializando entradas:
  pinMode(sensorsecundaria, INPUT);
  pinMode(sensorpedestre, INPUT);

// Inicializando saídaS:
  pinMode(Led1PrincipalVermelho, OUTPUT);
  pinMode(Led2PrincipalAmarelo, OUTPUT);
  pinMode(Led3PrincipalVerde, OUTPUT);

  pinMode(Led4SecundariaVermelho, OUTPUT);
  pinMode(Led5SecundariaAmarelo, OUTPUT);
  pinMode(Led6SecundariaVerde, OUTPUT);

  pinMode(Led7PedestreVermelho, OUTPUT);
  pinMode(Led8PedestreVerde, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:



}