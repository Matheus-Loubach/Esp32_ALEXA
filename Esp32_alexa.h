#include "SinricPro.h"
#include "SinricProSwitch.h"
#ifdef ESP8266
#include <ESP8266WiFi.h>
#endif
#ifdef ESP32
#endif
/*----------------------------------------------------------*/
#define WIFI_SSID         "Name Wifi"
#define WIFI_PASS         "Password"
#define APP_KEY           "key SinricPro"
#define APP_SECRET        "key secret SinricPro"
/*----------------------------------------------------------*/
//Motor 
#define Exemplo_ID       "5dc1564130xxxxxxxxxxxxxx"    // exemplo "5dc1564130xxxxxxxxxxxxxx"
#define MotorDireita_PIN 2  // Pino

/*----------------------------------------------------------*/
#define BAUD_RATE         9600                // pode trocar o baud rate se for preciso
/*----------------------------------------------------------*/
void setupWiFi();
void setupSinricPro();
bool ExemploState(const String &deviceId, bool &state);

// main setup
void setup() 
{
  setupWiFi();
  setupSinricPro(); 

  pinMode(Exemplo, OUTPUT);
  digitalWrite(Exemplo, HIGH);

}

void loop() 
{
  SinricPro.handle();
}

bool ExemploState(const String &deviceId, bool &state)
{
  digitalWrite(Exemplo, !state);
  return true; 
}


//Conexões Wifi
void setupWiFi()
{
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(250);
  }
}
// setup das funções para o SinricPro
void setupSinricPro() 
{
  // add devices and callbacks to SinricPro
  SinricProSwitch &mySwitch1 = SinricPro[Exemplo_ID];
  mySwitch1.onPowerState(ExemploState);

   // setup SinricPro
  SinricPro.onConnected([](){  }); 
  SinricPro.onDisconnected([](){  });
  SinricPro.begin(APP_KEY, APP_SECRET);
}
