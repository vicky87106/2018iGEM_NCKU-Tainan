#define SensorPin A0            //pH meter Analog output to Arduino Analog Input A0
#define Offset 0.07             //deviation compensate
#define samplingInterval 20     //collect the value every 20ms
#define printInterval 800       //print every 800ms
#define ArrayLenth  40          //put the collect value in the array
int pHArray[ArrayLenth];        //Store the average value of the sensor feedback
int pHArrayIndex=0;             //initialize the value
void setup(void)
{ 
  Serial.begin(9600);  
  Serial.println("pH meter experiment!");    //Test if the serial works
}
void loop(void)
{
  static unsigned long samplingTime = millis();
  static unsigned long printTime = millis();
  static float pHValue,voltage;
  if(millis()-samplingTime > samplingInterval)               //collect the value every 20ms
  {
      pHArray[pHArrayIndex++]=analogRead(SensorPin);         //put the analog signal into the array
      if(pHArrayIndex==ArrayLenth)pHArrayIndex=0;            //reinitialize the array when the array is full
      voltage = avergearray(pHArray, ArrayLenth)*5.0/1024;   //turn analog signal to voltage
      pHValue = 3.5*voltage+Offset;                          //turn voltage to pH value
      samplingTime=millis();                                 //counter of time
  }
  if(millis() - printTime > printInterval)                   //print the value every 800ms
  {
        Serial.print("Voltage:");                             //print voltage on the serial monitor
        Serial.print(voltage,2);                              //print voltage to two decimal places
        Serial.print("    pH value: ");                       //print pH value on the serial monitor
        Serial.println(pHValue,2);                            //Print pH value to two decimal places
        printTime=millis();                                  //counter of time
  }
}
double avergearray(int* arr, int number){                    //average the array index
  int i;
  int max,min;
  double avg;
  long amount=0;
  if(number<=0){                                            //error message when nothing in the array
    Serial.println("Error number for the array to avraging!/n");
    return 0;
  }
  if(number<5){                                            //calculate the average directly when less than 5
    for(i=0;i<number;i++){
      amount+=arr[i];
    }
    avg = amount/number;
    return avg;
  }else{
    if(arr[0]<arr[1]){
      min = arr[0];max=arr[1];
    }
    else{
      min=arr[1];max=arr[0];
    }
    for(i=2;i<number;i++){
      if(arr[i]<min){
        amount+=min;                    //collect the min
        min=arr[i];
      }else {
        if(arr[i]>max){
          amount+=max;                  //collect the min
          max=arr[i];
        }else{
          amount+=arr[i];               //sum up the index without max and min
        }
      }//end if
    }//end for
    avg = (double)amount/(number-2);   //Deduct the maximum and minimum values ​​and average
  }//end if
  return avg;
}
