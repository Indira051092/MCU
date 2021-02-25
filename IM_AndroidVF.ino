#include <Servo.h>
#include <SoftwareSerial.h>

int Rx2=3; //conectar al TX RS232
int Tx2=2; //conectar al RX del RS232

SoftwareSerial sensor(Rx2, Tx2); //comunicacion sensorLaser
#define start 0xAA
#define fin 0XA8
#define slave 0xFF
#define EN 4
#define TRIG 12
#define ECHO 13
#define ini1 8 
#define ini2 7 
#define ini3 6  
#define ini4 5 
int num=0,aux1=0,aux2=0;

Servo servomec; 

void setup() {
 pinMode(EN, OUTPUT);
 pinMode(TRIG, OUTPUT);
 pinMode(ECHO, INPUT);
 pinMode(ini1,OUTPUT);
 pinMode(ini2,OUTPUT);
 pinMode(ini3,OUTPUT);
 pinMode(ini4,OUTPUT);
 digitalWrite(EN, LOW);
 digitalWrite(TRIG, LOW);
 digitalWrite(ECHO, LOW);
 digitalWrite(ini1, LOW);
 digitalWrite(ini2, LOW);
 digitalWrite(ini3, LOW);
 digitalWrite(ini4, LOW);
 Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed
  }
 digitalWrite(EN, HIGH);
 sensor.begin(9600);
 sensor.setTimeout(200);
 singleMeasurement();
 }

int laser(int siete)
{if (siete =='7') 
  {  laserOn(false); }
}

int altura(int cuatro)
{
if (cuatro =='1')
  { 
  delay(100);
  singleMeasurement();
  }
}

int implantacion (int cinco,int seis)
{
servomec.detach();
delay(100);
int angulo=0, enable1=0, enable2=0;
if (cinco =='5')
{
 servomec.attach(9);
 for(angulo = 0; angulo <85; angulo += 1) {   //  un ciclo para mover el servo entre los 0 y los 90 grados  
  if (enable1==0)
 {
 servomec.write(angulo);// manda al servo la posicion
 delay(15); 
 enable1++;
    }
   enable2++;
}
aux1=1;
aux2=0;
}
else if (seis =='6')
{
  aux2=1;
  for(angulo = 85; angulo >= 1; angulo -= 1)    {   //  un ciclo para mover el servo entre los 90 y los 0 grados                             
   if (enable2==0)
 {
  servomec.attach(9);
  servomec.write(angulo);                
  delay(15); 
  enable2++;
  }
}}}

void singleMeasurement()
{
  laserOn(false);
  byte args[2]={slave,0x44}; //arreglo de 2 argumentos tipo cadena de caracteres 
  //definir comportamiento del sensor como esclavo en la dirección 0xFF y a una sola medición
  //Serial.println("Midiendo");
  sensor.write(start);
  sensor.write(args,2); //activa una sola medición
  sensor.write(generateChecksum(args));
  sensor.write(fin);
  delay(1500);
  sensor.read(); 
  sensor.read();
  sensor.read();
  sensor.read(); 
  sensor.read();
  num=sensor.readString().toInt();
  if(aux1==1 && aux2==0){
  num=num+32;               //ajuste de implantacion (32)
  Serial.println(num);  
  }
  else if(aux1==1 && aux2==1){
  num=num+143;              //ajuste de altura quitarle 2mm **155
  Serial.println(num);  
  }
  laserOff(false);
}

void laserOn(bool read)
{
  byte args[2]={slave,0x42};
  sensor.write(start);
  sensor.write(args,2);
  sensor.write(generateChecksum(args));
  sensor.write(fin);
  delay(200);
  if(read)
  {
    printResult();
  }
  else
  {
    flushResult();
  }
}

void laserOff(bool read)
{
  byte args[2]={slave,0x43};
  sensor.write(start);
  sensor.write(args,2);
  sensor.write(generateChecksum(args));
  sensor.write(fin);
  delay(200);
  if(read)
  {
    printResult();
  }
  else
  {
    flushResult();
  }
}

void printResult()
{
while(sensor.available()>0)
{
    Serial.print(sensor.read(),HEX);
    Serial.print(" ");
  }
  Serial.println();
}

