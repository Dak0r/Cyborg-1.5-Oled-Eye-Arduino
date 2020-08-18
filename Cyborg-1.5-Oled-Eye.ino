#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif


//U8G2_SSD1327_WS_128X128_1_4W_SW_SPI u8g2(U8G2_R0, /* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
U8G2_SSD1327_WS_128X128_1_4W_HW_SPI u8g2(U8G2_R0, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);

  
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

 
  /* U8g2 Project: SSD1306 Test Board */
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  digitalWrite(10, 0);
  digitalWrite(9, 0);   
  
  u8g2.begin();  

}

void u8g2_prepare(void) {
  u8g2.setFont(u8g2_font_6x10_tf);
  u8g2.setFontRefHeightExtendedText();
  u8g2.setDrawColor(1);
  u8g2.setFontPosTop();
  u8g2.setFontDirection(0);
}

int i=0;
int posX = 64;
int posY = 64;

int move = 1;


void loop() {

u8g2.firstPage();  
  do {
       u8g2_prepare();
  // u8g2.drawStr( 0, 0, "Hello World");
  //u8g2.drawStr( 0, 8, "Daniel Korgel");
 
  //u8g2.drawStr( 0, 3, i);

  u8g2.drawDisc(posX,posY,48);
  u8g2.setDrawColor(0);
  u8g2.drawDisc(posX,posY,16);
  for(int i=1; i<8; i++){
    u8g2.drawCircle(posX,posY,16+(i*2));
  }
  } while( u8g2.nextPage() );

  if(move > 0 && posX < 78){
    posX += 2;
    if(posX >= 78){
      move = -1;
    }
  }
  if(move < 0 && posX > 50){
    posX -= 2;
    if(posX <= 50){
      move = 1;
    }
  }
  
  //Serial.println("Test");
  //delay(50);
  i+=1;
}
