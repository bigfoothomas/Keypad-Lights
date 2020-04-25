#include <Keypad.h>
#include <Adafruit_NeoPixel.h>
#define PIN      6
#define N_LEDS 24
Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, PIN, NEO_GRB + NEO_KHZ800);
const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
byte keys[ROWS][COLS] = {
  {1,2,3},
  {4,5,6},
  {7,8,9},
  {11,10,12} // 11==* 10==0 12==#
};
byte rowPins[ROWS] = {7, 8, 9, 10}; //connect to the row pinouts of the keypad //this is hole3 to pin7,hole8 to pin8,hole7 to pin9, hole5 to pin10
byte colPins[COLS] = {2, 3, 4}; //connect to the column pinouts of the keypad //this is hole4 to pin2, hole2 to pin3, hole6 to pin4

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
byte key;
byte oldkey;
byte key0; //this is the position
byte key1; //this is the color
byte key2; //this is the pattern
byte oldkey0;
byte oldkey1;
byte oldkey2;

void setup(){
  Serial.begin(9600);
  strip.begin();
  for(int i=0;i<=N_LEDS; i++){
    strip.setPixelColor(i,0,0,0);
    strip.show();
    
  }
}
  
void loop(){
  
  getkey0();
  getkey1();
  getkey2();
  getkey3();
  //this switchwill have to be a "set color command" this will be same as below
  //there will need to be a "set brightness command" this will put a multiplier infront of the color values this isnt really necesary
  //there will need to be a "set pattern command" this will have to be located as an if statement in the color command ex if pattern=1 display solid, else... 
  //or as a seperate program that uses a nested switch and returns to the initial switch. 
  switch(key) {
    case 1:
      solid(strip.Color(255, 0, 0)); // Red
      break;
    
    case 2:
      solid(strip.Color(200,58,0));//orange
      break;

    case 3:
      solid(strip.Color(255,255,0));//yellow
      break;

    case 4:
      solid(strip.Color(0, 255, 0)); // Green
      break;

    case 5:
      solid(strip.Color(0, 0, 255)); // Blue
      break;

      case 6:
      solid(strip.Color(30,0,180));//purple
      break;

    case 7:
      solid(strip.Color(255,255,0));//yellow
      getkey();
      delay(400);
      getkey();
      solid(strip.Color(30,0,180));//purple
      getkey();
      delay(400);
      getkey();
      break;

    case 8:
      solid(strip.Color(255, 0, 0)); // Red
      getkey();
      delay(400);
      getkey();
      solid(strip.Color(0, 255, 0)); // Green
      getkey();
      delay(400);
      getkey();
      solid(strip.Color(0, 0, 255)); // Blue
      getkey();
      delay(400);
      getkey();
      break;

    case 9:
      solid(strip.Color(255, 0, 0)); // Red
      getkey();
      delay(400);
      getkey();
      solid(strip.Color(0, 0, 255)); // Blue
      getkey();
      delay(400);
      getkey();
      break;

    case 10:
      solid(strip.Color(0,0,0));//off
      break;

    case 11:
      solid(strip.Color(50, 50, 50));// light white
      break;

    case 12:
      solid(strip.Color(200,200,200));//bright white
      break;
  }
}

byte getkey()
{
   key = keypad.getKey();
   
   if(key==0)
   {
      getkey();
   }
  else
  {
    key=key;
  }
  oldkey=key;
  
  if (key){
    Serial.println(key);
  }  
  return(key); 
}
//*****************************************
byte getkey0()
{//this is position
  getkey();
  /*if (key==0)
  {
    getkey0();
    }
  }
  else if (key==11||key==10||key==12)
  {
    key0=key;
    }
  else
  {
  key0=oldkey0;
  }*/
  key0=key
  return(key0);
  
  }


//*********************
byte getkey1()
{//this is the brightness
  getkey()
  if (key==11 || key==12 ||key=10)
  {
   key1=0;
  }
  else
  {
  key1=key;
  }
  key=0;
  return(key1);
  }
  //*******************
byte getkey2()
{
  //this is the color
  getkey()
  if(key==0)
  {
    getkey2();
   }
   else
   {
  key2=key;
   }
  key=0;
  return(key2);
  }
  void pressedkey
  {//this tests if a key is pressed if so it goes to getkey0()
    key=keypad.getKey
    if(key !=0)
    {
      getkey0();//if a button is pressed send button value to getkey0 function }
  }
  else
  {return();}
  }
/* static void chase(uint32_t c) {
      for(uint16_t i=0; i<strip.numPixels()+4; i++) {
          strip.setPixelColor(i  , c); // Draw new pixel
          strip.setPixelColor(i-4, 0); // Erase pixel a few steps back
          strip.show();
          delay(25);
      }
    }
    */
    static void solid(uint32_t c){
      for(uint16_t i=0; i<strip.numPixels(); i++) {
          strip.setPixelColor(i  , c); // Draw new pixel
          //strip.setPixelColor(i-4, 0); // Erase pixel a few steps back
          strip.show();
          delay(1);
    }
    }
