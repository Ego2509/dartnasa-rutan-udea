#include <Servo.h>
//#include <math.h>
Servo S_01;  //BASE
Servo S_02;  //HOMBRO


double theta=0; //angulo de la base al objetivo (x)
double alfa=0; //angulo del hombro al objetivo (y)
double distancia_r = 2.10; //distancia servo(10cm)+servo_tablero(2m)
double distancia_r2 = distancia_r*distancia_r; //distancia servo-tablero
double d = 0; //distancia servo-objetivo
double ar = 0.207; //altura piso al robot (metros)

double velocidad_asteroide=0.08;//en metros. (80mm/s)

double tiempo_objetivo = (1/velocidad_asteroide)*0.6; // 1 metro en horizontal, cambiar para vertical
double xa=velocidad_asteroide*tiempo_objetivo; //x objetivo de asteroide a donde se dispararA


double rad_deg(double angle_rad) return angle_rad*180/PI;
void sm_hombro(double in_angle_deg);
void sm_base(double in_angle_deg, bool dir_derecha);
void base_setup();

void setup() {
  S_01.attach(5);//base
  S_02.attach(6);//hombro
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
 
  //esperando coneccion (bluetooth) bool para no repetir
  //esperando params de asteroide
  //esperando senal de inicio de asteriode()
    //iniciar reloj()
    //apuntar
    //ir mirando reloj para disparar
      //disparar
  //reinicia loop
    //base_setup() orientar al centro inicialmente

  d=sqrt(xa*xa + distancia_r2);
  alfa = atan((0.6-ar)/d); // 0.6 fue la altura del centro que se utilizo
  //puede variar si va para arriba
  sm_hombro(rad_deg(alfa));
  delay(100);
  theta= atan(xa/distancia_r);
  sm_base(rad_deg(theta),true);
  delay(100);
}


void sm_hombro(double in_angle_deg){
  int angle=(int)round(in_angle_deg);
  (in_angle>90)?
  S_02.write(90)
  :
  S_02.write(180-in_angle);
}

void sm_base(double in_angle_deg, bool dir_derecha){
  int angle=(int)round(in_angle_deg)
  (dir_derecha)?
    S_01.write(90-angle)
    :
    S_01.write(90+angle);
}

void base_setup(){
  #define THETA_INIT 90
  S_01.write(THETA_INIT); //siempre, porque sino las funciones del servo no funcionan
  //debe calibrarse en el centro siempre
  
  #define ALPHA_INIT 169
  S_02.write(ALPHA_INIT); //basado en el centro de nuestro tablero, osea calibrado.
  delay(10000); //[pruebas] para permitir rayar el punto. Pero no puede ser 0.
}
