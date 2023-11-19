#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

WebServer server(80);
const char* ssid = "Arakadabra";
const char* pwd = "Pivecko12";

//Func
String HomePage();
void LoadHomePage();
void setup() 
{
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pwd);
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.println("Pripajam sa na wifi: " + String(ssid));
  }
  Serial.print("Uspesne pripojene s IP: ");
  Serial.println(WiFi.localIP());
  server.on("/", LoadHomePage);
  server.begin();
}

void loop() 
{
  server.handleClient();
}

String HomePage()
{
  String page = R"===(<!DOCTYPE html>
<html>
    <head>
        <meta charset="UTF-8">
        <title>Služba</title>
        <link rel="icon" type="icon" href="https://dodko.cloud/Semestralne-zadanie/Images/icon.png">
        <link rel="stylesheet" href="https://dodko.cloud/Semestralne-zadanie/CSS/style.css">
        
    </head>
    <body>
        <div id="background"></div>
        <h1 id="mainHeader">Hasičšký služobný systém</h1>
        <form id="loginForm" action="" method="post">            
            <input type="text" id="fname" name="fname" value="Login"><br>
            <input type="text" id="pwd" name="pwd" value="Password"><br>
            <input type="submit" value="Prihlásiť">
        </form> 
    </body>
</html>)===";
  return page;
}
void LoadHomePage()
{
  server.send(200, "text/html", HomePage());
}