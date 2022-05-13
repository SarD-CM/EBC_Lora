//--------> Code used to develop the json serialization and deserialization

#include <ArduinoJson.h>

void setup() {
  Serial.begin(9600);
  }

void loop() {
  //String Message = jsonMess();    //For serialization 
  StaticJsonDocument<32> doc;       //For deserialization 
  char message[] = "{\"s1\":5.4,\"s2\":2.4,\"s3\":3.4,\"s4\":4.4}";  // Would prefer to put this in a function
  DeserializationError error = deserializeJson(doc, message);  // oh well
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
  }

  double sen1 = doc["s1"];
  double sen2 = doc["s2"];
  double sen3 = doc["s3"];
  double sen4 = doc["s4"];
  Serial.print("Hope this works s1:");
  Serial.println(sen1);
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

//WHATINGODSNAMEAREYOU jsonNoMore(String Message){
  //Oh were you expecting a formal name?
  
//  }
