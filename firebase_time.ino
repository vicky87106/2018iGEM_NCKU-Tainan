#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <time.h>

// Set these to run example.
#define FIREBASE_HOST "co2-app.firebaseio.com"
#define FIREBASE_AUTH "Eo3ox0F2Mqlc2TDxA8Xdbmq7S0NxUGo8vOj9AOSa"
#define WIFI_SSID "elieen"
#define WIFI_PASSWORD "elieen22"

const char* ssid = "elieen";
const char* password = "elieen22";

int timezone = (-4) * 3600;//設定時區因為台灣是+8所以->時區*3600
int dst = 0;

void setup() {
  Serial.begin(9600);

  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  configTime(timezone, dst, "pool.ntp.org","time.nist.gov");
  Serial.println("\nWaiting for Internet time");

  while(!time(nullptr)){
     Serial.print("*");
     delay(1000);
  }
  Serial.println("\nTime response....OK"); 
}

int n = 0;

void loop() {
  time_t now = time(nullptr);
  struct tm* p_tm = localtime(&now);
  Serial.print(p_tm->tm_mday);
  Serial.print("/");
  Serial.print(p_tm->tm_mon + 1);
  Serial.print("/");
  Serial.print(p_tm->tm_year + 1900);

  Serial.print(" ");

  Serial.print(p_tm->tm_hour);
  Serial.print(":");
  Serial.print(p_tm->tm_min);
  Serial.print(":");
  Serial.println(p_tm->tm_sec); 
  StaticJsonBuffer<200> jsonBuffer;//下面五行是資料庫並列的code  就是concentration、溫度...
  JsonObject& valueObject = jsonBuffer.createObject();
  valueObject["temperature"] = 28.47;
  valueObject["concentration"] = 5.1;
  valueObject["pH"]=6.34;
  String mon;
  String day;
  String hour;
  String minu;
  String sec;
  if(p_tm->tm_mon==0||p_tm->tm_mon==1||p_tm->tm_mon==2||p_tm->tm_mon==3||p_tm->tm_mon==4||p_tm->tm_mon==5||p_tm->tm_mon==6||p_tm->tm_mon==7||p_tm->tm_mon==8)
  {mon="0"+String(p_tm->tm_mon+1);}
  else{mon=String(p_tm->tm_mon+1);}
 
  if(p_tm->tm_mday==0||p_tm->tm_mday==1||p_tm->tm_mday==2||p_tm->tm_mday==3||p_tm->tm_mday==4||p_tm->tm_mday==5||p_tm->tm_mday==6||p_tm->tm_mday==7||p_tm->tm_mday==8||p_tm->tm_mday==9)
  {day="0"+String(p_tm->tm_mday);}
  else{day=String(p_tm->tm_mday);}
  
  if(p_tm->tm_hour==0||p_tm->tm_hour==1||p_tm->tm_hour==2||p_tm->tm_hour==3||p_tm->tm_hour==4||p_tm->tm_hour==5||p_tm->tm_hour==6||p_tm->tm_hour==7||p_tm->tm_hour==8||p_tm->tm_hour==9)
  {hour="0"+String(p_tm->tm_hour);}
  else{hour=String(p_tm->tm_hour);}
  
  if(p_tm->tm_min==0||p_tm->tm_min==1||p_tm->tm_min==2||p_tm->tm_min==3||p_tm->tm_min==4||p_tm->tm_min==5||p_tm->tm_min==6||p_tm->tm_min==7||p_tm->tm_min==8||p_tm->tm_min==9)
  {minu="0"+String(p_tm->tm_min);}
  else{minu=String(p_tm->tm_min);}
  
  if(p_tm->tm_sec==0||p_tm->tm_sec==1||p_tm->tm_sec==2||p_tm->tm_sec==3||p_tm->tm_sec==4||p_tm->tm_sec==5||p_tm->tm_sec==6||p_tm->tm_sec==7||p_tm->tm_sec==8||p_tm->tm_sec==9)
  {sec="0"+String(p_tm->tm_sec);}
  else{sec=String(p_tm->tm_sec);}
  Firebase.set(mon + "/"+day+"/"+hour+":"+minu+":"+sec, valueObject);
 
 //const String deviceName = "Wio Link " + deviceNumber;
 

 
 
 /* StaticJsonBuffer<200> jsonBuffer;//下面五行是資料庫並列的code  就是concentration、溫度...
  JsonObject& valueObject = jsonBuffer.createObject();
  valueObject["temperature"] = 1;
  valueObject["raw"] = 2;
  Firebase.push(deviceNumber + "/value", valueObject);*/
 
  
  
  //Firebase.setString(deviceNumber + "/name", deviceName);
  //delay(1000);
  /*
  String concentration="10/10/21:00:10/concentration";
  String pH="10/10/21:00:10/pH";
//  temperature="10/10/21:00:10/temperature";
  Firebase.pushFloat(concentration,88.2);*/
  //Firebase.pushFloat(pH,1.3);
  //Firebase.pushFloat(temperature,2.5);
  /*if(n==60)
    n=0;
  else
    n=n+10;
  */
  if (Firebase.failed()) {
      Serial.print("pushing /logs failed:");
      Serial.println(Firebase.error());  
      return;
  }
  delay(1000);
}
