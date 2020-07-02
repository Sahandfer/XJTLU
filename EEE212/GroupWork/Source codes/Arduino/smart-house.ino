#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid ="HUAWEI";
const char* password= "asd662304";

char* light1= "off";
char* light2= "off";
char* light3= "off";


int ledPin1 = 16; //D0 // GPIO2 of ESP8266
int ledPin2 = 4;  //D2
int ledPin3 = 0;  //D3
int inputPinhey = 13; // choose the input pin
int oldval=0;
int changeState=LOW;

const char* host="eeearduino.000webhostapp.com";



int arrayIndex= 0;
String ourResponse;

void setup() {
   Serial.begin(115200);
   delay(10);

   pinMode(ledPin1, OUTPUT);
   pinMode(ledPin2, OUTPUT);
   pinMode(ledPin3, OUTPUT);
   pinMode(inputPinhey, INPUT);
   digitalWrite(ledPin1, LOW);
   digitalWrite(ledPin2, LOW);
   digitalWrite(ledPin3, LOW);

   Serial.println();
   Serial.println();
   Serial.println("Connecting to ");
   Serial.println(ssid);

   WiFi.begin(ssid, password);

   while(WiFi.status() != WL_CONNECTED){
      delay(500);
      Serial.print(".");
   }
   Serial.println();
   Serial.println("Wifi connected");
   Serial.println("IP:");
   Serial.println(WiFi.localIP());
}

void loop() {

  char* door="open";
  
  int val = digitalRead(inputPinhey);
  //Setter
  Serial.println("Value: ");
  Serial.println(String(val));
  if (val==HIGH){ //Door closed
      door="closed";
      Serial.println("Door: ");
      Serial.println(door);
  }
  else{
      door="open";
      Serial.println("Door: ");
      Serial.println(door);
   }

  HTTPClient http1;  //Declare an object of class HTTPClient
 
  http1.begin("http://eeearduino.000webhostapp.com/lightSetter.php?lightNum=doorlock&status="+String(door));  //Specify request destination
  int httpCode1 = http1.GET();                                                                  //Send the request
   
  if (httpCode1 > 0) { //Check the returning code
   
  String payload1 = http1.getString();   //Get the request response payload
  Serial.println(payload1);                     //Print the response payload
   
  }
   
  http1.end();   //Close connection

  
  //GETTER
  HTTPClient http;  //Declare an object of class HTTPClient
 
  http.begin("http://eeearduino.000webhostapp.com/lightGetter.php");  //Specify request destination
  int httpCode = http.GET();                                                                  //Send the request
   
  if (httpCode > 0) { //Check the returning code
   
  String payload = http.getString();   //Get the request response payload
  Serial.println(payload);                     //Print the response payload
  if (payload.substring(0,2) =="on"){
    light1="on";

    
    //on on 
    if (payload.substring(3, 5) =="on"){
      light2="on";
      //on on on
      if (payload.substring(6,8) =="on"){
        light3="on";
      }
      else{
        light3="off";
      }
      
    }

    //on off
    else{
      light2="off";
      //on off on
      if (payload.substring(7,9) =="on"){
        light3="on";
      }
      else{
        light3="off";
      }
    }
  }

  //Light 1 is off
  else{
    
    light1="off";
    //off on
    if (payload.substring(4,6) =="on"){
      light2="on";
      //off on on
      if (payload.substring(7,9) =="on"){
        light3="on";
      }
      else{
        light3="off";
      }
    }

    // off off
    else{
      light2="off";
      //off off on
      if (payload.substring(8,10) =="on"){
        light3="on";
      }
      else{
        light3="off";
      }
    }
    
  }
  Serial.println("light 1 ==>");
  Serial.println(light1);
  Serial.println("light 2 ==>");
  Serial.println(light2);
  Serial.println("light 3 ==>");
  Serial.println(light3);
  Serial.println("Closing connection...");

  //Changing status of light 1
  if(light1=="on"){
    digitalWrite(ledPin1, HIGH);
  }
  else{
    digitalWrite(ledPin1, LOW);
  }

  //Changing status of light 2
  if(light2=="on"){
    digitalWrite(ledPin2, HIGH);
  }
  else{
    digitalWrite(ledPin2, LOW);
  }

  //Changing status of light 3
  if(light3=="on"){
    digitalWrite(ledPin3, HIGH);
  }
  else{
    digitalWrite(ledPin3, LOW);
  }
  }
   
  http.end();   //Close connection


  
  delay(1000); 

}
