// * Dos tareas se encargan de controlar el toggle de un GPIO
// * El toggle de una tarea deberá ser del doble de la frecuencia de la otra tarea.

//Configuramos los nucleos que se van a utilizar
#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else 
static const BaseType_t app_cpu =1;
#endif


 int led_pin1 =2; //Led Amarillo
static const int led_pin2 = 4; //Led Azul

//usamos un toggle al doble del otro
static const int rate_1 = 400; //ms
static const int rate_2 = 200; //ms


//Tarea para led Azul con toggle de 400ms
void toggleLED_1(void *parameter) {
  while(1) {
    digitalWrite(led_pin2, HIGH);
    vTaskDelay(rate_1 / portTICK_PERIOD_MS);
    digitalWrite(led_pin2, LOW);
    vTaskDelay(rate_1 / portTICK_PERIOD_MS);
  }
}

//Tarea para led Amarillo con toggle de 200ms
void toggleLED_2(void *parameter) {
  while(1) {
    digitalWrite(led_pin1, HIGH);
    vTaskDelay(rate_2 / portTICK_PERIOD_MS);
    digitalWrite(led_pin1, LOW);
    vTaskDelay(rate_2 / portTICK_PERIOD_MS);
  }
}


void setup() {  
  pinMode(led_pin1, OUTPUT);
  pinMode(led_pin2, OUTPUT);

//llamamos la tarea del Rojo
  xTaskCreatePinnedToCore(  
              toggleLED_1,  
              "Toggle 1",   
              1024,         
              NULL,         
              1,            
              NULL,         
              app_cpu);
                   
//llamamos la tarea del Amarillo
  xTaskCreatePinnedToCore(  
              toggleLED_2,  
              "Toggle 2",   
              1024,         
              NULL,         
              2,            
              NULL,         
              app_cpu);     
}

void loop() {

//Si le ponemos la misma prioridad a las 2 tareas, estas se empalman
//Pero si le ponemos diferentes prioridades, por un tiempo parpadearan cada una a su tiempo, hasta que 
//una la de menor prioridad se interrumpirá de vez en cuando
