//***************** Librerias *****************
#include <ArduinoJson.h>
#include <SoftwareSerial.h>

#define RXD2 14
#define TXD2 12

//***************** Variables *****************

SoftwareSerial mySerial(RXD2, TXD2);

#define TARGET_ID 1

String Message = "Hello from Dev2";   // Este es el que será la medición directa del voltaje entonces va dentro del codigo con json
String content = "";
int counter = 0;


//***************** SetUp *****************

void setup()
{
  Serial.begin(115200);
  mySerial.begin(115200);
  pinMode(0, INPUT_PULLUP);
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
  
}

//***************** Main *****************

void loop() {
  // meter 
  // String Message = jsonMess();
  // Serial.println("Hope this works"+Message);   // por ahi luego veo la logistica jajajaja
  if (Serial.available()){
    Serial.println("Writing");
    content = Serial.readString();
    content.trim();
    Serial.println();
    content = content + "\r\n";
    char* bufc = (char*) malloc(sizeof(char) * content.length() + 1);
    content.toCharArray(bufc, content.length() + 1);
    mySerial.write(bufc);
    free(bufc);
  }

  if (mySerial.available()) {
    String incomming = mySerial.readString();
    if (incomming.length() <= 10)
      Serial.println(incomming);
    else {
      String channel_ID = incomming.substring(incomming.indexOf('=') + 1, incomming.indexOf(','));
      Serial.println("Channel ID : " + channel_ID);

      String str = incomming.substring(incomming.indexOf(',') + 1);

      String msgLength = str.substring(0, str.indexOf(','));
      Serial.println("Message Length : " + msgLength);

      String str2 = str.substring(str.indexOf(',') + 1);

      String message = str2.substring(0, str2.indexOf(','));
      Serial.println("Message : " + message);

      //send confirmation message
      content = "Message received: " + message;
      sendLoraData(content, TARGET_ID);
    }
  }

  // When the button is pressed send the message to other module
  if (digitalRead(0) == LOW) {
    delay(1000);
    String data = Message + " - Count: " + counter;
    sendLoraData(data, TARGET_ID);
    //increase counter on each send
    counter++;
  }
}

//***************** Functions *****************
String jsonMess(){
   // --------> Json initiall config
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


void sendLoraData(String data, int address) {
  String myString = "AT+SEND=" + String(address) + "," + String(data.length()) + "," + data + "\r\n";
  char* buf = (char*) malloc(sizeof(char) * myString.length() + 1);
  Serial.println(myString);
  myString.toCharArray(buf, myString.length() + 1);
  mySerial.write(buf);
  free(buf);
}
