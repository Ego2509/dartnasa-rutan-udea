#include <Servo.h>
Servo S_01;  //BASE
Servo S_02;  //HOMBRO
Servo disp;


#define G 9.8

const int pM1=11;
const int pM2 = 10;
const int finCar=17;
bool ban = false;
String Dat;
float Vel,X,Y;
int i;
String Shoot;double theta=0; //angulo de la base al objetivo (x)
double alfa=0; //angulo del hombro al objetivo (y)
double distancia_r = 2.12; //distancia servo(10cm)+servo_tablero(2m)
double distancia_r2 = distancia_r*distancia_r; //distancia servo-tablero
double d = 0; //distancia servo-objetivo
double ar = 0.25; //altura piso al robot (metros)

double velocidad_asteroide;//en metros. (80mm/s)
double x_ast,y_ast;
 // 1 metro en horizontal, cambiar para vertical
double xa; //x objetivo de asteroide a donde se dispararA

double vi = 7; //Velocidad inicial del proyectil 7m/s
double delta_y; //yfinal - yasteroide
double t_proyectil;
double Viy; // Velocidad inicial en y del proyectil

double t_ast;//Tiempo del asteroide
double delta_xast; //distancia a recorrer del asteroide



double rad_deg(double angle_rad){
  return angle_rad*180/PI;
  }

void sm_hombro(double in_angle_deg);
void sm_base(double in_angle_deg, bool dir_derecha);
void base_setup();



void setup() {
  S_01.attach(5);//base
  S_02.attach(6);//hombro
  disp.attach(7);

pinMode(pM1,OUTPUT);
pinMode(pM2,OUTPUT);
pinMode(finCar,INPUT);
  
  Serial.begin(9600);
  /*
    el servom de la base puede moverse de 0-180, pero
    hacia la derecha, el objetivo estaría en el rango de 90->0,
    hacia la izq., el objetivo estaría en el rango 90->180.

    el servom del hombro puede moverse de 180 a 90, pero
    en el rango 100->0 básicamente no sirve porque no avanza
    casi en dirección horizontal

     */
     base_setup();

}

void loop() { 
 //While para recibir parametros iniciales de la app

  while(1){
    posicionarDisparador();
    if(ban){
      break;
    }
  }


  while(0){
    if(Serial.available()>0){ 
      Dat = Serial.readString();
      //Serial.println(Dat);
  
      // Se envia pos de X y Y inicial
      if(Dat.startsWith("P")){
         i=Dat.indexOf(",");
         X = Dat.substring(1,i).toFloat();
         Y = Dat.substring(i+1).toFloat();
         x_ast=X;
         y_ast=Y;
         delta_y = y_ast - ar;
         
         
      }
  
      // Se envía la velocidad del meteorito
      if(Dat.startsWith("V")){
        Vel = Dat.substring(1).toFloat();
        velocidad_asteroide=Vel;
        
        }
  
      // Se mueve hacia la derecha
      if(Dat.startsWith("R")){
        xa = 0.4*x_ast + 0.6;
        posicionarse();
        break;
      }
      // Se mueve hacia la izquierda
      if(Dat.startsWith("L")){
        xa = 0.4*x_ast -0.6;
        posicionarse():
        break;
      }
      // Se mueve hacia arriba
      
     
      
    }
  }
  //esperando coneccion (bluetooth) bool para no repetir

  //esperando params de asteroide
  //esperando senal de inicio de asteriode()
    //iniciar reloj()
    //apuntar
    //ir mirando reloj para disparar
      //disparar
  //reinicia loop
    //base_setup() orientar al centro inicialmente

  //While para iniciar movimiento
  while(1){
    delta_xast = abs(x_ast - xa);
    t_ast = delta_xast/velocidad_asteroide;
    t
    if(Serial.available()>0){ 
      Shoot = Serial.read();
      if(Shoot=="49"){
       disp.write(30);
       ban=false;
        break;
      }
    }
   }
}

void posicionarse(){
  
  d=sqrt(xa*xa + distancia_r2);
  t_proyectil = d/vi;
  
  viy = (2*delta_y + G*(t_proyectil*t_proyectil))/(2*t_proyectil);
  
  alfa = asin(viy/vi);
  //alfa = atan((y_ast-ar)/d); // 0.6 fue la altura del centro que se utilizo
  Serial.println(rad_deg(alfa));
  //puede variar si va para arriba
  sm_hombro(rad_deg(alfa));

  theta= atan(xa/distancia_r);
  sm_base(rad_deg(theta),true);

  }

void sm_hombro(double in_angle_deg){
  int angle=(int)round(in_angle_deg);
  (angle>90)?
  S_02.write(90)
  :
  (angle<=179)?
  S_02.write(179)
  :
  S_02.write(180-angle);
}

void sm_base(double in_angle_deg, bool dir_derecha){
  int angle=(int)round(in_angle_deg);  
  (dir_derecha)?
    S_01.write(88-angle)
    :
    S_01.write(88+angle);
}

void base_setup(){
  #define THETA_INIT 81
  S_01.write(THETA_INIT); //siempre, porque sino las funciones del servo no funcionan
  //debe calibrarse en el centro siempre

  
  #define ALPHA_INIT 148
  S_02.write(ALPHA_INIT); //basado en el centro de nuestro tablero, osea calibrado.
  //delay(10000); //[pruebas] para permitir rayar el punto. Pero no puede ser 0.
}

void posicionarDisparador(){
  digitalWrite(pM1,HIGH);
  digitalWrite(pM2,LOW);
  disp.write(30);
  if(digitalRead(finCar) == HIGH){
    delay(1500);
    digitalWrite(pM1,LOW);
    digitalWrite(pM2,LOW);
    disp.write(100);
    delay(500);
    digitalWrite(pM1,LOW);
    digitalWrite(pM2,HIGH);
    delay(13000);   
    ban=true;
  } 

}
