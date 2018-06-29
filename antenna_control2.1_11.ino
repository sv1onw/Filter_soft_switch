/*  Soft Selector Switch Sketch "antenna_control2.1_11.ino" ==>"Antenna Soft Selector"
 *  by SV1ONW , Konstantinos  - Jun 2018.
 *  This source file is under General Public License version 3.0
 *  Used with an Arduino Nano , Uno or Pro Mini to select one of six Antennas.
 *  If modified can be used to "soft" switch select practically any "relay controlled" situation.
 *  Modify on your own responsibility! May run with other Arduino boards. You have to test it!
 *  
 *  A SSD1306 128 x 64 I2C OLED Display is used.
 *  For I2C displays, connect Vcc and Ground, SDA to A4, SCL to A5 on the Arduino board.
 *  
 *  In this current application the Sketch is used with SV1AFN's "HF Amateur poss Preselector". 
 *  See: https://www.sv1afn.com/ham_pos_presel.html  for Schematics, connectivity and Filter response at each pos.
*/
// include the following libraries code:
#include <Arduino.h>  //Included in Αrduino IDE
#include <U8g2lib.h>  //Get the library and serious doccumentation from: https://github.com/olikraus/u8g2
#include <Wire.h>     //Included in Αrduino IDE

// Set up MCU pins
 
#define PosChange       12  //Cyclically going up and then down to Lowest Position, starting from ANT 5. Input pin 
#define ANT1out          4  //Pin 4  Output to ANT 1  control circuit   
#define ANT2out          5  //Pin 5  Output to ANT 2  control circuit  
#define ANT3out          6  //Pin 6  Output to ANT 3  control circuit  
#define ANT4out          7  //Pin 7  Output to ANT 4  control circuit  
#define ANT5out          8  //Pin 8  Output to ANT 5  control circuit  
#define ANT6out          9  //Pin 9  Output to ANT 6  control circuit  

// U8g2 Contructor for noname 128 x 64 OLED Display
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
// Constructor ends here

// configure variables 
unsigned int bStepcount=4;  //Start up value "4" selects the 5 position. Can be changed to your taste.
String pos = " ANT 5";    //Prints the start up selected Position name. Should be changed to match bStepcount accordingly.
unsigned long debounce,DebounceDelay=500000;


void setup()
{
  u8g2.begin();
  u8g2.enableUTF8Print();  

//********** Write on the display *****************************************
  u8g2.firstPage();
  do{
  u8g2.setFont(u8g2_font_helvB08_tf);  // Select a font to suit your taste
  u8g2.setFontDirection(0);
  u8g2.clearBuffer();
  u8g2.drawFrame(12,1,116,13);// Draw a rectangle outline
  u8g2.setCursor(15, 11);
  u8g2.print("Antenna Soft Selector");//Sketch title
  u8g2.setCursor(36, 30);
  u8g2.print("by SV1ONW");//Author    
  u8g2.setCursor(4, 55);
  u8g2.print("Select Antenna:");//Action to do
  u8g2.setFont(u8g2_font_helvB10_tf);  //  Select a font to suit your taste
  u8g2.setFontDirection(0);
  u8g2.setCursor(82, 55);
  u8g2.print(pos);
  u8g2.sendBuffer();
  }while (u8g2.nextPage());
  
  delay(1000);
  
//INITIALIZATION  **********************************************************
  // Set up pos Change Button (momentarily push type)
  pinMode(PosChange, INPUT);         // Set as input
  digitalWrite(PosChange, HIGH);     // Enable internal pull-up resistor
  // Set up Outputs
  pinMode(ANT1out,  OUTPUT);           // Set as output
  pinMode(ANT2out,  OUTPUT);           // Set as output
  pinMode(ANT3out,  OUTPUT);           // Set as output
  pinMode(ANT4out,  OUTPUT);           // Set as output
  pinMode(ANT5out,  OUTPUT);           // Set as output
  pinMode(ANT6out,  OUTPUT);           // Set as output
  
  digitalWrite(ANT1out,  LOW);         // Initial state must be Low
  digitalWrite(ANT2out,  LOW);         // Initial state must be Low
  digitalWrite(ANT3out,  LOW);         // Initial state must be Low
  digitalWrite(ANT4out,  LOW);         // Initial state must be Low
  digitalWrite(ANT5out,  LOW);         // Initial state must be Low
  digitalWrite(ANT6out,  LOW);         // Initial state must be Low
  
  digitalWrite(ANT5out, HIGH);         // Set High for the 5th position, i.e. ANT 5  
}

//******************************************************************
// Loop starts here:
// Loops consecutively to check MCU's activity
//******************************************************************
void loop()
{   
    // pos selection begins here:
    if(digitalRead(PosChange) == LOW)
    {
      for(debounce=0; debounce < DebounceDelay; debounce++) {
      };
      bStepcount++;
      if(bStepcount>5)bStepcount=0;
      setAnt(); // Call the: Select the desired Antenna subroutine
    }

}

//******************************************************************
// Subroutines
//******************************************************************
// Select the desired Antenna subroutine
//******************************************************************
  void setAnt()
  {
    switch(bStepcount)
    {
    case 0:
      pos = " ANT 1";
      digitalWrite(ANT6out, LOW);
      digitalWrite(ANT1out, HIGH);
      break;
    case 1:
      pos = " ANT 2";
      digitalWrite(ANT1out, LOW);
      digitalWrite(ANT2out, HIGH);
      break;
    case 2:
      pos = " ANT 3";
      digitalWrite(ANT2out, LOW);
      digitalWrite(ANT3out, HIGH);
      break;
    case 3:
      pos = " ANT 4";
      digitalWrite(ANT3out, LOW);
      digitalWrite(ANT4out, HIGH);
      break;
    case 4:
       pos = " ANT 5";
      digitalWrite(ANT4out, LOW);
      digitalWrite(ANT5out, HIGH);
      break;
    case 5:
      pos = " ANT 6";
      digitalWrite(ANT5out, LOW);
      digitalWrite(ANT6out, HIGH);
      break;
    }
  resDisplay();
  }

//******************************************************************
// Display the selected pos subroutine
//******************************************************************
void resDisplay()
{

  u8g2.setFont(u8g2_font_helvB08_tf);  // Select a font to suit your taste
  u8g2.setFontDirection(0);
  u8g2.clearBuffer();
  u8g2.drawFrame(12,1,116,13);
  u8g2.setCursor(15, 11);
  u8g2.print("Antenna Soft Selector");
  u8g2.setCursor(36, 30);
  u8g2.print("by SV1ONW");    
  u8g2.setCursor(4, 55);
  u8g2.print("Select Antenna:");
  u8g2.setFont(u8g2_font_helvB10_tf);  // Select a font to suit your taste
  u8g2.setFontDirection(0);
  u8g2.setCursor(82, 55);
  u8g2.print(pos);
  u8g2.sendBuffer();
  
}
//******************************************************************
