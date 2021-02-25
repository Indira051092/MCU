#define TRIG 2
#define ECHO 3
#define ini1 5
#define ini2 6
#define ini3 7
#define ini4 8
#define anPin 0
int bot1=4,bot2=9,bot3=10,bot4=11;

void setup() {
  Serial.begin(9600);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(bot1,INPUT);
  pinMode(bot2,INPUT);
  pinMode(bot3,INPUT);
  pinMode(bot4,INPUT);
  pinMode(ini1,OUTPUT);
  pinMode(ini2,OUTPUT);
  pinMode(ini3,OUTPUT);
  pinMode(ini4,OUTPUT);
}

int altura(int cuatro)
{
  long volts, pulg,dist_sens2=0;
  int sum = 0, lecturas = 3,dist_max2=600;
    while (dist_sens2<dist_max2 & cuatro == HIGH )
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
        Serial.print(dist_sens2);
        Serial.print("m");
        Serial.println();
        sum = 0;
        delay(500);
     }
}

int basemovil (int dos,int tres)
{
int velocidad=10;   
if (dos==HIGH)
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
else if (tres==HIGH)
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
 }
 }

int decentramiento(int uno)
{
long tiempo,dist_sens=0,dist_fin=0,dist_max=400;
while (dist_sens<dist_max & uno == HIGH )
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
int R1,R2,R3;
int estado1=digitalRead(bot1);
int estado2=digitalRead(bot2);
int estado3=digitalRead(bot3);
int estado4=digitalRead(bot4);
R1=decentramiento(estado1);
R2=basemovil(estado2,estado3);
R3=altura(estado4);
}
