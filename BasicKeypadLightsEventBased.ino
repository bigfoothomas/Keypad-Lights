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
byte oldkey;
byte key;
byte r, g, b;
void setup(){
  Serial.begin(9600);
  strip.begin();
  Serial.println("setup");
  for(int i=0;i<=N_LEDS; i++){
    Serial.println("init color");
    strip.setPixelColor(i,0,0,0);
    strip.show();
    
  }
}
  
void loop(){
  //byte key = keypad.getKey();
  getkey();
/*  if(key==0){
    key=oldkey;
    }
  else{
    key=key;
  }
  oldkey=key;
  
  if (key){
    Serial.println(key);
  }*/
  switch(key) {
    case 1:
      r=255;
      g=0;
      b=0;
      solid(strip.Color(r, g, b)); // Red
      break;
    
    case 2:
    r=200;
    g=58;
    b=0;
      solid(strip.Color(r,g,b));//orange
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

/* static void chase(uint32_t c) {
      for(uint16_t i=0; i<strip.numPixels()+4; i++) {
          strip.setPixelColor(i  , c); // Draw new pixel
          strip.setPixelColor(i-4, 0); // Erase pixel a few steps back
          strip.show();
          delay(25);
      }
    }
    */
    void getkey()
    {
      key = keypad.getKey();
      if(key==0){
      key=oldkey;
    }
      else{
      key=key;
    }
  oldkey=key;
  
  if (key){
    Serial.println(key);
    
  }
  return(key);
  }
  
    /*static*/ void solid(uint32_t c){
      for(uint16_t i=0; i<strip.numPixels(); i++) {
          strip.setPixelColor(i  , c); // Draw new pixel
          //strip.setPixelColor(i-4, 0); // Erase pixel a few steps back
          strip.show();
          delay(1);
    }
    }
