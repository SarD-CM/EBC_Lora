#include <ArduinoJson.h>

void setup() {
  Serial.begin(9600);
  }

void loop() {
  String Message = jsonMess();
  Serial.println("Hope this works"+Message);
  delay(500);
}

String jsonMess(){
  String json_string;
  StaticJsonDocument<32> doc;
  doc["s1"] = analogRead(A0) * (5.0 / 1023.0);
  doc["s2"] = 4095;
  doc["s3"] = 4094;
  doc["s4"] = 4093;
  
  serializeJson(doc,json_string);
  Serial.println("Lets see"+json_string);
  
  return json_string;
  }
