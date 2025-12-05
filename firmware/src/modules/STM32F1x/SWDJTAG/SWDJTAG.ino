// CHECK THIS VIDEO TO LEARN HOW TO FLASH THE FIRMWARE TO STM32F103C8T6 : https://www.youtube.com/watch?v=L670v-Oghs4
// ALSO MAKE SURE TO DISABLE OPTIMIZATION ON COMPILER BEFORE UPLOADING

volatile int enable_send = 0;
volatile String password = "TS{JT@G+P@55W0RD}";

void setup(){
  Serial.begin(9600);
  pinMode(PA10,OUTPUT);
  pinMode(PB1, INPUT_PULLUP);
  delay(500);
  enable_send = digitalRead(PB1);
  delay(500);
}

void loop(){
  enable_send = digitalRead(PB1);
  if(!enable_send){
    digitalWrite(PA10,HIGH);
  }
  delay(3000);
  digitalWrite(PA10,LOW);
}