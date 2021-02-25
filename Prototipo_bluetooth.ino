#include <Servo.h>
#include <SoftwareSerial.h>
int Rx=10;
int Tx=11;
SoftwareSerial serial2(Rx, Tx);

#define TRIG 2
#define ECHO 3
#define ini1 5
#define ini2 6
#define ini3 7
#define ini4 8
#define anPin 0
#define pulso 4

Servo servomec; 

void setup() {
  Serial.begin(9600);
  serial2.begin(9600);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(ini1,OUTPUT);
  pinMode(ini2,OUTPUT);
  pinMode(ini3,OUTPUT);
  pinMode(ini4,OUTPUT);
  pinMode(13, OUTPUT);//prueba
  servomec.attach(4);
}

int altura(int cuatro)
{
  long volts, pulg,dist_sens2=0;
  int sum = 0, lecturas = 3,dist_max2=600;
    while (dist_sens2<dist_max2 & cuatro == '1' )
      {
        cuatro=LOW;
        for (int i = 0; i < lecturas ; i++)
          {
            volts = analogRead(anPin) / 2;
            sum += volts;
            delay(10);
          }
        pulg = sum / lecturas;
        dist_sens2 = (pulg * 0.0254);//+k[m]compensación de altura
        Serial.print("Altura= ");
        Serial.println(String(dist_sens2)+"m");
        sum = 0;
        delay(500);
     }
}

int implantacion (int cinco,int seis)
{
int angulo=0, enable1=0, enable2=0;
if (cinco =='5')
{
 for(angulo = 0; angulo < 90; angulo += 1) {   //  un ciclo para mover el servo entre los 0 y los 90 grados  
  if (enable1==0)
 {
 servomec.write(angulo);               //  manda al servo la posicion
 delay(15); 
 enable1++;
    }
   enable2++;
}}
else if (seis =='6')
{
  for(angulo = 90; angulo >= 1; angulo -= 1)    {   //  un ciclo para mover el servo entre los 90 y los 0 grados                             
   if (enable2==0)
 {
  servomec.write(angulo);                 //  manda al servo la posicion
  delay(15); 
  enable2++;
  }
  enable1=0;
}
}}

int basemovil (int dos,int tres)
{
int velocidad=10;   
if (dos =='3')
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
}
else if (tres =='4')
{
digitalWrite(13,HIGH); //prueba 
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
 }
 }

int decentramiento(int uno)
{
long tiempo,dist_sens=0,dist_fin=0,dist_max=400;
  while (dist_sens<dist_max & uno == '2' )
    {
    uno=LOW;
    digitalWrite(TRIG,LOW); 
    delayMicroseconds(5);
    digitalWrite(TRIG,HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG,LOW);
    tiempo=pulseIn(ECHO,HIGH);
    dist_sens=(tiempo/29.1)*0.5;
    if (dist_sens<=40)
    {dist_fin = 50-(dist_sens+7);
    Serial.println(String(dist_fin)+"cm (-)");
    }
    else
    { dist_fin = dist_sens-43;
    Serial.println(String(dist_fin)+"cm (+)");}
    delay(1000);
    } 
}
void loop() {
int R1,R2,R3,R4,estado1=0;
  if (Serial.available()>0)
  {
    serial2.println("test de bluetooth activado");
    delay(50);
    serial2.write(Serial.read());
    //BT1.flush();
    estado1=Serial.read();
    R1=decentramiento(estado1);
    R3=altura(estado1);
    R2=basemovil(estado1,estado1);
    R4=implantacion(estado1,estado1);
  }
  if (serial2.available())
  {
   Serial.write(serial2.read()); 
  }
}
