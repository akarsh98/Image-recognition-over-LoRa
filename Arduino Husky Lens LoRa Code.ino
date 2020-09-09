#include "HUSKYLENS.h"
#include "SoftwareSerial.h"

HUSKYLENS huskylens;
SoftwareSerial mySerial(10, 11); // RX, TX
//HUSKYLENS green line >> Pin 10; blue line >> Pin 11
void printResult(HUSKYLENSResult result);
String incomingString;

void setup() {
    Serial.begin(115200);
    mySerial.begin(9600);
    while (!huskylens.begin(mySerial))
    {
        Serial.println(F("Begin failed!"));
        Serial.println(F("1.Please recheck the \"Protocol Type\" in HUSKYLENS (General Settings>>Protocol Type>>Serial 9600)"));
        Serial.println(F("2.Please recheck the connection."));
        delay(100);
    }
}

void loop() {
    if (!huskylens.request()) {
      incomingString = (F("Fail to request data from HUSKYLENS, recheck the connection!"));
      if(incomingString.length()>2){
      String messStr = "AT+SEND=0,";              // messStr(AT COMMAND) is to be sent to the LoRa module to send the relavant data
      messStr += (incomingString.length());
      messStr += ",";
      messStr += incomingString;
      Serial.println(messStr);
    }
    }
    else if(!huskylens.isLearned()) {
      incomingString = (F("Nothing learned, press learn button on HUSKYLENS to learn one!"));
      if(incomingString.length()>2){
      String messStr = "AT+SEND=0,";              // messStr(AT COMMAND) is to be sent to the LoRa module to send the relavant data
      messStr += (incomingString.length());
      messStr += ",";
      messStr += incomingString;
      Serial.println(messStr);
    }
    }
    else if(!huskylens.available()) {
      incomingString = "No block or arrow appears on the screen!";
      if(incomingString.length()>2){
      String messStr = "AT+SEND=0,";              // messStr(AT COMMAND) is to be sent to the LoRa module to send the relavant data
      messStr += (incomingString.length());
      messStr += ",";
      messStr += incomingString;
      Serial.println(messStr);
    }
    }
    else
    {
        while (huskylens.available())
        {
            HUSKYLENSResult result = huskylens.read();
            printResult(result);
        }    
    }
    delay(3000);
}

void printResult(HUSKYLENSResult result){
    if (result.command == COMMAND_RETURN_BLOCK){
        incomingString = (String()+F("Block:xCenter=")+result.xCenter+F(",yCenter=")+result.yCenter+F(",width=")+result.width+F(",height=")+result.height+F(",ID=")+result.ID);
    }
    else if (result.command == COMMAND_RETURN_ARROW){
        incomingString = (String()+F("Arrow:xOrigin=")+result.xOrigin+F(",yOrigin=")+result.yOrigin+F(",xTarget=")+result.xTarget+F(",yTarget=")+result.yTarget+F(",ID=")+result.ID);
    }
    else{
        incomingString = ("Object unknown!");
    }
    if(incomingString.length()>2){
      String messStr = "AT+SEND=0,";              // messStr(AT COMMAND) is to be sent to the LoRa module to send the relavant data
      messStr += (incomingString.length());
      messStr += ",";
      messStr += incomingString;
      Serial.println(messStr);
    }
}
