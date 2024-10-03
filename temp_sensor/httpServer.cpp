#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "waterTempSensor.h"
#include "metrics.h"
#include "airSensor.h"

// Create an instance of the ESP8266 WebServer on port 80
ESP8266WebServer server(80);

void handleClients(){
  server.handleClient();
}

// Handler to serve the HTML page
void handleIndex() {
  String htmlPage = R"(
  <html lang="hu">
  <head>
      <meta charset="UTF-8">
      <meta name="viewport" content="width=device-width, initial-scale=1.0">
      <title>ESP12E Temperature</title>
      <link rel="stylesheet" href="style.css">
  </head>

  <body>
      <div class="temp-container">
          <!-- Water temperature box -->
          <div class="container water-height" onclick="window.location.href = '/';">
              <div class="title-bar water">Víz</div>
              <h1>Hőmérséklete <span class="degree-symbol">(&deg;C)</span></h1>
              <p class="anton-regular">)" + String(getWaterTemperatureFloat()) + R"(</p>
          </div>

          <!-- Air temperature box with additional data -->
          <div class="container air-height" onclick="window.location.href = '/';">
              <div class="title-bar air">Levegő</div>
              <h1>Hőmérséklete <span class="degree-symbol">(&deg;C)</span></h1>
              <p class="anton-regular">)" + String(getAirTemperatureFloat()) + R"(</p>
              <h1>Páratartalom <span class="degree-symbol">(% RH)</span></h1>
              <p class="anton-regular small-value">)" + String(getAirHumidityFloat()) + R"(%</p>
              <h1>Légnyomás <span class="degree-symbol">(hPa)</span></h1>
              <p class="anton-regular small-value">)" + String(getAirPressureFloat() / 100) + R"(</p>
          </div>

          <!-- Weather of Toszeg (Idokep) -->
          <div class="container weather-height" onclick="window.location.href = 'http://www.idokep.hu/idojaras/T%C3%B3szeg';">
              <div class="title-bar weather">Időkép</div>
              <h1>Tószeg jelenlegi időjárása</h1>
          </div>
      </div>
  </body>

  </html>
)";
  
  Serial.print("[HTML] (" + String(millis()/1000) + ") Called from: ");
  Serial.println(server.client().remoteIP());
  
  server.send(200, "text/html", htmlPage);
}

// Handler to serve the CSS file
void handleCSS() {
  String css = R"(
  /* General styling */
  body {
      font-family: Arial, sans-serif;
      text-align: center;
      background-color: #f0f0f0;
      margin: 0;
      padding: 10px;
  }

  h1 {
      color: #333;
      font-size: 2em;
      margin-bottom: 10px;
  }

  p {
      font-size: 5em;
      color: #007BFF;
      margin: 0;
  }

  p.small {
      font-size: 2em;
  }

  /* Flexbox container */
  .temp-container {
      display: flex;
      flex-wrap: wrap;
      justify-content: center;
  }

  /* Default container styling */
  div.container {
      padding: 0px;
      background-color: white;
      margin: 20px;
      border-radius: 10px;
      box-shadow: 0 0 10px rgba(0, 0, 0, 0.1);
      max-width: 700px;
      display: inline-block;
      width: 100%;
  }

  /* Separate container for Water and Weather */
  div.container.water-height {
      height: 250px;  /* Standard height for Water and Weather cards */
  }

  div.container.weather-height {
      height: 180px;  /* Standard height for Water and Weather cards */
  }

  /* Taller container for Air card */
  div.container.air-height {
      height: 500px;  /* Taller height for Air card to fit additional data */
  }

  /* Responsive behavior for smaller screens */
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

  /* Temperature value styling */
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
      vertical-align: middle;
  }

  /* Smaller value for humidity and pressure */
  p.anton-regular.small-value {
      font-size: 3em;
  }

  /* Title bar for each card */
  .title-bar {
      background-color: #007BFF; /* Default color */
      color: white;
      padding: 10px;
      border-radius: 8px 8px 0 0;
      font-weight: bold;
      text-align: center;
      font-size: 1.5em;
  }

  /* Specific title bar colors */
  .water {
      background-color: #2196F3; /* Blue for water */
  }

  .air {
      background-color: #4CAF50; /* Green for air */
  }

  .weather {
      background-color: #FF9800; /* Orange for weather */
  }
)";
  
  server.send(200, "text/css", css);
}

void handleMetrics(){
  String metrics = metricsGetSystem();
  metrics += metricsGetCollectedData();

  Serial.print("[METRICS] (" + String(millis()/1000) + ") Called from: ");
  Serial.println(server.client().remoteIP());

  server.send(200, "text/plain", metrics);
}

void defineRoots(){
  server.on("/", handleIndex);
  server.on("/style.css", handleCSS);
  server.on("/metrics", handleMetrics);
}

void initHttpServer(const char* ssid, const char* password){

  Serial.print("Connecting to Wi-Fi...");
  WiFi.begin(ssid, password);

  while(WiFi.status() != WL_CONNECTED){

    Serial.print(".");
    digitalWrite(LED_BUILTIN, HIGH);
    delay(250);
    digitalWrite(LED_BUILTIN, LOW);
    delay(250);

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