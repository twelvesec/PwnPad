/*

Copyright (C) 2025 TwelveSec

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.

*/


/*************************** LIBRARIES ******************************/
#include <Arduino.h>  
#include <Wire.h>
#include <SoftwareSerial.h>
#include <stdio.h>
#include <stdlib.h>
/*************************** DEFINED PINS ******************************/

#define MOD1 9
#define MOD2 A3
#define MOD3 A2
#define MOD4 A1
#define MOD5 A0

#define LED_0 2
#define LED_1 3
#define LED_2 4

#define BTN_DOT 5
#define BTN_DASH 6
#define BTN_SPACE 8
#define BTN_OK 7

#define SPEED 250
/*************************** FUNCTION DEFINITIONS ******************************/

// ========>>>> INITIALIZERS
void initialize(void);
int modeReader(void) ;
void challengeSelector(int mode);

// ========>>>> CHALLENGES
void handheld_challenge_uart(void);
void handheld_challenge_uart_v2(void);
void handheld_challenge_i2c(void);
void handheld_challenge_i2c_v2(void);
void handheld_challenge_firmware_extraction(void);
void handheld_challenge_voltage_glitch(void);
void handheld_challenge_voltage_glitch_v2(void);
void handheld_challenge_side_channel_timing_attack(void);
void handheld_challenge_side_channel_timing_attack_v2(void);
void blackbox_chain_UART_Glitch_Attack(void);
void blackbox_chain_UART_Timing_Attack(void);
// =========>>>> HELPER FUNCTIONS
void morseMessager(String morse, int speed);
/*******************************************************************************/ 

void setup(){
  initialize();
  Serial.println("------------------------"); // TO BE REMOVED
  modeReader(); //helps for steadier digitalRead for some reason
  challengeSelector(modeReader());
}


void loop()
{
  Serial.print(".");  // TO BE REMOVED
  delay(1000);
}




  

/*************************** FUNCTIONS ******************************/

void initialize(void){
  pinMode(MOD1, INPUT);
  pinMode(MOD2, INPUT);
  pinMode(MOD3, INPUT);
  pinMode(MOD4, INPUT);
  pinMode(MOD5, INPUT);
}


int modeReader(void) {
  delay(1000);
  int bits[5];
  bits[4] = digitalRead(MOD1);
  delay(20);
  bits[3] = digitalRead(MOD2);
  delay(20);
  bits[2] = digitalRead(MOD3);
  delay(20);
  bits[1] = digitalRead(MOD4);
  delay(20);
  bits[0] = digitalRead(MOD5);
  delay(20);
  int mode = 0;
  for (int i = 0; i < 5; i++) {
    mode |= (bits[i] << (4 - i)); // MOD1 is the highest bit
  }
  return mode;
}

void challengeSelector(int mode){
  switch(mode){
	case 1: // 00001
      handheld_challenge_uart();
      break;
    case 2: // 00010
      handheld_challenge_uart_v2();
      break;
    case 3: // 00011
      handheld_challenge_i2c();
      break;
    case 4: // 00100
      handheld_challenge_i2c_v2();
      break;
    case 5: // 00101
      handheld_challenge_firmware_extraction();
      break;
    case 6: // 00110
      // No need extract code, eeprom has been written.
      break;
    case 7: // 00111
      handheld_challenge_voltage_glitch();
      break;
    case 8: // 01000
      handheld_challenge_voltage_glitch_v2();
      break;
    case 9: // 01001
      handheld_challenge_side_channel_timing_attack();
      break;
    case 17: // BUG ! Probably Hardware Changed To 17 For Stability 10001
      handheld_challenge_side_channel_timing_attack_v2();
      break;
    case 16: // BUG ! Probably Hardware Changed To 16 For Stability 10000
      blackbox_chain_UART_Glitch_Attack();
      break; 
    case 12: // 01100
      blackbox_chain_UART_Timing_Attack();
      break;
    default:
      Serial.println("No Challenge Selected!"); // TO BE REMOVED
  }
}

// ======================>>> CHALLENGES

