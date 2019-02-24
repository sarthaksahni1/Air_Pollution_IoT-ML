#include <ESP8266WiFi.h>  
 #include <WiFiClient.h>  
 #include <ThingSpeak.h>
 int gas = A0;   
 const char* ssid = "sarthak1";  
 const char* password = "12345678";  
 WiFiClient client;  
 unsigned long myChannelNumber = 666694;  
 const char * myWriteAPIKey = "RD7DK93MY24SDWI8";    
 void setup()  
 {
  pinMode(D0,OUTPUT); 
  pinMode(D1,OUTPUT); 
  pinMode(gas,INPUT);  
  Serial.begin(115200);  
  delay(10);  
  // Connect to WiFi network  
  Serial.println();  
  Serial.println();
  Serial.print("Connecting to ");  
  Serial.println(ssid);  
  WiFi.begin(ssid, password);  
  while (WiFi.status() != WL_CONNECTED)  
  {  
   delay(500);  
   Serial.print(".");  
  }  
  Serial.println("");  
  Serial.println("WiFi connected");  
  // Print the IP address  
  Serial.println(WiFi.localIP());  
  ThingSpeak.begin(client);
 }  
 void loop()   
 {  
  static boolean data_state = true;  
  int sensorValue = analogRead(gas);
 float a = sensorValue*(5.0/1023.0);
  if(a>1)
  {
       ThingSpeak.writeField(myChannelNumber,  3,a , myWriteAPIKey);
      Serial.println("uploaded");
      digitalWrite(D1,LOW);
          digitalWrite(D0,HIGH);
  }
  else
  {
        digitalWrite(D0,LOW);
        digitalWrite(D1,HIGH);
       ThingSpeak.writeField(myChannelNumber,  3,a , myWriteAPIKey);
      Serial.println("uploaded");
  }
  Serial.println(a);
  delay(1000);

  // Write to ThingSpeak. There are up to 8 fields in a channel, allowing you to store up to 8 different  
  // pieces of information in a channel. Here, we write to field 1. 
  delay(1000); // ThingSpeak will only accept updates every 1 second.  
 }
