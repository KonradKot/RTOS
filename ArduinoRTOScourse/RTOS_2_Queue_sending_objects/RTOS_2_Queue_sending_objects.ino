#include<Arduino_FreeRTOS.h>
#include "queue.h"

typedef int TaskProfiler;

TaskProfiler SenderProfiler;
TaskProfiler ReceiverProfiler;

typedef enum
{
  eSender1, // tworze typy zmiennych
  eSender2,
}DataSource_t; //żródło danych

typedef struct // tworze struktórę
{
  uint8_t ucValue;
  DataSource_t eDataSource;
}Data_t;

static const Data_t xStructToSend[2]= // tworze listę z obiektó
{
  {100, eSender1},
  {50, eSender2}
};

QueueHandle_t NFZQueue;

void setup()
{
  Serial.begin(9600);
  NFZQueue=xQueueCreate(3,sizeof(Data_t)); // rozmiar danych struktury
  
  xTaskCreate(vSenderTask,"Sender Task 1",100,&(xStructToSend[0]),2,NULL);
  // przesyłam adres do funkcji
  xTaskCreate(vSenderTask,"Sender Task 2",100,&(xStructToSend[1]),2,NULL);

  xTaskCreate(vReceiverTask,"Receiver Task 3",100,NULL,1,NULL);
  
}

void vSenderTask (void *pvParameters)
{
 // pinMode(RED,OUTPUT);
  BaseType_t xStatus;
  const TickType_t xTicksToWait = pdMS_TO_TICKS(100);
  while(1)
  {
    xStatus=xQueueSend(NFZQueue,pvParameters,xTicksToWait);
    if(xStatus != pdPASS) // tu musi byc przerwa
    {
    Serial.println("Could not send to the queue");
    //vTaskDelay(100);
    }
    //digitalWrite(RED,HIGH);
  }
}

void vReceiverTask(void *pvParameters)
{
  //pinMode(RED,OUTPUT);
  Data_t xReceivedStructure; // ma pd. zdefiniowanej struktury 
  // tworze dla własnego typu danych zmienną coś jak Kulka p1(3,3)
  BaseType_t xStatus;
  //const TickType_t xTicksToWait = pdMS_TO_TICKS(100);
  // konwertuje ticki do ms
  while(1)
  {
    xStatus = xQueueReceive(NFZQueue,&xReceivedStructure,0);
    if(xStatus == pdPASS)
    {
     // Serial.print(xStatus);
      if(xReceivedStructure.eDataSource == eSender1)
      {
      Serial.print("Data send succesffully ! ");
      Serial.println(xReceivedStructure.ucValue);
      }
      else
      {
      Serial.print("This is from sender 2: ");
      Serial.println(xReceivedStructure.ucValue);
      }
    }
    else
    {
      Serial.println("Could not received a structure");
    }
  }
}

void loop(){}