void handheld_challenge_uart(){

  int LED_0_STATE = 1;
  int LED_1_STATE = 1;
  int LED_2_STATE = 1;

  Serial.begin(9600);

  pinMode(LED_0, OUTPUT);
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  
  digitalWrite(LED_0, LED_0_STATE);
  digitalWrite(LED_1, LED_1_STATE);
  digitalWrite(LED_2, LED_2_STATE);

  Serial.println("+=========== Welcome To The UART Challenge ===========+");
  Serial.println("|       You Successfully Identified The Baudrate      |");
  Serial.println("|            You Can Now Control The LEDS             |");
  Serial.println("|                 TS{U@rt_15_@w3s0m3}                 |");
  Serial.println("+=====================================================+\n\n");

  while(1) {

    Serial.print("\nSELECT LED (1/2/3) > ");
    while(Serial.available() <= 0){};

    while (Serial.available() > 0) {
      char led = Serial.read();
      Serial.println(led);
      if (led != '1' && led != '2' && led != '3'){
        Serial.println("\nError Wrong Id !");
      }
      else{
        Serial.print("\nSELECT STATUS (0/1) > ");
        while(Serial.available() <= 0){};   
        char status = Serial.read();
        Serial.println(status);
        if (status != '1' && status != '0'){
          Serial.println("\nSomething Went Wrong!");
          break;
        }

        if (led == '1'){
          if (status == '1'){
            digitalWrite(LED_0, HIGH);
          }
          else{
            digitalWrite(LED_0, LOW);
          }
        }

        if (led == '2'){
          if (status == '1'){
            digitalWrite(LED_1, HIGH);
          }
          else{
            digitalWrite(LED_1, LOW);
          }
        }

        if (led == '3'){
          if (status == '1'){
            digitalWrite(LED_2, HIGH);
          }
          else{
            digitalWrite(LED_2, LOW);
          }
        }
      }
    }
  }
}

void handheld_challenge_uart_v2(){
    Serial.begin(31337);
    delay(10);
    while(1){
      Serial.println("TS{N0w_Y0u_@r3_@n_el173_H@(k3r}");
      delay(2000);
    }
}

void handheld_challenge_i2c(){
  String OTP = "TS{(h@||eng3_07P_i5_"; 

  Wire.begin(); 
  randomSeed(analogRead(0));

  for (int r=0; r < 10; r++)
  {
    OTP += String(random(10));
  }

  OTP += "}";

  while(1) { 
    for (int i=0; i < OTP.length(); i++){
      Wire.beginTransmission(OTP.charAt(i)); 
      Wire.endTransmission();   
    }
    delay(1000);
  }
}


void handheld_challenge_i2c_v2(){
  String OTP = "TS{1_N33D_/\\/\\y_8u66y}"; 
  Wire.begin(); 

  while(1) { 
    Wire.beginTransmission(0x12); 
    Wire.write(OTP.c_str());       
    Wire.endTransmission();   
    delay(500);
  }
}

void morseMessager(String morse, int speed){

  digitalWrite(LED_0, LOW);
  digitalWrite(LED_1, LOW);
  digitalWrite(LED_2, LOW);
  delay(speed * 2);

  for (int i=0; i < morse.length(); i++){
    if (morse.charAt(i) == '.') {   
        delay(speed);    
        digitalWrite(LED_2, HIGH);
        delay(speed);
        digitalWrite(LED_2, LOW);
    }

    if (morse.charAt(i) == '-') {
        delay(speed);           
        digitalWrite(LED_0, HIGH);
        digitalWrite(LED_1, HIGH);
        delay(speed);
        digitalWrite(LED_0, LOW);
        digitalWrite(LED_1, LOW);
    }

    if (morse.charAt(i) == ' ') {
        delay(speed * 2);    
        digitalWrite(LED_0, LOW);
        digitalWrite(LED_1, LOW);   
        digitalWrite(LED_2, LOW);
        delay(speed * 2);
    }
  }

  delay(speed * 2);
  digitalWrite(LED_0, HIGH);
  digitalWrite(LED_1, HIGH);
  digitalWrite(LED_2, HIGH);
}

