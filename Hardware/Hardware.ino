// LifeSense-V0.1
// A Project for SIH202
// By Team: Runtime Terror


#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#define DEVICE_ID "A7-01"
#define SENSOR_TYPE 1
#define CURRENT_LEVEL 3
#define MIN_LEVEL 0
#define MAX_LEVEL 5
#define CONFIDENCE 1
#define USE_SERIAL Serial
#define SERVER_IP "192.168.43.43:8000"
#define UA "LifeSense-V0.1"

#define PIN_COUNT 6
int PINS[6] = { 0,2,4,5,14,16 };

#ifndef STASSID
#define STASSID "Galaxy A50"
#define STAPSK  "zebrafamily"
#endif

void setup() {

  for ( int index = 0 ; index < PIN_COUNT , index++) {
  pinMode( PINS[index] , OUTPUT);
  }
  
  USE_SERIAL.begin(115200);
  USE_SERIAL.println();
  USE_SERIAL.println();
  USE_SERIAL.println();

  

  WiFi.begin(STASSID, STAPSK);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    USE_SERIAL.print(".");
  }
  USE_SERIAL.println("");
  USE_SERIAL.print("Connected! IP address: ");
  USE_SERIAL.println(WiFi.localIP());

}

void loop() {
  // wait for WiFi connection

  for ( int index = 0 ; index < PIN_COUNT , index++) {
  DIGITAL( PINS[index] , OUTPUT);
  }
  
  if ((WiFi.status() == WL_CONNECTED)) {

    WiFiClient client;
    HTTPClient http;

    USE_SERIAL.print("[HTTP] begin...\n");
    // configure traged server and url
    
    http.begin(client, "http://" SERVER_IP); //HTTP
    http.setUserAgent(UA);
    http.addHeader("From", DEVICE_ID);
    http.addHeader("Content-Type", "application/json");

    USE_SERIAL.print("[HTTP] POST...\n");
    // start connection and send HTTP header and body

    char buff[10000];
    sprintf(buff,
    "{\"Device-Id\":\"%s\" , \"Sensor-Type: %d\" , \"Current-Level\": \"%d\" , \"Min-Level\" : \"%d\" , \"Max-Level\" : \"%d\" , \"Confidence\" : \"%d\" }"
      , DEVICE_ID , SENSOR_TYPE , CURRENT_LEVEL , MIN_LEVEL , MAX_LEVEL , CONFIDENCE  );
    
    int httpCode = http.POST(buff);

    // httpCode will be negative on error
    if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
      USE_SERIAL.printf("[HTTP] POST... code: %d\n", httpCode);

      // file found at server
      if (httpCode == HTTP_CODE_OK) {
        const String& payload = http.getString();
        USE_SERIAL.println("Recived Data:\n---------");
        USE_SERIAL.println(payload);
        USE_SERIAL.println("End of recived data.");
      }
    } else {
      USE_SERIAL.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();
  }

  delay(10000);
}
