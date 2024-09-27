#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "waterTempSensor.h"

// WiFi credentials
#define SSID ""
#define PASSWORD ""

// Create an instance of the ESP8266 WebServer on port 80
ESP8266WebServer server(80);

void handleClients(){
  server.handleClient();
}

// Handler to serve the HTML page
void handleIndex() {
  String htmlPage = R"(
  <!DOCTYPE html>
  <html>
  <head>
      <title>ESP12E Temperature</title>
      <link rel="stylesheet" href="/style.css">
      <meta charset="UTF-8">
  </head>
  <body>
      <div class="container">
          <h1>Current Temperature</h1>
          <p>The current temperature is: )" + getTemperatureString() + R"(</p>
      </div>
  </body>
  </html>
  )";
  
  Serial.print("Called from: ");
  Serial.println(server.client().remoteIP());

  server.send(200, "text/html", htmlPage);
}

// Handler to serve the CSS file
void handleCSS() {
  String css = R"(
  body {
      font-family: Arial, sans-serif;
      text-align: center;
      background-color: #f0f0f0;
  }
  h1 {
      color: #333;
  }
  p {
      font-size: 1.5em;
      color: #007BFF;
  }
  div.container {
      padding: 20px;
      background-color: white;
      margin: 50px auto;
      border-radius: 10px;
      box-shadow: 0 0 10px rgba(0,0,0,0.1);
      max-width: 600px;
  }
  )";
  
  server.send(200, "text/css", css);
}

void defineRoots(){
  server.on("/", handleIndex);
  server.on("/style.css", handleCSS);
}

void initHttpServer(){

  Serial.print("Connecting to Wi-Fi...");
  WiFi.begin(SSID, PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("\nConnected to Wi-Fi!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  
  defineRoots();
  
  // Start the server
  server.begin();
  Serial.println("HTTP server started");
}