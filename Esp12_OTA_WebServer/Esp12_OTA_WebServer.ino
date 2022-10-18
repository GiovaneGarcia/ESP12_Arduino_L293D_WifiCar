#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <ESP8266WebServer.h>
//#include "HandleMotors.h"

#ifndef STASSID
#define STASSID "ESPCar"
#define STAPSK  "gigio123"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;
byte bMotor = 0;// motor off
byte bState = 0;// vehicle stopped

ESP8266WebServer server;

//IPAddress ip(192,168,2,100);
//IPAddress gateway(192,168,2,1);
//IPAddress subnet(255,255,255,0);

byte led = 2;

void ligaled(){
  digitalWrite(led,LOW);
  server.send(204,"");
}
void desligaled(){
  digitalWrite(led,HIGH);
  server.send(204,"");
}

void FRONT(){
  bState=1;
  Serial.println("FT");//bState); //just a gateway from WIFI to Serial
  server.send(204,"");
};
void LEFT(){
  bState=2;
  Serial.println("LE");
  server.send(204,"");
};
void BACK(){
  bState=3;
  Serial.println("BA");
  server.send(204,"");
};
void RIGHT(){
  bState=4;
  Serial.println("RI");
  server.send(204,"");
};
void FL(){
  bState=5;
  Serial.println("FL");
  server.send(204,"");
};
void FR(){
  bState=6;
  Serial.println("FR");
  server.send(204,"");
};
void BR(){
  bState=7;
  Serial.println("BR");
  server.send(204,"");
};
void BL(){
  bState=8;
  Serial.println("BL");
  server.send(204,"");
};

void DoNothing(){
  if (bState){
    Serial.println("DN");
    bState=0;
  }  
  server.send(204,"");
}
//*******************
/*
void fHandleCommand(byte state){
  switch (state) {
    case 0:
      bMotor = 0x00; //motor OFF
    break;
    case 1: //Note - todos a frente
      bMotor = 0xF0; //motor OFF    
    break;
    case 2: //Leste - FL=+1, FR=-1, BL=+1, BR=-1
      //bMotor = 0x1010 0101;
    break;
    case 3: //Sul - FL=-1, FR=-1, BL=-1, BR=-1
      bMotor = 0x0F; //motor OFF    
    break;
    case 4: //Oeste - FL=-1, FR=+1, BL=-1, BR=+1
      //bMotor = 0x0101 1010;
      bMotor = 0; //motor OFF    

    break;        
    case 5: //NE
      bMotor = 0; //motor OFF    
    break;
    case 6:
      bMotor = 0; //motor OFF    
    break;  
    case 7:
      bMotor = 0; //motor OFF    
    break;
    case 8:
      bMotor = 0; //motor OFF    
    break;      
  
    default:
//      bState=0;
      bMotor = 0; //motor OFF
    break;
}
}
*/
//*******************







void setup() {
  Serial.begin(115200);
  //Serial.println("Booting");

  pinMode(led,OUTPUT);
  desligaled();
  server.on("/",[](){server.send(200,"","");});
  server.on("/Lon",ligaled);
  server.on("/Loff",desligaled);

//  N   L    S    O   N
//   NE   SE   SO  NO

  server.on("/FRONT",FRONT);
  server.on("/LEFT",LEFT);
  server.on("/BACK",BACK);
  server.on("/RIGHT",RIGHT);
  server.on("/FL",FL);
  server.on("/BL",BL);
  server.on("/BR",BR);
  server.on("/FR",FR);
  server.on("/DN",DoNothing);
  

  
  
  
  
  server.begin();

  
  WiFi.mode(WIFI_STA);
  //WiFi.config(ip, gateway, subnet);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    //Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }

  // Port defaults to 8266
  // ArduinoOTA.setPort(8266);

  // Hostname defaults to esp8266-[ChipID]
  // ArduinoOTA.setHostname("myesp8266");

  // No authentication by default
  // ArduinoOTA.setPassword("admin");

  // Password can be set with it's md5 value as well
  // MD5(admin) = 21232f297a57a5a743894a0e4a801fc3
  // ArduinoOTA.setPasswordHash("21232f297a57a5a743894a0e4a801fc3");

  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else { // U_FS
      type = "filesystem";
    }

    // NOTE: if updating FS this would be the place to unmount FS using FS.end()
    //Serial.println("Start updating " + type);
  });
  ArduinoOTA.onEnd([]() {
    //Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    //Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    //Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      //Serial.println("Auth Failed");
    } else if (error == OTA_BEGIN_ERROR) {
      //Serial.println("Begin Failed");
    } else if (error == OTA_CONNECT_ERROR) {
      //Serial.println("Connect Failed");
    } else if (error == OTA_RECEIVE_ERROR) {
      //Serial.println("Receive Failed");
    } else if (error == OTA_END_ERROR) {
      //Serial.println("End Failed");
    }
  });
  ArduinoOTA.begin();
  //Serial.println("Ready");
  //Serial.print("IP address: ");
  //Serial.println(WiFi.localIP());
}

void loop() {
  ArduinoOTA.handle();
  server.handleClient();
  //fHandleCommand(0);//bState);
 
}


 
