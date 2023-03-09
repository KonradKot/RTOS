#include<Arduino_FreeRTOS.h>
#include "queue.h"
#define RED 6
#define YELLOW 7
#define BLUE 8

typedef int TaskProfiler;
TaskProfiler SenderTaskProfiler;
TaskProfiler ReceiverTaskProfiler;

QueueHandle_t NFZQueue; // tworzę nowy wskażnik do kolejki/listy root

void setup()
{
  Serial.begin(9600);
  NFZQueue = xQueueCreate(5,sizeof(int32_t)); //teraz definuje kolejkę ilość elementó i rozmiar każdego z obiekty

  xTaskCreate(vSenderTask,"Sender Task 1",100,1999,1,NULL); // podaję tutaj elemnt, który będzie wysyłany
  xTaskCreate(vSenderTask,"Sender Task 2",100,2019,1,NULL);
  xTaskCreate(vReceiverTask,"Receiver Task",100,NULL,2,NULL); // otrzymywanie wyższy priorytet
}

void vSenderTask(void *pvParameters)
{
  pinMode(RED,OUTPUT);
  BaseType_t qStatus; // znacznik statusu przesłaia danych
  int32_t valueToSend; // informacja wysyłan będzie typu int 32bitowa
  valueToSend = (int)pvParameters; // casting zmiennej,,, teraz to na co pokazuję wskaźnik pvParameters bedzie przypisane do value to send czyli adres nie wartość
  // 

  while(1)
  {
    qStatus=xQueueSend(NFZQueue,&valueToSend,0); //wysyłam informacje(na jaka kolejke, &(weartość do wysłania jako wartość a nie adres))
    if(qStatus != pdPASS)// pdPASS czyli dane przeszły przez koolejke
    {
      Serial.println("Could not send to the queue");
      for(int i=0;i<30000;i++){};// opóźnienie
    }
    digitalWrite(RED,HIGH);
  }
  
}
void vReceiverTask(void *pvParameters)
{
  pinMode(RED,OUTPUT);
  BaseType_t qStatus;
  int32_t valueReceived;
  const TickType_t xTicksToWait = pdMS_TO_TICKS(100);
  while(1)
  {
    qStatus=xQueueReceive(NFZQueue,&valueReceived,xTicksToWait);//status jest równy (nazwa kolejki, otrzymana wartoć, czas na kolejce) 
// uwaga ten status tu musi byc
    if(qStatus == pdPASS)
    {
      Serial.print("Data received succinessfully: ");
      Serial.println(valueReceived);
      Serial.print(" ");
      Serial.println(xTicksToWait);
      for(int i=0;i<30000;i++){};
    }
    else{
      Serial.println("Could not receive from queue");
    }
    digitalWrite(RED,LOW);
  }
}
void loop(){}
