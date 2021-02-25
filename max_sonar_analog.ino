const int anPin = 0;
int bot4;

void setup()
{
  Serial.begin(9600);
  pinMode(bot4,INPUT);
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

void loop()
{
int estado4=digitalRead(11);
int R3;
R3=altura(estado4);
}
