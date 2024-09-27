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
  <html lang="hu"> <!-- Added language attribute for Hungarian -->
  <head>
      <meta charset="UTF-8">
      <meta name="viewport" content="width=device-width, initial-scale=1.0"> <!-- Responsive meta tag -->
      <title>ESP12E Temperature</title>
      <link rel="stylesheet" href="/style.css">
      <meta charset="UTF-8">
  </head>

  <body>
      <div class="temp-container">
          <!-- Water temperature box -->
          <div class="container" onclick="window.location.href = '/';">
              <h1>Víz hőmérséklete <span class="degree-symbol">(&deg;C)</span></h1>
              <p class="anton-regular">)" + String(getWaterTemperatureFloat()) + R"(</p>
          </div>

          <!-- Air temperature box -->
          <div class="container" onclick="window.location.href = '/';">
              <h1>Levegő hőmérséklete <span class="degree-symbol">(&deg;C)</span></h1>
              <p class="anton-regular">)" + String(getWaterTemperatureFloat()) + R"(</p>
          </div>

          <!-- Weather of Toszeg (Idokep) -->
          <div class="container" onclick="window.location.href = 'http:\/\/www.idokep.hu/idojaras/T%C3%B3szeg';">
              <h1>Időkép</h1>
              <p class="small">Tószeg jelenlegi időjárása</p>
          </div>
        </div>
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
      margin: 0;
      padding: 10;
  }

  h1 {
      color: #333;
      font-size: 2em;
  }

  p {
      font-size: 5em;
      color: #007BFF;
      margin: 0;
  }

  p.small {
    font-size: 2em;
  }

  div.container {
      padding: 20px;
      background-color: white;
      margin: 20px;
      border-radius: 10px;
      box-shadow: 0 0 10px rgba(0, 0, 0, 0.1);
      max-width: 700px;
      display: inline-block;
      width: 100%;
  }

  /* Flexbox container */
  .temp-container {
      display: flex;
      flex-wrap: wrap;
      justify-content: center;
  }

  /* Style for smaller screens */
  @media (max-width: 768px) {
      div.container {
          max-width: 90%;
          margin: 10px auto;
      }
  }

  /* Style for larger screens */
  @media (min-width: 768px) {
      div.container {
          flex: 1 1 45%; /* Takes up 45% of the screen width on large screens */
          margin: 10px;
      }
  }

  /* Style for the temperature and °C symbol in a single row */
  .anton-regular {
      display: inline-block;
      font-family: "Anton", sans-serif;
      font-weight: 800;
      font-style: normal;
      font-size: 5em;
      color: #007BFF;
  }

  .degree-symbol {
      font-size: 0.5em;
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

  Serial.println("\n-------------------------------------");
  Serial.println("Connected to Wi-Fi!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.print("MAC Address: ");
  Serial.println(WiFi.macAddress());
  Serial.println("-------------------------------------");
  
  defineRoots();
  
  // Start the server
  server.begin();
  Serial.println("HTTP server started");
}