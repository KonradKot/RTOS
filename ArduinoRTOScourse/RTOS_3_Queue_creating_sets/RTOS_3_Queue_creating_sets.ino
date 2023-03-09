#include <Arduino_FreeRTOS.h>
#include "queue.h"

QueueHandle_t xQueue1;
QueueHandle_t xQueue2;// tworze dwie kolejjki a raczej wskażniki to są uchwyty

QueueSetHandle_t xQueueSet; // tworzez zbiórz kolejek


void setup()
{
  Serial.begin(9600);
  xQueue1=xQueueCreate(1,sizeof(char *));// tutja tworzę kolejkę (długośc kolejki 1, wielkosc pojedynczego obiektu obiektu 
  xQueue2=xQueueCreate(1,sizeof(char *));
                                                                    // ----b
  xQueueSet = xQueueCreateSet(2); // tworze zbiór dwóch kolejek set---
                                                                    // ----c
  xQueueAddToSet(xQueue1,xQueueSet); //tutaj dodaję do zbioru zwoją kolejkę 
  xQueueAddToSet(xQueue2,xQueueSet); // tworze drzewo kolejek, które składa się z dwóch podgałęźi

  xTaskCreate(vSenderTask1,"Sender Task 1",100,NULL,1,NULL); // tworze zadania dla swoich kolejek tu akurat dane wysyłane przez sender1
  xTaskCreate(vSenderTask2,"Sender Task 2",100,NULL,1,NULL); // tutaj wysyłam inforamcje kolejki drugiej

  xTaskCreate(vReceiverTask,"ReceiverTask",100,NULL,2,NULL); // tu przychodzą informację priorytet zadania otrymwanego jest zawsze wyższy
}

void vSenderTask1(void *pvParameters)
{
  const TickType_t xBlockTime = pdMS_TO_TICKS(200);// konwertuję ms do tików
  const char *const messageToSend = "Message from Sender 1"; // wiadmość do wysłania typu char jest stały wskażnik na stały obiekt
  while(1)
  {
    vTaskDelay(xBlockTime);// opóżnienie zadania o 200ms
    xQueueSend(xQueue1,&messageToSend,0);
  }
}

void vSenderTask2(void *pvParameters)
{
  const TickType_t xBlockTime = pdMS_TO_TICKS(200);
  const char *const messageToSend = "Hellow from Sender 2";
  while(1)
  {
    vTaskDelay(xBlockTime);
    xQueueSend(xQueue2,&messageToSend,0);
  }
}

void vReceiverTask(void *pvParameters)
{
  QueueHandle_t xQueueThatContainData; //tworze wskażnik do otrzymanych danych 
  char *pcReceivedString; // tutja tworze wskaźnik do otrzymanego stringa, ponieważ przesyłam wskaźniki nie obiekty statyczne
  while(1)
  {
    xQueueThatContainData = (QueueHandle_t)xQueueSelectFromSet(xQueueSet,portMAX_DELAY);// chodzi o to że otrzymauję zbiór informacji/obiektów i podczepiam je do wskażnika
    xQueueReceive(xQueueThatContainData,&pcReceivedString,0);
    Serial.println(pcReceivedString);
  }

  
}

void loop() {}