void flushResult()
{
  while(sensor.available())
  {
    sensor.read();
  }
}

char getASCII(byte entrada)
{
    return char(entrada);
}

byte generateChecksum(byte args[])
{
  byte checksum = 0;

  for(int i=0;i<2;i++)
  {
    checksum += args[i];
  }

  if((args[1]==0x41)||(args[1]==0x47)) //0x41 set slave address 0x47 buzzer
  {
    checksum += args[2];
  }
  checksum = checksum & 0x7F; //Evalua bit a bit
  //dirección del esclavo+comando.... & 0x7F
  
  return checksum;
}

bool validateChecksum(byte args[])
{
  return true;
}

int basemovil (int dos,int tres)
{

int velocidad=10;
if (dos=='3')//horario
{
digitalWrite(ini1,HIGH);
digitalWrite(ini2,LOW);
digitalWrite(ini3,HIGH);
digitalWrite(ini4,LOW);

delay(velocidad);
digitalWrite(ini1,LOW);
digitalWrite(ini2,HIGH);
digitalWrite(ini3,HIGH);
digitalWrite(ini4,LOW);

delay(velocidad);
digitalWrite(ini1,LOW);
digitalWrite(ini2,HIGH);
digitalWrite(ini3,LOW);
digitalWrite(ini4,HIGH);
delay(velocidad);
digitalWrite(ini1,HIGH);
digitalWrite(ini2,LOW);
digitalWrite(ini3,LOW);
digitalWrite(ini4,HIGH);

delay(velocidad);
digitalWrite(ini1,LOW);
digitalWrite(ini2,LOW);
digitalWrite(ini3,LOW);
digitalWrite(ini4,LOW);
 
}
else if (tres=='4')
{
digitalWrite(ini1,HIGH);
digitalWrite(ini2,LOW);
digitalWrite(ini3,LOW);
digitalWrite(ini4,HIGH);

delay(velocidad);

digitalWrite(ini1,LOW);
digitalWrite(ini2,HIGH);
digitalWrite(ini3,LOW);
digitalWrite(ini4,HIGH);

delay(velocidad);

digitalWrite(ini1,LOW);
digitalWrite(ini2,HIGH);
digitalWrite(ini3,HIGH);
digitalWrite(ini4,LOW);

delay(velocidad);

digitalWrite(ini1,HIGH);
digitalWrite(ini2,LOW);
digitalWrite(ini3,HIGH);
digitalWrite(ini4,LOW);

delay(velocidad);

digitalWrite(ini1,LOW);
digitalWrite(ini2,LOW);
digitalWrite(ini3,LOW);
digitalWrite(ini4,LOW);
 }
 }
//Referencia:Medición hacia el poste negativa
int decentramiento(int uno)
{
//long tiempo,dist_sens=0,dist_fin=0,dist_max=200;
float tiempo,dist_sens=0,dist_fin=0,dist_max=200;
  while (dist_sens<dist_max & uno == '2' )
    {
    uno=LOW;
    digitalWrite(TRIG,LOW); 
    delayMicroseconds(5);
    digitalWrite(TRIG,HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG,LOW);
    tiempo=pulseIn(ECHO,HIGH);
    dist_sens=(tiempo/29.1)*0.5; //cambiar por 2.91 para hacer la medición en mm (antes 29.1 para cm)
    if (dist_sens<=76.5)//antes 76.5
    {dist_fin=85-(dist_sens+8.5);//ajustar el 76.5 y 8.5 solamente ej 76.6@8.4 // **ajustar a 9.5 (antes 85 8.5)
    Serial.println("-"+(String(dist_fin)));
    }
    else
    { dist_fin = (dist_sens + 10)-85; //**ajustar 8.5 a 11.5 (Antes 8.5 y 85)
    Serial.println("+"+(String(dist_fin)));}

    } 
digitalWrite(TRIG,LOW);
digitalWrite(ECHO,LOW);
}

void loop() {
int R1, R2, R3,R4,R5, estado1=0;

  if (Serial.available()>0)
  {
    estado1=Serial.read();
    R1=decentramiento(estado1);
    R3=altura(estado1);
    R2=basemovil(estado1,estado1);
    R4=implantacion(estado1,estado1);
    R5=laser(estado1);
  }
 }