void handheld_challenge_firmware_extraction(){
  const char SECRET[] = "- .-- ...-- .-.. ...- . ..... ...-- -.-."; // TW3LVE53C

  int LED_0_STATE = 1;
  int LED_1_STATE = 1;
  int LED_2_STATE = 1;

  char MorseInput[60] = {'\0'};
  int morse_index = 0;

  bool flag = true;

  pinMode(LED_0, OUTPUT);
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  
  pinMode(BTN_DOT, INPUT);
  pinMode(BTN_DASH, INPUT);
  pinMode(BTN_OK, INPUT);
  pinMode(BTN_SPACE, INPUT);

  digitalWrite(LED_0, LED_0_STATE);
  digitalWrite(LED_1, LED_1_STATE);
  digitalWrite(LED_2, LED_2_STATE);
  
  Serial.begin(9600);

  while(1){
    
    Serial.println(MorseInput);

    if (digitalRead(BTN_DOT) == HIGH){
      MorseInput[morse_index] = '.';
      morse_index++;
      if(morse_index == 40){
        morse_index = 0;
      }
      delay(300);
    }
    
    if (digitalRead(BTN_DASH) == HIGH){
      MorseInput[morse_index] = '-';
      morse_index++;
      if(morse_index == 40){
        morse_index = 0;
      }
      delay(300);
    }
    
      
    if (digitalRead(BTN_SPACE) == HIGH){
      MorseInput[morse_index] = ' ';
      morse_index++;
      if(morse_index == 40){
        morse_index = 0;
      }
      delay(300);
    }
      
    if (digitalRead(BTN_OK) == HIGH){
      delay(10);
      if (strcmp(MorseInput , SECRET) == 0){
        Serial.println("SECTER MODE UNLOCKED: TS{F1rmw@re_S3cret}");  
        while(true){
          digitalWrite(LED_0, HIGH);
          delay(100);
          digitalWrite(LED_0, LOW);
          delay(100);
          digitalWrite(LED_1, HIGH);
          delay(100);
          digitalWrite(LED_1, LOW);
          delay(100);
          digitalWrite(LED_2, HIGH);
          delay(100);
          digitalWrite(LED_2, LOW);
          delay(100);
        }
      }
      else
      {
          digitalWrite(LED_0, HIGH);
          digitalWrite(LED_1, HIGH);
          digitalWrite(LED_2, HIGH);
          delay(500);
          digitalWrite(LED_0, LOW);
          digitalWrite(LED_1, LOW);
          digitalWrite(LED_2, LOW);
          delay(500);
          digitalWrite(LED_0, HIGH);
          digitalWrite(LED_1, HIGH);
          digitalWrite(LED_2, HIGH);
      }
      delay(500);
      morse_index = 0;
      memset(MorseInput, '\0', sizeof(MorseInput));
    }
  }
}

void handheld_challenge_voltage_glitch(){
  const int TRIGGER = A4; // SDA 
  volatile uint16_t i;
  volatile uint16_t j;
  volatile uint32_t cnt;
  int MAX = 200;

  Serial.begin(9600);
  pinMode(TRIGGER, OUTPUT);
  digitalWrite(TRIGGER, LOW);
  Serial.println("\nI will never tell you my secret !");

  while(1){
    
    
    cnt=0;
    digitalWrite(TRIGGER, HIGH);

    for ( i = 0; i < MAX; i++){
      for ( j = 0; j < MAX; j++){
        cnt++;
      }
    }

    digitalWrite(TRIGGER, LOW);

    if ( i != 200 || j != 200 || cnt != 40000 ){
      Serial.println("TS{Gl1th3s_@r3_Awe50m3_!}");
      Serial.println("---------------------");
      Serial.print("i: ");
      Serial.println(i);
      Serial.print("j: ");
      Serial.println(j);
      Serial.print("cnt: ");
      Serial.println(cnt);
      delay(60000);
    }
  }
}

