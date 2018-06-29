/*  Soft Selector Switch Sketch "filter_control2.1_11.ino" ==>"Filter Soft Selector"
 *  by SV1ONW , Konstantinos - Jun 2018.
 *  This source file is under General Public License version 3.0
 *  Used with an Arduino Nano , Uno or Pro Mini to select the Bands of a BPF Filter Board.
 *  If modified can be used to "soft" switch select practically any "relay controlled" situation.
 *  Modify on your own responsibility! May run with other Arduino boards. You have to test it!
 *  
 *  A SSD1306 128 x 64 I2C OLED Display is used.
 *  For I2C displays, connect Vcc and Ground, SDA to A4, SCL to A5 on the Arduino board.
 *  
 *  In this current application the Sketch is used with SV1AFN's "HF Amateur Bands Preselector". 
 *  See: https://www.sv1afn.com/ham_band_presel.html  for Schematics, connectivity and Filter response at each Band.
*/
// include the following libraries code:
#include <Arduino.h>  //Included in Αrduino IDE
#include <U8g2lib.h>  //Get the library and serious doccumentation from: https://github.com/olikraus/u8g2
#include <Wire.h>     //Included in Αrduino IDE

// Set up MCU pins
 
#define BandChange     12  //Cyclically going up and then down to Lowest Band, starting from 20m Band. Input pin
#define Bypass          2  //Pin 2  Output to BPF Bypass  
#define M160out         3  //Pin 3  Output to BPF 160m   
#define M80out          4  //Pin 4  Output to BPF 80m    
#define M40out          5  //Pin 5  Output to BPF 40m    
#define M30out          6  //Pin 6  Output to BPF 30m    
#define M20out          7  //Pin 7  Output to BPF 20m    
#define M17out          8  //Pin 8  Output to BPF 17m    
#define M15out          9  //Pin 9  Output to BPF 15m    
#define M12out         10  //Pin 10 Output to BPF 12m   
#define M10out         11  //Pin 11 Output to BPF 10m    

// U8g2 Contructor for noname 128 x 64 OLED Display
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
// Constructor ends here

// configure variables 
unsigned int bStepcount=4;  //Start up value "4" selects 20 meter band. Can be changed to your taste.
String band = " 20m";    //Prints the start up selected Band name. Should be changed to match bStepcount accordingly.
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
  u8g2.drawFrame(14,1,110,13);// Draw a rectangle outline
  u8g2.setCursor(22, 11);
  u8g2.print("Filter Soft Selector");//Sketch title
  u8g2.setCursor(36, 30);
  u8g2.print("by SV1ONW");//Author    
  u8g2.setCursor(10, 55);
  u8g2.print("Select a Band:");//Action to do
  u8g2.setFont(u8g2_font_helvB10_tf);  //  Select a font to suit your taste
  u8g2.setFontDirection(0);
  u8g2.setCursor(85, 55);
  u8g2.print(band);
  u8g2.sendBuffer();
  }while (u8g2.nextPage());
  
  delay(1000);
  
//INITIALIZATION  **********************************************************
  // Set up Band Change Button (momentarily push type)
  pinMode(BandChange, INPUT);         // Set as input
  digitalWrite(BandChange, HIGH);     // Enable internal pull-up resistor
  // Set up Outputs
  pinMode(Bypass,  OUTPUT);           // Set as output 
  pinMode(M160out, OUTPUT);           // Set as output 
  pinMode(M80out,  OUTPUT);           // Set as output
  pinMode(M40out,  OUTPUT);           // Set as output
  pinMode(M30out,  OUTPUT);           // Set as output
  pinMode(M20out,  OUTPUT);           // Set as output
  pinMode(M17out,  OUTPUT);           // Set as output
  pinMode(M15out,  OUTPUT);           // Set as output
  pinMode(M12out,  OUTPUT);           // Set as output
  pinMode(M10out,  OUTPUT);           // Set as output
  
  digitalWrite(Bypass,  LOW);         // Initial state must be Low
  digitalWrite(M160out, LOW);         // Initial state must be Low
  digitalWrite(M80out,  LOW);         // Initial state must be Low
  digitalWrite(M40out,  LOW);         // Initial state must be Low
  digitalWrite(M30out,  LOW);         // Initial state must be Low
  digitalWrite(M20out,  LOW);         // Initial state must be Low
  digitalWrite(M17out,  LOW);         // Initial state must be Low
  digitalWrite(M15out,  LOW);         // Initial state must be Low
  digitalWrite(M12out,  LOW);         // Initial state must be Low
  digitalWrite(M10out,  LOW);         // Initial state must be Low

  digitalWrite(M20out, HIGH);         // Set High for the 20 meter default band  
}

//******************************************************************
// Loop starts here:
// Loops consecutively to check MCU's activity
//******************************************************************
void loop()
{   
    // Band selection begins here:
    if(digitalRead(BandChange) == LOW)
    {
      for(debounce=0; debounce < DebounceDelay; debounce++) {
      };
      bStepcount++;
      if(bStepcount>9)bStepcount=0;
      setBand(); // Call the: Select the desired band subroutine
    }

}

//******************************************************************
// Subroutines
//******************************************************************
// Select the desired band subroutine
//******************************************************************
  void setBand()
  {
    switch(bStepcount)
    {
    case 0:
      band = "160m";
      digitalWrite(Bypass, LOW);
      digitalWrite(M160out, HIGH);
      break;
    case 1:
      band = " 80m";
      digitalWrite(M160out, LOW);
      digitalWrite(M80out, HIGH);
      break;
    case 2:
      band = " 40m";
      digitalWrite(M80out, LOW);
      digitalWrite(M40out, HIGH);
      break;
    case 3:
      band = " 30m";
      digitalWrite(M40out, LOW);
      digitalWrite(M30out, HIGH);
      break;
    case 4:
       band = " 20m";
      digitalWrite(M30out, LOW);
      digitalWrite(M20out, HIGH);
      break;
    case 5:
      band = " 17m";
      digitalWrite(M20out, LOW);
      digitalWrite(M17out, HIGH);
      break;
    case 6:
      band = " 15m";
      digitalWrite(M17out, LOW);
      digitalWrite(M15out, HIGH);
      break;
    case 7:
      band = " 12m";
      digitalWrite(M15out, LOW);
      digitalWrite(M12out, HIGH);
      break;
    case 8:
      band = " 10m";
      digitalWrite(M12out, LOW);
      digitalWrite(M10out, HIGH);
      break;
     case 9:
      band = " F.=off"; // Filter is bypassed
      digitalWrite(M10out, LOW);
      digitalWrite(Bypass, HIGH);
      break;  
    }
  resDisplay();
  }

//******************************************************************
// Display the selected band subroutine
//******************************************************************
void resDisplay()
{

  u8g2.setFont(u8g2_font_helvB08_tf);  // Select a font to suit your taste
  u8g2.setFontDirection(0);
  u8g2.clearBuffer();
  u8g2.drawFrame(14,1,110,13);
  u8g2.setCursor(22, 11);
  u8g2.print("Filter Soft Selector");
  u8g2.setCursor(36, 30);
  u8g2.print("by SV1ONW");    
  u8g2.setCursor(10, 55);
  u8g2.print("Select a Band:");
  u8g2.setFont(u8g2_font_helvB10_tf);  // Select a font to suit your taste
  u8g2.setFontDirection(0);
  u8g2.setCursor(85, 55);
  u8g2.print(band);
  u8g2.sendBuffer();
  
}
//******************************************************************
