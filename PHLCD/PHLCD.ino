#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>

#define RX 0 
#define TX 1

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);  // The LCD pins connected with the Arduino
float calibration_value = 21.34 + 7.9; // Calibration of the pH scale to make it neutral
unsigned long int avgValue;  //Store the average value of the sensor feedback
int buf[10], temp;

float phValue; // The value of the pH

void setup(){

Serial.begin(9600);  


lcd.begin(16, 2);  // Starts up the LCD device
lcd.clear();  
lcd.setCursor(0, 0);  
lcd.print("Welcome To");     // Prints the beginning message for it loads on line 1
lcd.setCursor(0, 1);  
lcd.print("       pH Meter"); // Prints the beginning message for it loads on line 2
delay(1000);
lcd.clear(); 

}

void loop(){
  
  // Calculates the value of the pH when the pH Sensor is dipped into a solution
 for(int i=0;i<10;i++) 
 { 
 buf[i]=analogRead(A1);
 delay(30);
 }
 for(int i=0;i<9;i++)
 {
 for(int j=i+1;j<10;j++)
 {
 if(buf[i]>buf[j])
 {
 temp=buf[i];
 buf[i]=buf[j];
 buf[j]=temp;
 }
 }
 }
 avgValue=0;
 for(int i=2;i<8;i++)
 avgValue+=buf[i];
 float volt=(float)avgValue*5/1024/6; 
  phValue = -5.70 * volt + calibration_value;
 
 Serial.println(phValue); // prints out the final value onto Serial to display on the Serial Monitor and Plotter
 delay(1000);
      
 lcd.setCursor(0, 0);  
  lcd.print(" pH Value: "); 
  lcd.print(phValue); // prints out the pH Value and text onto the LCD when live.
  lcd.print("  ");

 // Prints out the type of pH that the current phValue Value is currently at.
  lcd.setCursor(1, 1); 
     if(phValue<4)                 lcd.print(" Very Acidic ");
else if(phValue>=4  && phValue<5)  lcd.print("    Acidic   ");
else if(phValue>=5  && phValue<7)  lcd.print(" Acidic-ish  ");
else if(phValue>=7  && phValue<8)  lcd.print("   Neutral   ");
else if(phValue>=8  && phValue<10) lcd.print("Alkaline-ish ");
else if(phValue>=10 && phValue<11) lcd.print("  Alkaline   ");
else if(phValue>=11)               lcd.print("Very Alkaline");
      
  delay(1000);

}