void handheld_challenge_voltage_glitch_v2(){
  const int TRIGGER_V2 = 3; // LED - DASH 
  volatile uint16_t i;
  volatile uint16_t j;
  volatile uint32_t cnt;
  int MAX = 200;

  Serial.begin(9600);
  pinMode(TRIGGER_V2, OUTPUT);
  digitalWrite(TRIGGER_V2, LOW);
  Serial.println("\nHahaha, I changed my trigger go and find it");

  while(1){
    
    cnt=0;
    digitalWrite(TRIGGER_V2, HIGH);

    for ( i = 0; i < MAX; i++){
      for ( j = 0; j < MAX; j++){
        cnt++;
      }
    }

    digitalWrite(TRIGGER_V2, LOW);

    if ( i != MAX || j != MAX || cnt != 40000 ){
      Serial.println("TS{0h_n0_y0u_foun6_my_7r1gg3r}");
    }
  }
}

void handheld_challenge_side_channel_timing_attack(void){

  int PIN[5] = {0};
  int UPIN[5] = {0};
  int upini = 0;
  int flag = 0;

  pinMode(LED_0, OUTPUT);
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  
  pinMode(BTN_DOT, INPUT);
  pinMode(BTN_DASH, INPUT);
  pinMode(BTN_OK, INPUT);
  pinMode(BTN_SPACE, INPUT);
  
  digitalWrite(LED_0, HIGH);
  digitalWrite(LED_1, HIGH);
  digitalWrite(LED_2, HIGH);

  randomSeed(analogRead(0));

  for (int p=0; p<5; p++){
    PIN[p] = random(1,4);
    delay(10);
  }

  Serial.begin(9600);
  delay(500);
  Serial.println ("\nYou will never enter my vault!");

  while(1){
    if (digitalRead(BTN_DOT) == HIGH){
      UPIN[upini] = 1;
      upini++;
      delay(300);
    }
    
    if (digitalRead(BTN_DASH) == HIGH){
      UPIN[upini] = 2;
      upini++;
      delay(300);
    }
    
      
    if (digitalRead(BTN_SPACE) == HIGH){
      UPIN[upini] = 3;
      upini++;
      delay(300);
    }
    
    if (upini == 5){
      upini = 0;
    }

    if (digitalRead(BTN_OK) == HIGH){
      flag = 0;
      upini = 0;
      for (int i=0; i<5; i++){
        if (UPIN[i] != PIN[i]){
          flag++;
          /* ERROR WRONG PIN */
          digitalWrite(LED_0, LOW);
          digitalWrite(LED_1, LOW);
          digitalWrite(LED_2, LOW);
          delay(500);
          digitalWrite(LED_0, HIGH);
          digitalWrite(LED_1, HIGH);
          digitalWrite(LED_2, HIGH);
          break;
        }
        delay(10);
      }

      if (flag == 0){
        Serial.println("TS{Y0u_3nter36_th3_v@ul7}");
        while(1){
          digitalWrite(LED_0, HIGH);
          delay(100);
          digitalWrite(LED_0, LOW);
          delay(100);
          digitalWrite(LED_1, HIGH);
          delay(100);
          digitalWrite(LED_1, LOW);
          delay(100);
          digitalWrite(LED_2, HIGH);
          delay(100);
          digitalWrite(LED_2, LOW);
          delay(100);
        }
      }
      delay(300);
    } 
    delay(10); 
  }
}


