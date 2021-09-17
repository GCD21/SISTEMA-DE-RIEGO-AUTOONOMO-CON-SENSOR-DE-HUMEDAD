
#include <ThreeWire.h>  
#include <RtcDS1302.h>
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd (0x27, 2, 1, 0, 4, 5, 6, 7);

ThreeWire myWire(4,5,2); // IO, SCLK, CE
RtcDS1302<ThreeWire> Rtc(myWire);
int automatico = HIGH;
int menor = 177;
int mayor = 302;

void setup () 
{
    Serial.begin(9600);
    pinMode(7, INPUT);
    pinMode(8, OUTPUT);
    lcd.setBacklightPin (3, POSITIVE);
    lcd.setBacklight (HIGH);
    lcd.begin(16, 2);
    lcd.clear();
}

void loop () 
{
    RtcDateTime now = Rtc.GetDateTime();

    printDateTime(now);
    Serial.println();

    if(digitalRead(7)==HIGH)
    {automatico=!automatico;
    while(digitalRead(7)==HIGH){
      }
      }

      if(automatico==HIGH){
      lcd.setCursor(0,1);
      lcd.print("AUT");}
      else{
       lcd.setCursor(0,1);
       lcd.print("TEM");}

       lcd.setCursor(4,1);
       lcd.print("HUM=");
       lcd.setCursor(8,1);
       lcd.print(map(analogRead(A0), mayor, menor, 0, 100));
       lcd.print("%   ");  
       
       if(automatico==HIGH){
       if((map(analogRead(A0), mayor, menor, 0, 100))<30){
       digitalWrite(8, HIGH);}
       if((map(analogRead(A0), mayor, menor, 0, 100))>50){
       digitalWrite(8, LOW);}}
       
       

    }

#define countof(a) (sizeof(a) / sizeof(a[0]))

void printDateTime(const RtcDateTime& dt)
{
    char datestring[20];

    snprintf_P(datestring, 
            countof(datestring),
            PSTR("%02u/%02u/%04u %02u:%02u:%02u"),
            dt.Month(),
            dt.Day(),
            dt.Year(),
            dt.Hour(),
            dt.Minute(),
            dt.Second() );
            lcd.setCursor(0,0);
            lcd.print(dt.Hour());
            lcd.print(":");
            lcd.print(dt.Minute());
            lcd.print(" ");
            lcd.print(dt.Day());
            lcd.print("/");
            lcd.print(dt.Month());
            lcd.print("/");
            lcd.print(dt.Year());
            delay(500);

            if(automatico==LOW){
            if(dt.Second()==10){
              digitalWrite(8, HIGH);
              delay(5000);
              digitalWrite(8, LOW);} 
            if(dt.Second()==30){
              digitalWrite(8, HIGH);
              delay(5000);
              digitalWrite(8, LOW);} 
            if(dt.Second()==50){
              digitalWrite(8, HIGH);
              delay(5000);
              digitalWrite(8, LOW);} }
              
            if(dt.Hour()<10){
            lcd.setCursor(1,0);}
            else{ lcd.setCursor(2,0);}
            lcd.print(" ");
            delay(500);
    Serial.print(datestring);
}
