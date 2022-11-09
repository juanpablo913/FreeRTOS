#include <BluetoothSerial.h>
#define LED1_GPIO 5

BluetoothSerial SerialBT;
void ConfigbyBluetooth (void);
 
void setup() {
  pinMode(LED1_GPIO, OUTPUT);
  Serial.begin(115200);
  Serial.println("inicio de codigo");
}

void loop() {
    ConfigbyBluetooth();
}


void ConfigbyBluetooth(void){
  String message = "";
  String message2 = "";
  char incomingChar;
  char incomingChar2;
  bool BTHControl = true;
  SerialBT.begin("Pancha");
  Serial.println("Bluetooth disponible");
  while(BTHControl==true){
    if(SerialBT.available()){
      char incomingChar = SerialBT.read();
      if (incomingChar != '\n'){
        message += String(incomingChar);
      }
      
      else{
        message ="";
      }
      
      Serial.write(incomingChar);
    } 
    if (message == "Reset"){
      BTHControl = false;
    }
    
    if(Serial.available()){
      char incomingChar2 = Serial.read();
      if(incomingChar2 != '\n'){
        message2 += String(incomingChar2);
      }
      else{
        message2 = "";
      }
      Serial.write(incomingChar2);
    }
  }
  SerialBT.end();
}