void handheld_challenge_side_channel_timing_attack_v2(){

  Serial.begin(9600);

  int PIN_v2[4] = {0};
  int UPIN_v2[4] = {0};
  int upini_v2 = 0;
  int flag = 0;

  pinMode(LED_0, OUTPUT);
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  
  pinMode(BTN_DOT, INPUT);
  pinMode(BTN_DASH, INPUT);
  pinMode(BTN_OK, INPUT);
  pinMode(BTN_SPACE, INPUT);

  randomSeed(analogRead(0));

  for (int p=0; p<4; p++){
    PIN_v2[p] = random(1,5);
    delay(10);
  }  

  delay(1000);
  Serial.println("You are no good enough");

  while(1) {

    if (digitalRead(BTN_DOT) == HIGH){
      UPIN_v2[upini_v2] = 1;
      upini_v2++;
      delay(300);
    }
    
    if (digitalRead(BTN_DASH) == HIGH){
      UPIN_v2[upini_v2] = 2;
      upini_v2++;
      delay(300);
    }
    
      
    if (digitalRead(BTN_SPACE) == HIGH){
      UPIN_v2[upini_v2] = 3;
      upini_v2++;
      delay(300);
    }

    if (digitalRead(BTN_OK) == HIGH){
      UPIN_v2[upini_v2] = 4;
      upini_v2++;
      delay(300);
    }    

    if (upini_v2 == 4){
      upini_v2 = 0;
      flag = 0;
      for (int i=0; i<4; i++){
        if (UPIN_v2[i] != PIN_v2[i]){
          /* ERROR WRONG PIN_v2 */
          flag++;  
          digitalWrite(LED_0, LOW);
          digitalWrite(LED_1, LOW);
          digitalWrite(LED_2, LOW);
          delay(500);
          digitalWrite(LED_0, HIGH);
          digitalWrite(LED_1, HIGH);
          digitalWrite(LED_2, HIGH);
          UPIN_v2[0] = 0;
          UPIN_v2[1] = 0;
          UPIN_v2[2] = 0;
          UPIN_v2[3] = 0;
          break;
        }
        delay(10);
      }
      if (flag == 0){
        while(1){
          Serial.println("TS{D@mn_y0u_@r3_g006}");
          digitalWrite(LED_0, HIGH);
          delay(100);
          digitalWrite(LED_0, LOW);
          delay(100);
          digitalWrite(LED_1, HIGH);
          delay(100);
          digitalWrite(LED_1, LOW);
          delay(100);
          digitalWrite(LED_2, HIGH);
          delay(100);
          digitalWrite(LED_2, LOW);
          delay(100);
        }
      }
      delay(300);
    }
    delay(10);
  }

}

void blackbox_chain_UART_Glitch_Attack(void){
  const char password[] = "d3@1bt7*0PqSxc9~^";
  Serial.begin(900847); // dbeef
  Serial.println("\nWelcome to my Login Interface!");
  Serial.println("You managed to identify my UART baudrate, now please login.");
  Serial.println("[+] Please Provide Your Password:");

  while(1){
      Serial.flush(); 
      if (Serial.available() > 0) {
      char provided_password[strlen(password)];
      Serial.readBytesUntil('\n', provided_password, strlen(password));
      int success = 1;
      for (int i = 0; i < strlen(password); i++) {
        if (provided_password[i] != password[i]) {
          success = 0;
          break;
        }
      }

      if (success == 1) {
        Serial.println("TS{L0gin_Succ355fu1_!}");
        Serial.flush(); 
        exit(0);
      } else {
        Serial.println("[-] Login FAILED");
        Serial.println("[+] Please Provide Your Password:");
      }
    }
  }
}


void blackbox_chain_UART_Timing_Attack(void){
  const int custom_rx = 12;
  const int custom_tx = 11;
  SoftwareSerial mySerial(custom_rx, custom_tx);
  mySerial.begin(1200); 

  char pin[] = "25315294";
  int upini_v2 = 0;
  int flag = 0;

  pinMode(LED_0, OUTPUT);
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  digitalWrite(LED_0, HIGH);
  digitalWrite(LED_1, HIGH);
  digitalWrite(LED_2, HIGH);
  delay(1000);
  mySerial.println("Please Enter Your 8 Digit PIN:");

  while(1){
    delay(500); 

    mySerial.flush(); 
    if (mySerial.available() > 0) {
      char provided_pin[strlen(pin)] = {'\0'};
      mySerial.readBytesUntil('\n', provided_pin, strlen(pin));
      mySerial.flush(); 
      int success = 0;
      for (int i = 0; i < strlen(pin); i++) {
        if (provided_pin[i] != pin[i]) {
          digitalWrite(LED_0, LOW);
          digitalWrite(LED_1, LOW);
          digitalWrite(LED_2, LOW);
          delay(500);
          digitalWrite(LED_0, HIGH);
          digitalWrite(LED_1, HIGH);
          digitalWrite(LED_2, HIGH);
          success = 0;
          break;
        }
        delay(10);
        success = 1;
      }

      if (success == 1){
        mySerial.println("TS{D0n7_M355_w17h_t1m3}");
        mySerial.flush();
        exit(0);
      }  
      else{
        mySerial.println("[-] Wrong PIN!");
        mySerial.println("Please Enter Your 8 Digit PIN:");
      }
    } 
  }
}