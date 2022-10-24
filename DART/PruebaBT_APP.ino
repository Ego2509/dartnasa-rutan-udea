
#include <SoftwareSerial.h>

int rxPin = 0; //Pin de recepción
int txPin = 1; //Pin transmisión
int pinLed = 13;

SoftwareSerial Bluetooth(1, 0);

char bt,Dir;
float Vel_meteoro;

void setup() {

  //Habilito módulo BT
  pinMode(pinLed,OUTPUT);

  
  // Configuración de seriales para comunicación 
  Serial.begin(9600); // Serial para comunicación con BT

}

void loop() {

  if(Serial.available()){
    Serial.println(Serial.readString());
  }
 
  
  
}
