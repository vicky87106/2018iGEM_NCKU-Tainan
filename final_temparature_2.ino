/********************************************************************/
//include the libraries
#include <OneWire.h> 
#include <DallasTemperature.h>
#include <LiquidCrystal.h>
/********************************************************************/
#define ONE_WIRE_BUS 2                  // Data wire is plugged into pin 2 on the Arduino
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);     // the pins used on the LCD panel 
OneWire oneWire(ONE_WIRE_BUS);          // Setup a oneWire instance to communicate with any OneWire devices
DallasTemperature sensors(&oneWire);    // Pass our oneWire reference to Dallas Temperature. 

/********************************************************************/
void setup(void) 
{ 
  
 Serial.begin(9600);                            // start serial port
 Serial.println("Temparature demo: ");          //print
 sensors.begin();                              // Start up the library 
 lcd.begin(16, 2);                             // start lcd library
 lcd.setCursor(0,0);                           //set the cursor in the LCD to (0,0)
} 
/********************************************************************/
void loop(void) 
{ 
  
   //print on serial
   Serial.print(" Requesting temperatures...");  
   sensors.requestTemperatures();               // Send the command to get temperature readings 
   Serial.println("DONE");                       

   Serial.print("Temperature is: ");             
   Serial.print(sensors.getTempCByIndex(0));     
   // Why "byIndex"?  
   // You can have more than one DS18B20 on the same bus.  
   // 0 refers to the first IC on the wire
/********************************************************************/ 
    //print on lcd
    lcd.setCursor(0,0);
    lcd.print("Temp: ");
    lcd.println(sensors.getTempCByIndex(0));
    lcd.setCursor(11,0);
    lcd.print("C");
   delay(1000); 
} 
