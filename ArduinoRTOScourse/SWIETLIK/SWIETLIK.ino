#include <Arduino_FreeRTOS.h>
#define RED 6
#define YELLOW 7
#define BLUE 8
#define GREEN 9

const TickType_t _500ms = pdMS_TO_TICKS(500);

void setup() {
  xTaskCreate(xSwietlikTask,"ledowo",100,NULL,1,NULL);

}

void xSwietlikTask(void *pvParameters)
{
  pinMode(RED,OUTPUT);
  pinMode(YELLOW,OUTPUT);
  pinMode(BLUE,OUTPUT);
  pinMode(GREEN,OUTPUT);

  while(1)
  {
    digitalWrite(RED,HIGH);
    vTaskDelay(4*_500ms);
    digitalWrite(GREEN,LOW);
    digitalWrite(YELLOW,HIGH);
    vTaskDelay(4*_500ms);
    digitalWrite(RED,LOW);
    digitalWrite(BLUE,HIGH);
    vTaskDelay(4*_500ms);
    digitalWrite(YELLOW,LOW);
    digitalWrite(GREEN,HIGH);
    vTaskDelay(4*_500ms);
    digitalWrite(BLUE,LOW);
    
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
