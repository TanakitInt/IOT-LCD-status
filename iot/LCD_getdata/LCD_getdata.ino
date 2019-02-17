//**5V in**

//Coded by TanakitInt.

//LCD----------------------------------------------------------------------------------
//Libraries
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address, if it's not working try 0x27 or 0x3F.

//TEMPERATURE---------------------------------------------------------------------------
//set analog pin
int ThermistorPin = A0;

//set constant resistance for know resistor
float R1 = 10000;

//initial value for Steinhart-Hart equation
//used for convert the resistance of the thermistor to a temperature reading
int Vo;
float logR2, R2, T;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;

//PHOTO RESISTOR------------------------------------------------------------------------
int sensorPin = A7;   // select the analog input pin for the photoresistor
int threshold = 400;  // analog input trigger level from photoresistor
int sensorValue = 0;  // photoresistor value read from analog input pin
int ledPin = 52;

void setup()
{
  //LCD---------------------------------------------------------------------------------
  lcd.begin(16, 2);  // iInit the LCD for 16 chars 2 lines

  lcd.backlight();   //backlight on

  //TEMPERATURE-------------------------------------------------------------------------
  Serial.begin(9600);

  //PHOTO RESISTOR----------------------------------------------------------------------
  pinMode(ledPin, OUTPUT);
}

void loop()
{
  //TEMPERATURE-------------------------------------------------------------------------
  //get analogRead from analog pin
  Vo = analogRead(ThermistorPin);

  //Steinhart-Hart equation
  //the T ouput is Kelvin
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2 * logR2 + c3 * logR2 * logR2 * logR2));

  //Convert Kelvin to Celsius
  T = T - 273.15;

  //print the value  
  Serial.print(T);
  Serial.print(",");

  //Setup LCD line

  lcd.setCursor(0, 0); //First line

  //PLEASE SEE THE HD44780 lcd controller MANUAL AND CONVERT Binary to Decimal AT FIRST!!
  //onndo = おんど = 温度
  //means "Temperature" in Japanese.

  //(char)181 >> o >> オ
  //(char)221 >> nn >> ン
  //(char)196 and (char)222 >> do >> ド

  lcd.print((char)181);
  lcd.print((char)221);
  lcd.print((char)196);
  lcd.print((char)222);

  lcd.print(" : ");
  lcd.print(T);
  lcd.println(" C  ");

  //PHOTO RESISTOR---------------------------------------------------------------------
  lcd.setCursor(0, 1); //Second line

  Serial.print(analogRead(sensorPin));
  Serial.print(",");
  
  //PLEASE SEE THE HD44780 lcd controller MANUAL AND CONVERT Binary to Decimal AT FIRST!!
  //(char)215 >> ra >> ラ
  //(char)178 >> i >> イ
  //(char)196 >> to >> ト

  lcd.print((char)215);
  lcd.print((char)178);
  lcd.print((char)196);

  lcd.print("  : ");

  lcd.print(analogRead(sensorPin));

  if (analogRead(sensorPin) < threshold)
  {
    digitalWrite(ledPin, HIGH);
    Serial.print("ON!");
    Serial.println(",");
    
    lcd.print(" ON!  ");
  }
  else
  {
    digitalWrite(ledPin, LOW);
    Serial.print("OFF");
    Serial.println(",");
    
    lcd.print(" OFF  ");
  }

  //---------------------------------------------------------------------------------
  //set delay output in millisecond (ms)
  delay(1000);

}
