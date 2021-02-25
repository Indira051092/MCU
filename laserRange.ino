//constantes
#define INITIATE 0xAA
#define END 0XA8
#define ADDRESS 0xFF

//pines
#define ENABLE 2
#define BOTON 3

#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX

void setup() {
  pinMode(BOTON, INPUT_PULLUP);
  pinMode(ENABLE, OUTPUT);
  digitalWrite(ENABLE, LOW);
  // Open serial communications and wait for port to open:
  Serial.begin(57600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  digitalWrite(ENABLE, HIGH);

  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  // Serial.println("Query");
  // mySerial.write(INITIATE);
  // mySerial.write(byte(0));
  // mySerial.write(0x04);
  // mySerial.write(0x04);
  // mySerial.write(END);
  // delay(200);
  // while (mySerial.available()) {
  //   Serial.println(mySerial.read(),HEX);
  // }
  laserOff(false);
  Serial.println("Listo");
}

void loop() {
  if(digitalRead(BOTON)==LOW)
  {
    delay(100);
    if(digitalRead(BOTON)==LOW)
    {
      singleMeasurement();
    }
  }
  // singleMeasurement();
  // delay(2000);
  // while (mySerial.available()) {
  //   Serial.println(mySerial.read(),HEX);
  // }
}

// void laserOn()
// {
//   byte args[2]={ADDRESS,0x42};
//   Serial.println("Laser ON");
//   mySerial.write(INITIATE);
//   mySerial.write(args,2);
//   mySerial.write(generateChecksum(args));
//   mySerial.write(END);
//   delay(200);
// }
//
// void laserOff()
// {
//   byte args[2]={ADDRESS,0x43};
//   Serial.println("Laser Off");
//   mySerial.write(INITIATE);
//   mySerial.write(args,2);
//   mySerial.write(generateChecksum(args));
//   mySerial.write(END);
//   delay(200);
// }

void laserOn(bool read)
{
  byte args[2]={ADDRESS,0x42};
  Serial.println("Laser ON");
  mySerial.write(INITIATE);
  mySerial.write(args,2);
  mySerial.write(generateChecksum(args));
  mySerial.write(END);
  delay(200);
  if(read)//Imprimir el resultado
  {
    printResult();
  }
  else//Ignorar el resultado
  {
    flushResult();
  }
}

void laserOff(bool read)
{
  byte args[2]={ADDRESS,0x43};
  Serial.println("Laser Off");
  mySerial.write(INITIATE);
  mySerial.write(args,2);
  mySerial.write(generateChecksum(args));
  mySerial.write(END);
  delay(200);
  if(read)//Imprimir el resultado
  {
    printResult();
  }
  else//Ignorar el resultado
  {
    flushResult();
  }
}

void printResult()
{
  while(mySerial.available())
  {
    Serial.print(mySerial.read(),HEX);
    Serial.print(" ");
  }
  Serial.println();
}

void flushResult()
{
  while(mySerial.available())
  {
    mySerial.read();
  }
}

void singleMeasurement()
{
  laserOn(false);
  byte args[2]={ADDRESS,0x44};
  Serial.println("Midiendo");
  mySerial.write(INITIATE);
  mySerial.write(args,2);
  mySerial.write(generateChecksum(args));
  mySerial.write(END);
  delay(1500);
  // printResult();
  mySerial.read(); //INITIATE
  mySerial.read(); //ADDRESS
  mySerial.read(); //Comando
  Serial.print(getASCII(mySerial.read()));
  Serial.print(getASCII(mySerial.read()));
  Serial.print(getASCII(mySerial.read()));
  Serial.print(getASCII(mySerial.read()));
  Serial.print(getASCII(mySerial.read()));
  Serial.print(getASCII(mySerial.read()));
  mySerial.read(); //Checksum
  mySerial.read(); //END
  Serial.println("mm");
  laserOff(false);
}

char getASCII(byte entrada)
{
  return char(entrada);
}

byte generateChecksum(byte args[])
{
  byte checksum = 0;
  /*
  *En general todos los comandos de maestro a esclavo tienen 2 elementos
  *más el checksum
  */
  for(int i=0;i<2;i++)
  {
    checksum += args[i];
  }
  /*
  *Los comandos Set Slave Address (0x41) y ON/OFF buzzer (0x47) llevan un
  *argumento que se debe considerar en el checksum
  */
  if((args[1]==0x41)||(args[1]==0x47))
  {
    checksum += args[2];
  }
  checksum = checksum & 0x7F;
  // Serial.print("Checksum: ");
  // Serial.print(checksum,HEX);
  // Serial.println();
  return checksum;
}

bool validateChecksum(byte args[])
{
  return true;
}
