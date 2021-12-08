#include <Wire.h> //libreria de conexion serial
#include <Servo.h> //libreria de control servomotores
 // Seteo de servomotores
Servo   servo1base; 
Servo   servo1codo;

//Servo   servo2mano;
Servo   servo2base; 
Servo   servo2codo; 

//Servo   servo3mano;
Servo   servo3base;  
Servo   servo3codo;
    
//Servo   servo4mano;
Servo   servo4base;  
Servo   servo4codo;
Servo servocamara;

//pata 1
 // enlazado de control de servomotor con pin fisico
#define SERVO_CODO1             A0 //
#define SERVO_BASE1             A2 //
////pines pata 2
#define SERVO_CODO2             A3 //
#define SERVO_BASE2             8 //


////pines pata 3
#define SERVO_CODO3             2 //
#define SERVO_BASE3             4 //
//pata 4
#define SERVO_CODO4             5  //
#define SERVO_BASE4             7  //
//
#define SERVO_CAMARA            9
int tiempo = 200;
void setup()
 {

  Wire.begin(2); // Define direccion i2c del bus #2
  Wire.onReceive(receiveEvent); // registra evento
  Serial.begin(9600); // Inicia el puerto serie
   // iniciado de servomotores
   servo1base.attach(SERVO_BASE1);  
   servo1codo.attach(SERVO_CODO1); 

  
   servo2base.attach(SERVO_BASE2);  
   servo2codo.attach(SERVO_CODO2); 
//


servo3base.attach(SERVO_BASE3);  
servo3codo.attach(SERVO_CODO3);
//    
  
   servo4base.attach(SERVO_BASE4);  
   servo4codo.attach(SERVO_CODO4); 
//

servocamara.attach(SERVO_CAMARA);
   delay(200);
  
 
 }
void loop()
{
 // funcion de avance del sistema
//mover_adelante();
//mover_adelante_izquierda();
//mover_adelante_derecha();
//retroceder();
delay(100);
}
void receiveEvent(int howMany)
{
while(1 < Wire.available()) // recorre todos mientas se prodcue la detecion de dato en el bus
{
char c = Wire.read(); // recibe como un caracter
Serial.print(c); // imprime el caracter
}
char x = Wire.read(); // recibe un byte como un entero
Serial.println(x); // imprime el entero

if (x=='w') { // Si el byte es w se llama la funcion respectiva
  
mover_adelante();
Serial.println("avanzar");
delay(200);
  }


if (x=='s') {
retroceder();
Serial.println("Retroceder");

}
if (x=='a') {
mover_adelante_izquierda(); 
Serial.println("Retroceder");

}
if (x=='d') {
mover_adelante_derecha(); 
Serial.println("Retroceder");

}
if (x=='g') {
  
  configuracion_inicial_servos();
  Serial.println("Configuracion inicial");
  
  }
  if (x=='h') {
Serial.println("Detenerse");

}

}

 void subir_bajar()
{
  //funcion de subida y bajada, solo es de testeo del sistema
  configuracion_inicial_servos();
  delay(600);
  bajar();
  delay(600);
} 
void configuracion_inicial_servos()
{
  //seteo de los motores en su posicion inicial fisica
    servocamara.write(0);
    
    servo1codo.write(90);

    servo1base.write(120); 
//    
    servo2codo.write(115);
  
    servo2base.write(90);
//    
    servo3codo.write(120);

    servo3base.write(90);
//    
    servo4codo.write(45);

    servo4base.write(90);
}
 void mover_cuadrado()
{
  //funcion de testeo
    servo1codo.write(90); 

    servo1base.write(80); // -40 grados a 120
//    
    servo2codo.write(115); 

    servo2base.write(40); // -50 grados a 90
//    
    servo3codo.write(120); 

    servo3base.write(40); // -40 grados a 90
//    
    servo4codo.write(45);

    servo4base.write(50); // -40 grados a 90
}
 void bajar()
{ //funcion de prueba del sistema
    servo1codo.write(130);

    servo1base.write(120); 
//    
    servo2codo.write(75);
 
    servo2base.write(90);
//    
    servo3codo.write(160);
 
    servo3base.write(90);
//    
    servo4codo.write(5);
 
    servo4base.write(90);
}


/////////////////////// Funciones de avance, los parentesis indican la pata fisica y el antecesor a ellos la pata virtual

