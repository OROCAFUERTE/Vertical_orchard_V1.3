//Ultima actualización 06/11/2022
#include <OneWire.h>                
#include <DallasTemperature.h>
#include <Wire.h> 
#include "RTClib.h"
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);
RTC_DS3231 RTC;
OneWire ourWire(2);                //Se establece el pin 2  como bus OneWire
DallasTemperature sensors(&ourWire); //Se declara una variable u objeto para nuestro sensor

#define sensorPin A0
 
int sensorValue = 0;
float tdsValue = 0;
float Voltage = 0;
 

int hora=0;
int minutos=0;
int segundos=0;


void setup () {
    lcd.begin(16,2);
    lcd.init();
    lcd.backlight();
    lcd.clear();
  //Inicializamos el puerto serie, wire y el modulo RTC
    Serial.begin(115200);
    Wire.begin();
    RTC.begin();
    //Si quitamos el comentario de la linea siguiente, se ajusta la hora y la fecha con la del ordenador
    // RTC.adjust(DateTime(__DATE__, __TIME__));
    pinMode(7,OUTPUT);
    pinMode(6,OUTPUT);
    pinMode(5,OUTPUT);
    pinMode(30,OUTPUT);
    pinMode(32,OUTPUT);
    pinMode(28,OUTPUT);
    
   sensors.begin();  // se inicia el sensor 
  }
  
void loop ()
{

sensorValue = analogRead(sensorPin);
    Voltage = sensorValue*5/1024.0; //Convert analog reading to Voltage
    tdsValue=(133.42/Voltage*Voltage*Voltage - 255.86*Voltage*Voltage + 857.39*Voltage)*0.5; //Convert voltage value to TDS value
    Serial.print("TDS Value = "); 
    Serial.print(tdsValue);
    Serial.println(" ppm");
  
  lcd.setCursor(9, 1);
  lcd.print("TDS:"); 
  lcd.print(tdsValue,0);  

  
sensors.requestTemperatures();   //Se envía el comando para leer la temperatura
float temp= sensors.getTempCByIndex(0); //Se obtiene la temperatura en ºC
  
    DateTime now = RTC.now();
  hora=(now.hour(),DEC);
  minutos=(now.minute(),DEC);
  segundos=(now.second(),DEC);
    //Imprimimos el dia
    lcd.setCursor(0,0);
    lcd.print(now.day(), DEC);
    lcd.print('/');
    //Imprimimos el mes
    lcd.print(now.month(), DEC);
    lcd.print('/');
    //Imprimimos el año
    lcd.print(now.year(), DEC);
    lcd.print(' ');
    //Imprimimos la hora
    lcd.setCursor(0,1);
    lcd.print(now.hour(), DEC);
    lcd.print(':');
    //Imprimimos los minutos
    lcd.print(now.minute(), DEC);
    lcd.print(':');
    //Imprimimos los segundos
    lcd.print(now.second(), DEC);
    lcd.setCursor(11,0);

    lcd.setCursor(9,0);
    lcd.print("T:");
    lcd.print(temp);
    lcd.print("C");

     if (now.hour()== 9 && now.minute() == 30 && now.second() == 00)
  {
   digitalWrite(5,HIGH);
   lcd.setCursor(9,1);
   lcd.print("LED_ON");
  }
  else if (now.hour()== 21 && now.minute() == 00 && now.second() == 00)
  {
    digitalWrite(5,LOW);
     lcd.setCursor(8,1);
   lcd.print("LED_OFF");
  }

     if (now.hour()== 9 && now.minute() == 29 && now.second() == 29 )
  {
   digitalWrite(6,HIGH);
     lcd.setCursor(9,1);
   lcd.print("SUP_ON");
  }
  else if (now.hour()== 21 && now.minute() == 35  && now.second() == 00)
  {
    digitalWrite(6,LOW);
     lcd.setCursor(8,1);
   lcd.print("SUP_OFF");
 }
  if (now.hour()== 9  && now.minute() == 30 && now.second() == 00)
  
  {
   digitalWrite(7,HIGH);
   lcd.setCursor(9,1);
   lcd.print("LED_ON");
   
  }
  else if (now.hour()== 21 && now.minute() == 00  && now.second() == 00)
  {
    digitalWrite(7,LOW);
    lcd.setCursor(9,1);
    lcd.print("LED_OFF");
  }

   if (now.hour()== 9 && now.minute() == 30 && now.second() == 00)

  {
   digitalWrite(30,HIGH);
   lcd.setCursor(9,1);
   lcd.print("LED2ON");
   
  }
  else if (now.hour()== 21 && now.minute() == 30  && now.second() == 00)
  {
    digitalWrite(30,LOW);
    lcd.setCursor(9,1);
    lcd.print("LED2OFF");
  }

  if (now.hour()== 9 && now.minute() == 30 && now.second() == 00)

  {
   digitalWrite(32,HIGH);
   lcd.setCursor(9,1);
   lcd.print("LED2ON");
   
  }
  else if (now.hour()== 21 && now.minute() == 30  && now.second() == 00)
  {
    digitalWrite(32,LOW);
    lcd.setCursor(9,1);
    lcd.print("LED2OFF");
  }

  if (now.hour()== 9 && now.minute() == 29  && now.second() == 50)  //Establecer encendido del ventilador 2

  {
   digitalWrite(28,HIGH);
   lcd.setCursor(9,1);
   lcd.print("VEN2ON");
   
  }
  else if (now.hour()== 21 && now.minute() == 32  && now.second() == 50)  //Establecer apagado del ventilador 2
  {
    digitalWrite(28,LOW);
    lcd.setCursor(9,1);
    lcd.print("VEN2OFF");
  }

}
