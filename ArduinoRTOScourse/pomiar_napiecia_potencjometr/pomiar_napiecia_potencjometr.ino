#define Analog_channel_pin 0
#define control 5
#define lowD 6
#define highD 7
#define highestD 8

int ADC_VALUE =0;
int voltage=0;
int last=0;
int now=0;
void setup()
{
  Serial.begin(9600);
  pinMode(control, OUTPUT);
}


void loop(){
  ADC_VALUE = analogRead(Analog_channel_pin);
 // Serial.print("ADC ValUE = ");
  //Serial.println(ADC_VALUE);
  voltage =(ADC_VALUE * 3.3*3)/(2048); // bo zasilanie tyle wynosi
  now=voltage;
  if(now!=last){
    digitalWrite(control, HIGH);
    delay(300);
  }
  last=now;
  if(voltage>=1){
    digitalWrite(lowD, HIGH);
  }
  else{
    digitalWrite(lowD, LOW);
  }
  if (voltage >=2)
  {
    digitalWrite(highD, HIGH);
  }
  else{
    digitalWrite(highD, LOW);
  }
  if( voltage >=3)
  {
    digitalWrite(highestD, HIGH);
  }
  else
  {
    digitalWrite(highestD, LOW);
  }
  digitalWrite(control,LOW);
  Serial.print("Voltage: ");
  Serial.print(voltage);
  Serial.print(" V ");
  Serial.println(" ");
  delay(1000);
}
