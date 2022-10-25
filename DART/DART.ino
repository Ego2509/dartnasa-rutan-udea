#include <Servo.h>
#define THETA_INIT 88
#define ALPHA_INIT 169

//#include <math.h>
Servo S_01;  //BASE
Servo S_02;  //HOMBRO


double theta=0; //angulo de la base al objetivo (x)
double alfa=0; //angulo del hombro al objetivo (y)
double distancia_r_alpha = 2.34;//distancia servo(10cm)+servo_tablero(2m) // servo hombro
double distancia_r_theta=2.16;//base
// double distancia_r2_theta = distancia_r_theta*distancia_r_theta; 
double distancia_r2_alpha = distancia_r_alpha*distancia_r_alpha; //distancia servo-tablero
double d_theta = 0; //distancia servo-objetivo
double d_alpha = 0; //distancia laser-objetivo
double ar = 0.175; //altura piso al robot (metros)

double velocidad_asteroide=0.08;//en metros. (80mm/s)

double x_ast=0;
double y_ast=0.6;

//double tiempo_objetivo = (1/velocidad_asteroide)*0.6; // 1 metro en horizontal, cambiar para vertical
double xa=0.4*x_ast + 0.6; //x objetivo de asteroide a donde se dispararA



double rad_deg(double angle_rad){return angle_rad*180/PI;};
void sm_hombro(double in_angle_deg);
void sm_base(double in_angle_deg, bool dir_derecha);
void base_setup();



void setup() {
  S_01.attach(5);//base
  S_02.attach(6);//hombro

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
 
  //esperando coneccion (bluetooth) bool para no repetir

  //esperando params de asteroide
  //esperando senal de inicio de asteriode()
    //iniciar reloj()
    //apuntar
    //ir mirando reloj para disparar
      //disparar
  //reinicia loop
    //base_setup() orientar al centro inicialmente

  //d_theta=sqrt(xa*xa + distancia_r2_theta);
  d_alpha=sqrt(xa*xa + distancia_r2_alpha);
  alfa = atan((y_ast-ar)/d_alpha); // 0.6 fue la altura del centro que se utilizo
  Serial.println(rad_deg(alfa));
  //puede variar si va para arriba
  sm_hombro(rad_deg(alfa));
  theta= atan(xa/distancia_r_theta);
  sm_base(rad_deg(theta),true);
}


void sm_hombro(double in_angle_deg){
  int angle=(int)round(in_angle_deg);
  (angle>=90)?
  S_02.write(90):
  (angle==0)?
  S_02.write(179):
  S_02.write(180-angle);
}

void sm_base(double in_angle_deg, bool dir_derecha){
  int angle=(int)round(in_angle_deg);
  (dir_derecha)?
    S_01.write(THETA_INIT-angle): S_01.write(THETA_INIT+angle);
}

void base_setup(){
  S_01.write(THETA_INIT); //siempre, porque sino las funciones del servo no funcionan
  //debe calibrarse en el centro siempre
  S_02.write(ALPHA_INIT); //basado en el centro de nuestro tablero, osea calibrado.
  delay(10000); //[pruebas] para permitir rayar el punto. Pero no puede ser 0.
}