void moverbases()
{ //coordinacion inicial de las bases para su movimiento
    servo1base.write(100); // -20 grados a 120
    servo2base.write(90); // posicion inicial
    servo3base.write(90); // posicion inicial
    servo4base.write(120); // +30 grados a 90
    delay(tiempo);   
}
///////////////////////
void mover2_dos()
{ //movimiento pata 2(2)
    servo2codo.write(55); // -20 grados a 75
    servo2base.write(130); // +40 grados a 90
    delay(200);
    servo2codo.write(100); // +45 grados a 55
 
   
    delay(tiempo);   
}
void mover1_dos()
{ //movimiento pata 1(1)
    servo1codo.write(160); // +70 grados a 90
    servo1base.write(150); // +30 grados a 120
    delay(200);
    servo1codo.write(130); // -30 grados a 120

   
    delay(tiempo);   
}
void mover3_dos()
{ //movimiento pata 3(3)
    servo3codo.write(190); // +70 grados a 120
    servo3base.write(50); // -40 grados a 90
    delay(200);
    servo3codo.write(160); // -30 grados a 190

 
    delay(tiempo);   
}
void mover4_dos()
{ //movimiento pata 4(4)
    servo4codo.write(0); // -45 grados a 45
    servo4base.write(80); // -10 grados a 90
    delay(200);
    servo4codo.write(25); // +25 grados a 0

   
    delay(tiempo);   
}
void mover_adelante()
{
  //llama a todas las funciones para ejecutar el movimiento
servocamara.write(0);
moverbases();
mover2_dos();
mover1_dos();


mover3_dos();
mover4_dos();
//moverbases();

} 
///////// Funciones de movimiento a la izquierda, los parentesis indican la pata fisica y el antecesor a ellos la pata virtual
void moverbases_izquierda()
{ //coordinacion inicial de las bases para su movimiento
    servo1base.write(150); // +30 grados a 120
    servo2base.write(70); // -20 grados a 90
    servo3base.write(90); // posicion inicial
    servo4base.write(90); // posicion inicial
    delay(tiempo);   
}
void mover1_dos_izquierda()
{ //movimiento pata 1(2)
    servo2codo.write(145); // +70 grados a 75
    servo2base.write(150); // +30 grados a 120
    delay(200);
    servo2codo.write(130); // -30 grados a 120

   
    delay(tiempo);   
}
void mover2_dos_izquierda()
{ //movimiento pata 2(3)
    servo3codo.write(100); // -20 grados a 120
    servo3base.write(130); // +40 grados a 90
    delay(200);
    servo3codo.write(145); // +45 grados a 100
 
   
    delay(tiempo);   
}
void mover3_dos_izquierda()
{ //movimiento pata 3(4)
    servo4codo.write(115); // +70 grados a 45
    servo4base.write(50); // -40 grados a 90
    delay(200);
    servo4codo.write(85); // -30 grados a 115

    delay(tiempo);   
}

void mover4_dos_izquierda()
{ //movimiento pata 4(1)
    servo1codo.write(20); // -70 grados a 90
    servo1base.write(110); // -10 grados a 120
    delay(200);
    servo1codo.write(50); // +30 grados a 20

   
    delay(tiempo);   
}

void mover_adelante_izquierda()
{
  //llama a todas las funciones para ejecutar el movimiento
servocamara.write(90);
moverbases_izquierda();
mover2_dos_izquierda();
mover1_dos_izquierda();

mover3_dos_izquierda();
mover4_dos_izquierda();
//moverbase_izquierda();

} 
///////////////// Funciones de movimiento a la derecha, los parentesis indican la pata fisica y el antecesor a ellos la pata virtual
void moverbases_derecha()
{ //coordinacion inicial de las bases para su movimiento
    servo1base.write(100); // posicion inicial
    servo2base.write(90); // posicion inicial
    servo3base.write(90); // +30 grados a 90
    servo4base.write(120); // +30 -20 grados a 120
    delay(tiempo);   
}
void mover2_dos_derecha()
{ //movimiento pata 2(1)
    servo1codo.write(70); // -20 grados a 90
    servo1base.write(130); // +40 grados a 120
    delay(200);
    servo1codo.write(115); // +45 grados a 70
 
   
    delay(tiempo);   
}
void mover1_dos_derecha()
{ //movimiento pata 1(4)
    servo4codo.write(115); // +70 grados a 45
    servo4base.write(120); // +30 grados a 90
    delay(200);
    servo1codo.write(85); // -30 grados a 115

   
    delay(tiempo);   
}

void mover3_dos_derecha()
{ //movimiento pata 3(2)
    servo3codo.write(170); // +70 grados a 90
    servo3base.write(80); // -40 grados a 120
    delay(200);
    servo3codo.write(140); // -30 grados a 170

 
    delay(tiempo);   
}

void mover4_dos_derecha()
{ //movimiento pata 4(3)
    servo3codo.write(50); // -70 grados a 120
    servo3base.write(80); // -10 grados a 90
    delay(200);
    servo3codo.write(80); // +30 grados a 50

   
    delay(tiempo);   
}

void mover_adelante_derecha()
{
  //llama a todas las funciones para ejecutar el movimiento
servocamara.write(270);
moverbases_derecha();
mover2_dos_derecha();
mover1_dos_derecha();

mover3_dos_derecha();
mover4_dos_derecha();
//moverbases_derecha();

} 
/////////////////////////// Funciones de movimiento hacia atras, los parentesis indican la pata fisica y el antecesor a ellos la pata virtual
void moverbases_atras()
{ //coordinacion inicial de las bases para su movimiento
    servo1base.write(120); // posicion inicial
    servo2base.write(90); // +30 grados a 90
    servo3base.write(70); // -20 grados a 90
    servo4base.write(120); // posicion inicial
    delay(tiempo);   
}

void mover2_dos_atras()
{ //movimiento pata 2(4)
    servo4codo.write(25); // -20 grados a 45
    servo4base.write(130); // +40 grados a 90
    delay(200);
    servo4codo.write(70); // +45 grados a 25
 
   
    delay(tiempo);   
}

void mover1_dos_atras()
{ //movimiento pata 1(3)
    servo3codo.write(180); // +60 grados a 120
    servo3base.write(120); // +30 grados a 90
    delay(200);
    servo3codo.write(150); // -30 grados a 180

   
    delay(tiempo);   
}
void mover3_dos_atras()
{ //movimiento pata 3(1)
    servo1codo.write(160); // +70 grados a 90
    servo1base.write(80); // -40 grados a 120
    delay(200);
    servo1codo.write(130); // -30 grados a 160

 
    delay(tiempo);   
}

void mover4_dos_atras()
{ //movimiento pata 4(2)
    servo4codo.write(5); // -70 grados a 75
    servo4base.write(80); // -10 grados a 90
    delay(200);
    servo4codo.write(35); // +30 grados a 5

   
    delay(tiempo);   
}

void retroceder()
{
  //llama a todas las funciones para ejecutar el movimiento
servocamara.write(180);
moverbases_atras();
mover2_dos_atras();
mover1_dos_atras();

mover3_dos_atras();
mover4_dos_atras();
//moverbases_atras();

} 
