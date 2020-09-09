// TAKES IN DATA FROM SERIAL MONITOR AND SENDS IT THROUGH LORA IN BROADCAST MANNER.

#include <SoftwareSerial.h>                           //we have to include the SoftwareSerial library, or else we can't use it
#define rx 13                                          //LORA TX
#define tx 15                                          //LORA RX
String incomingString;
String PrStr;                                           // String used to print the incoming string after decoding it

SoftwareSerial myserial(rx, tx);                      //define how the soft serial port is going to work


void setup() {
  Serial.begin(115200);
  myserial.begin(115200);

}

void loop() {
  if (Serial.available()){
        incomingString = Serial.readString();
          if(incomingString.length()>2){
          Serial.print("YOU: ");
          Serial.println(incomingString);
          String messStr = "AT+SEND=0,";              // messStr(AT COMMAND) is to be sent to the LoRa module to send the relavant data
          messStr += (incomingString.length()-2);
          messStr += ",";
          messStr += incomingString;
          myserial.print(messStr);
          }
    }

   else if (myserial.available()){                  // this will read the incomming data from the lora and decode it and print it on serial monitor
        incomingString = myserial.readString();
        String recTest = incomingString.substring(1,4);
        if(recTest == "RCV"){
        String messagesize;
        int addr_start = incomingString.indexOf(',');
        int addr_mid = incomingString.indexOf(',', addr_start + 1);
        messagesize = incomingString.substring(addr_start + 1, addr_mid);
        PrStr = incomingString.substring(addr_mid + 1, (addr_mid + 1 + messagesize.toInt()));
        Serial.print("HIM: ");
        Serial.println(PrStr);
        }
    }

}
