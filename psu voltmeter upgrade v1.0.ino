#include <LiquidCrystal.h>
const int rs = 6, en = 4, d4 = 3, d5 = 2, d6 = 1, d7 = 0;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

float voltage = 0.00;
float ampere = 0.00;
float watt = 0.00;
int valueA4 = 0;
int valueA3 = 0;

void setup() 
{
  lcd.begin(16, 2);
  lcd.print(F("Linear PSU V1.0"));

  lcd.setCursor(0, 1);
  lcd.print(F("Loading"));
  for(int l=1;l<=5;l++){
    lcd.print(F("."));
    delay(500);
  }
  
  lcd.clear();
  lcd.setCursor(6, 0);
  lcd.print(F("V"));
  lcd.setCursor(15, 0);
  lcd.print(F("A"));
  lcd.setCursor(11, 1);
  lcd.print(F("W"));
}
//This function is measure the Ampere
float measureAmper() {
  const float ampereDivider = 2.00;  // 1:2
  int valueA5 = 0;

  for(int v3=1; v3<=20; v3++)
  {
    int read5 = analogRead(A5);
    valueA5 = valueA5 + read5;
    delay(10);
  }
  int value3=valueA5 / 20;
  float ampere1 = value3 / 1024.00 * 5.00;
  return ampere1*ampereDivider;
}
//This function is measure the Voltage from minV until 3V
float measureVoltage1() 
{
  const float voltageDivider = 0.75; 
  valueA4=0;
  for(int v1=1; v1<=10; v1++)
  {
    int read1 = analogRead(A4);
    valueA4 =valueA4+ read1;
    delay(10);
  }

  int value = valueA4 / 10;
  float voltage1= value / 1024.00 * 5.00;
  return voltage1 * voltageDivider;
}

//This function is measure the Voltage from 3V until maxV
float measureVoltage2() 
{
  const float voltageDivider2 = 7.50;  // 1:7
  valueA3 = 0;
  for(int v2=1; v2<=10; v2++){
    int read2 = analogRead(A3);
    valueA3 =valueA3+ read2;
    delay(10);
  }

  int value2=valueA3 / 10;
  float voltage2= value2 / 1024.00 * 5.00;
  return voltage2 * voltageDivider2;
}

void printlcd()
{
  int s = analogRead(A4);
  if (s <= 1000) 
  {
    voltage = measureVoltage1();
    lcd.setCursor(0, 0);
    lcd.print(voltage, 2); lcd.print(" ");
  } 
  else if (analogRead(A3) <= 292) 
  {
    voltage = measureVoltage2();
    lcd.setCursor(0, 0);
    lcd.print(voltage, 2); lcd.print(" ");
  } 
  else 
  {
    voltage = measureVoltage2();
    lcd.setCursor(0, 0);
    lcd.print(voltage, 1); lcd.print(" ");
  }
 int a = analogRead(A5);
  if (a <= 402) 
  {
    ampere = measureAmper();
    lcd.setCursor(9, 0);
    lcd.print(ampere, 2);
    lcd.print(" ");
  } 
  else 
  {
     ampere = measureAmper();
    lcd.setCursor(9, 0);
    lcd.print(ampere, 2);
    lcd.print(" ");
  }
  
 watt = voltage * ampere;
  if(watt <= 0.08)
  {
    watt=0.00;
  }
  lcd.setCursor(5, 1);
  lcd.print(watt, 1); lcd.print(" ");
  
}
void loop() 
{
  printlcd();
}