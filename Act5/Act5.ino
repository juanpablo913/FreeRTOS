// Use only core 1 for demo purposes
#if CONFIG_FREERTOS_UNICORE
  static const BaseType_t app_cpu = 0;
#else
  static const BaseType_t app_cpu = 1;
#endif

// Globals
static int shared_var = 0;
static SemaphoreHandle_t mutex;

// Tasks

// Increment shared variable (the wrong way)
void incTask(void *parameters) {

  int local_var;

  // Loop forever
  while (1) {

    // Take mutex prior to critical section
    if (xSemaphoreTake(mutex, 0) == pdTRUE) {

      local_var = shared_var;
      local_var++;
      vTaskDelay(random(100, 500) / portTICK_PERIOD_MS);
      shared_var = local_var;
      
      Serial.println(shared_var);
  
      xSemaphoreGive(mutex);

    } else {
      // Do something else
    }
  }
}


void setup() {

  // Hack to kinda get randomness
  randomSeed(analogRead(0));

  Serial.begin(115200);

  vTaskDelay(1000 / portTICK_PERIOD_MS);
  Serial.println();
  Serial.println("---FreeRTOS mutexes-");

  mutex = xSemaphoreCreateMutex();

  // Start task 1
  xTaskCreatePinnedToCore(incTask,
                          "Increment Task 1",
                          1024,
                          NULL,
                          1,
                          NULL,
                          app_cpu);

  // Start task 2
  xTaskCreatePinnedToCore(incTask,
                          "Increment Task 2",
                          1024,
                          NULL,
                          1,
                          NULL,
                          app_cpu);           

  vTaskDelete(NULL);
}

void loop() {
  
}

//En este programa se time uma función que aumenta en uno el valor de la variable.
//considerando que se ejecutan 2 tareas con la misma función, la logica os diria que el valor aumentara de dos en dos
//, pero gracias a la instruccion mutex, una se ve excluida por la otra, por lo cual 
//el valor aumenta solamente de uno en uno. 
//Por esta razón el contador se ve 1 en 1 y no de más 
//
