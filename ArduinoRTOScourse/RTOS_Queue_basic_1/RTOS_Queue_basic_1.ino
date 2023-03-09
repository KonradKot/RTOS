#include<Arduino_FreeRTOS.h>
#include "queue.h"

QueueHandle_t yearQueue; // deklarujemy kolejkę od jej nazwy

void setup()
{
  Serial.begin(9600);
  yearQueue = xQueueCreate(5,sizeof(int32_t));//32 bity
  // pierwszy argument to liczba obiektów, które będąna kolejce
  // drugi argument to rozmiar obiektu

  xTaskCreate(vSenderTask,"Sender Task",100,NULL,1,NULL);
  // tworze zadanie, 1. zadanie wysyłania dancych,
  xTaskCreate(vReceiverTask,"Receiver Task",100,NULL,1,NULL);
}

void vSenderTask(void *pvParameters)
{
  BaseType_t qStatus; // potrzebne do wykrywania błędów
  int32_t valueToSend = 2018;
  while(1)
  {
    qStatus=xQueueSend(yearQueue, &valueToSend,0) ;// ostatni argument to czas na wysłanie
  }// przesyłamy skzażniki
}
void vReceiverTask(void *pvParameters)
{
  BaseType_t qStatus;
  int32_t valueReceived;
  const TickType_t xTicksToWait = pdMS_TO_TICKS(100);
  // ilośćc czasu na uczekiwanie
  while(1)
  {
    xQueueReceive(yearQueue,&valueReceived,xTicksToWait);
    Serial.print("Received value: ");
    Serial.println(valueReceived); // wyswietlam otrzymane wartosci
    vTaskDelay(10);
  }
}


void loop(){}
