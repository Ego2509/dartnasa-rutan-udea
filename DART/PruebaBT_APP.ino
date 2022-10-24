

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
