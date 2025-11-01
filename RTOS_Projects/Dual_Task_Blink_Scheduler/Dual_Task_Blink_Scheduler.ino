#include <Arduino_FreeRTOS.h>
#define LEDR 5
#define LEDG 6

 void LEDR_task(void *parameters){
  while(1){
    digitalWrite(LEDR,HIGH);
    vTaskDelay(pdMS_TO_TICKS(500));
    digitalWrite(LEDR,LOW);
    vTaskDelay(pdMS_TO_TICKS(500));
  }
 }

 void LEDG_task(void *parameters){
  while(1){
    digitalWrite(LEDG,HIGH);
    vTaskDelay(pdMS_TO_TICKS(200));
    digitalWrite(LEDG,LOW);
    vTaskDelay(pdMS_TO_TICKS(200));
  }
 }



void setup() {
  pinMode(LEDR,OUTPUT);
  pinMode(LEDG,OUTPUT);
  xTaskCreate(
    LEDR_task,  // Function that implements the taskx`
    "LEDR",     // Name for the task (for debugging purposes)
    128,            // Stack depth in words
    NULL,           // Parameter to pass to the task
    2,              // Task priority (0 is the lowest priority)
    NULL              // Task handle
   );
   
  xTaskCreate(
    LEDG_task,
    "LEDG",
    128,
    NULL,
    1,
    NULL
   );

  vTaskStartScheduler();
}

void loop() {

}
