#define btn 2


void setup() {
  pinMode (btn, INPUT_PULLUP);
  Serial.begin (115200);

}

void loop() {
  if (digitalRead(btn) == 0) {
    delay(500);
    if(digitalRead(btn) == 0){
      while(digitalRead(btn) == 0){
      Serial.println("Boton Presionado");
      delay(500);
      }
        }
  }
  else {
    Serial.println("Boton No presionado");
  }
  delay(1000);
}

// La conexion va de Gnd a una patita del boton
// y la otra patita del mismo lado a IO2
