#include <Arduino_FreeRTOS.h>

#define RED    6
#define YELLOW 7
#define BLUE   8

typedef int TaskProfiler; // tworze profil do zadań

TaskProfiler RedLEDProfiler;  // definiuje zadania 
TaskProfiler YellowLEDProfiler;
TaskProfiler BlueLEDProfiler;

// 1.nastepnie tworzymy zadania


void setup() {
  Serial.begin(9600);
  xTaskCreate(redLedControllerTask,// funkca zadania
    "Red LED Task", // nazwa własna
    100, // rozmiar stosu
    NULL,
    1, // priorytet 0:3 0-lowest 1-low 2-higher 3-highest
    NULL // bez uchwytu
  );
  xTaskCreate(blueLedControllerTask,
    "Blue LED Task",
    100,
    NULL,
    1,
    NULL
  );
  xTaskCreate(yellowLedControllerTask,
    "Yellow LED Task",
    100,
    NULL,
    1,
    NULL
  );
  // 2.teraz tworzymy opis/treśc tych zadan co mają robić
}

void redLedControllerTask(void *pvParameters) // ten sam wskażnik co w deklaracji zadania on pokazuje na nic
{
  pinMode(RED, OUTPUT);// kunfigureuje dopiero teraz pin

  while(1)
  {
    Serial.println("This is RED");
  }
}

void blueLedControllerTask(void *pvParameters)
{
  pinMode(BLUE, OUTPUT);// kunfigureuje dopiero teraz pin

  while(1)
  {
    Serial.println("This is BLUE");
  }

} 

void yellowLedControllerTask(void *pvParameters)
{
  pinMode(YELLOW, OUTPUT);// kunfigureuje dopiero teraz pin

  while(1)
  {
    Serial.println("This is YELLOW");
  }
}

void loop(){}
