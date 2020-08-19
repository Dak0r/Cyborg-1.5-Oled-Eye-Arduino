#include <Arduino.h>
#include <U8g2lib.h>
#include <Eye.h>

using namespace EyeBehavior;

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif


//U8G2_SSD1327_WS_128X128_1_4W_SW_SPI u8g2(U8G2_R0, /* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
U8G2_SSD1327_WS_128X128_1_4W_HW_SPI u8g2(U8G2_R0, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);


EyeConfig eyeconfig;
Eye eye(&eyeconfig);

  
void setup() {

  // put your setup code here, to run once:
  Serial.begin(9600);

  eyeconfig.blink_timing_duration.min = 65;
  eyeconfig.blink_timing_duration.max = 85;

  eyeconfig.blink_timing_in_between.min = 1000;
  eyeconfig.blink_timing_in_between.max = 7000;

  eyeconfig.eyelid_upper_y_range.min = 0.1;
  eyeconfig.eyelid_upper_y_range.max = 0.5;    
  eyeconfig.eyelid_lower_y_range.min = 0.9;
  eyeconfig.eyelid_lower_y_range.max = 0.5; 

  eyeconfig.eyelid_movement_speed = 0.5;

  eyeconfig.pupil_size_speed = 0.2;
  
  eye.init_pos();
 
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

int posX = 64;
int posY = 64;

int move = 1;


void loop() {

  eye.update(millis());
  posX = 64 + (eye.get_position_x()*20);
  posY = 64 + (eye.get_position_y()*10);

#if DEBUG_POS
  Serial.print("Values: ");
  Serial.print(posX);
  Serial.print(" - ");
  Serial.println(posY);
#endif

  /*Serial.print("Eyelid: ");
  Serial.print(lower_eyelid);
  Serial.print(" - ");
  Serial.println(eye.get_upper_eyelid());*/

  //Serial.print("Pupil: ");
  //Serial.println(eye.get_pupil_size());

  // u8g2.clearBuffer();
  u8g2.firstPage();  
  do {
      u8g2_prepare();
  // u8g2.drawStr( 0, 0, "Hello World");
  //u8g2.drawStr( 0, 8, "Daniel Korgel");
 
  //u8g2.drawStr( 0, 3, i);
  
  //eye ball
  u8g2.drawDisc(posX,posY,48);
  u8g2.setDrawColor(0);
  u8g2.drawCircle(posX,posY,48);
  u8g2.drawCircle(posX,posY,48-1.5);
  //u8g2.drawCircle(posX,posY,48-2);
  
  // pupil
  u8g2.setDrawColor(0);
  u8g2.drawDisc(posX,posY,20*eye.get_pupil_size());


  // iris
  for(int i=1; i<12; i++){
    u8g2.drawCircle(posX,posY,8+(i*2));
  }
  // Eyelids
  u8g2.setDrawColor(0);
  u8g2.drawBox(posX-48, posY-48,98,96*eye.get_upper_eyelid());
  float lower_eyelid = eye.get_lower_eyelid();
  u8g2.drawBox(posX-48, posY-48+(98*(lower_eyelid)),98,48);
  } while( u8g2.nextPage() );
  //u8g2.sendBuffer();
  
  //delay(5);
}
