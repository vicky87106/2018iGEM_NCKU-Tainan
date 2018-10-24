#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);                   // select the pins used on the LCD panel
/*************************************************************************************/
#define         MG_PIN                       (A0)    //define which analog input channel you are going to use
#define         DC_GAIN                      (8.5)   //define the DC gain of amplifier
#define         READ_SAMPLE_INTERVAL         (50)    //define how many samples you are going to take in normal operation
#define         READ_SAMPLE_TIMES            (5)     //define the time interval(in milisecond) between each samples
 
/*************************************************************************************/
//These two values differ from sensor to sensor. User should determine this value.
#define         V400        (705)                   //measure the air of the atmosphere(approximate 400ppm)
#define         V40000      (500)                   //measure the analog value of 100% CO2
 
/*************************************************************************************/
float slope=(V40000-V400)/(4.602-2.602);            //calculate the slope of the correction line
                                                    //log40000=4.602
                                                    //log400=2.602
                                                                                               
void setup()
{
    Serial.begin(9600);                               
    lcd.begin(16,2);                                // start the LCD library
    lcd.setCursor(0,0);                             //set the LCD cursor to(0,0)
}
 
void loop()
{
/*************************************************************************************/
    int percentage;
    float analogValue;
    float volts;
/*************************************************************************************/     
    analogValue = MGRead(MG_PIN);                   //read the analog value from the pin
    volts=analogValue*5/1024;                       //turn the analog value into voltage
    percentage = MGGetPercentage(analogValue);      //turn the analog value to percentage
/*************************************************************************************/   
    Serial.print("Analog Value:  ");
    Serial.print(analogValue);
    Serial.print( "\t" );
    
    Serial.print("Voltage: ");           
    Serial.print(volts); 
    Serial.print( "V" );
    Serial.print( "\t" );  
     
    Serial.print("CO2:");
    Serial.print(percentage);
    Serial.print( "ppm" );  
    Serial.print( "\t" );
    
    Serial.print( "Time point:" );
    Serial.print(millis());
    Serial.print("\n");
/*************************************************************************************/ 
    lcd.setCursor(0,0);
    lcd.print("CO2:");
    lcd.print(percentage);
    lcd.setCursor(10,0);
    lcd.print( "ppm" ); 
}
 
float MGRead(int mg_pin)                               //average the sample value 
{
    int i;
    float v=0;
    for (i=0;i<READ_SAMPLE_TIMES;i++)
    {
        v += analogRead(mg_pin);
        delay(READ_SAMPLE_INTERVAL);
    }
    v =v/READ_SAMPLE_TIMES ;
    return v;  
}
 

int  MGGetPercentage(float analogValue)
{   
     float logConc=2.602 +(analogValue-V400)/slope;   //calculate the log value of CO2 concentration
      return pow(10,logConc );
}
