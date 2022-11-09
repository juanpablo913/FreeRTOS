// Use only core 1 for demo purposes
#if CONFIG_FREERTOS_UNICORE
  static const BaseType_t app_cpu = 0;
#else
  static const BaseType_t app_cpu = 1;
#endif

// Settings
static const uint8_t msg_queue_len = 5;

// Globals
static QueueHandle_t msg_queue;

//*****************************************************************************
// Tasks

void printMessages(void *parameters) {

  int item;

  // Loop forever
  while (1) {

    
    if (xQueueReceive(msg_queue, (void *)&item, 0) == pdTRUE) {
    }
    Serial.println(item);

    // Wait before trying again
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}

// Main 

void setup() {

  // Configure Serial
  Serial.begin(115200);

  vTaskDelay(1000 / portTICK_PERIOD_MS);
  Serial.println();
  Serial.println("---FreeRTOS Queue Demo---");

  msg_queue = xQueueCreate(msg_queue_len, sizeof(int));

  // Start print task
  xTaskCreatePinnedToCore(printMessages,
                          "Print Messages",
                          1024,
                          NULL,
                          1,
                          NULL,
                          app_cpu);
}

void loop() {

  static int num  = 0;

  if (xQueueSend(msg_queue, (void *)&num, 10) != pdTRUE) {
    Serial.println("Queue full");
  }
  num++;

  vTaskDelay(1000 / portTICK_PERIOD_MS);
}
//Existen 2 parametros importantes que nos permiten ver el comportamiento del queue
//El tiempo de espera entre tareas y el tiempo que tarda en refrescarse
//Si ponemos el tiempo de espera más chico, se imprimirá el mismo valor hasta que llegue
//el tiempo de refresh.
//En el otro caso, ponemos el tiempo de refresca más chico y el queue se llenará de hasta que se desborde por capacidad.
