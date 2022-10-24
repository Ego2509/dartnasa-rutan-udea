const int rxPin = 15; //Pin de recepción
const int txPin = 14; //Pin transmisión

String Dat;
float Vel,X,Y;
int i;
String Shoot;

void setup() {
 
   Serial.begin(9600); // Monitor serial para corroborar botón presionado
}

void loop() {
  
  //While para recibir parametros iniciales de la app
  while(1){
    if(Serial.available()>0){ 
      Dat = Serial.readString();
      //Serial.println(Dat);
  
      // Se envia pos de X y Y inicial
      if(Dat.startsWith("P")){
         i=Dat.indexOf(",");
         X = Dat.substring(1,i).toFloat();
         Y = Dat.substring(i+1).toFloat();
         Serial.println(X);
         Serial.println(Y);
      }
  
      // Se envía la velocidad del meteorito
      if(Dat.startsWith("V")){
        Vel = Dat.substring(1).toFloat();
        Serial.println(Vel);
      }
  
      // Se mueve hacia la derecha
      if(Dat.startsWith("R")){
        Serial.println("Right");
        break;
      }
      // Se mueve hacia la izquierda
      if(Dat.startsWith("L")){
        Serial.println("Left");
        break;
      }
      // Se mueve hacia arriba
      if(Dat.startsWith("U")){
        Serial.println("Up");
        break;
      }
      // Se mueve hacia abajo
      if(Dat.startsWith("D")){
        Serial.println("Down");
        break;
      }
      
    }
  }

  //While para iniciar movimiento
  while(1){
    if(Serial.available()>0){ 
      Shoot = Serial.read();
      if(Shoot=="49"){
        Serial.println("Shooter robot!");
        break;
      }
    }
   }
}  
  
  
