#include <SoftwareSerial.h> 

SoftwareSerial sensor = SoftwareSerial(10,11); //Configurar puerto serie de Arduino MEGA(RX_PIN1O,TX_PIN11)
//RX_PIN10 SE CONECTA AL TX DEL DISPOSITIVO
//TX_PIN11 SE CONECTA AL RX DEL DISPOSITIVO
#define pulso 13 //lámpara


void setup() { 
  Serial.begin(9600); //Abre el puerto Serie ajusta la tasa de datos a 19200bps
  sensor.begin(9600); //Abre el puerto de transmision de datos a 38400bps
  pinMode(pulso, OUTPUT);
  //SendResetCmd(); //Función para RESETEAR la camara, se inicializa para que permita tomar fotografias
  delay(3000); //retardo 3000milisegundos=3seg
  
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//INSTRUCCIONES
void loop() {
  char b;
 // digitalWrite(pulso, HIGH);
  delay(1000);
  Serial.println("hola1"); 

  sensor.write((byte)0x01);
  b=sensor.read();
  Serial.print(b,DEC);
        /* Escribe 79 como código ASCII en decimal que es “79” */
  Serial.print(b,HEX);
        /* Escribe 79 como código ASCII en hexadecimal que es “4F” */
  Serial.print(b,OCT);
        /* Escribe 79 como código ASCII en octal que es “117” */
  Serial.print(b,BIN);
        /* Escribe 79 como código ASCII en binario que es “1001111” */

  //sensor.write((byte)0x42);
  
   
  Serial.println("hola2"); 
  delay(3000);
  while(sensor.available()>0) {
 Serial.println("hola3");
  Serial.println(sensor.read());
  
  //Serial.println("hola4");
     
    }// available() da el número de bytes disponibles para leer
}

