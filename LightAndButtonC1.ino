#include <Keypad.h>
#include <Adafruit_NeoPixel.h>
#define PIN      6//this is pwm pin for lights inside
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
byte key1; //this is the brightness
byte key2; //this is the color
byte key3;//this is the pattern
//above copied from key function test
int R;
int G;
int B;
int r,g,b;
// the above is additional code

void setup(){
  Serial.begin(9600);//turns on serial data transfer
  strip.begin();//initializes ws2812 strip
  Serial.println("setup");
  for(int i=0;i<=N_LEDS; i++){
    Serial.println("set init color");
    strip.setPixelColor(i,0,0,0);
    strip.show();
    
  }
}
//above copied from Basic Keypad Lights Event Based
void loop() {
  // put your main code here, to run repeatedly:
  /*getkey0();//this is for the position */
  /*I will need to implement a master and 2 slaves for this. 
  The set will become a send data and the slaves wil recieve the data
  The process at the slaves will be the this set function.
  If a button is pressed on the board a reset funstion will need to be made
  which will set all data to zero and transmit to slaves to turn off. 
  The slaves will send no data back to the master 
  */
  Serial.println("main loop");
  //getkey1();//this is for the brightness
  getkey2();//this is for the color
  getkey3();//this is for the pattern
  Serial.println("next is the set function");
  set();//this sets it all
  //these are functions from keyfunctiontest

}

static void solid(){//this is for solid color
      Serial.println("in solid");
      Serial.println(r);
      for(int i=0; i<strip.numPixels(); i++) {
        Serial.println("inside solid for loop");
          strip.setPixelColor(i,r,g,b); // Draw new pixel
          //strip.setPixelColor(i-4, 0); // Erase pixel a few steps back
          strip.show();
          delay(1);
      
    }
    Serial.println("right after solid for loop");
 }

byte getkey()
{//this is used by the functions to retrieve a the pressed button value
  
   key = keypad.getKey();
   delay(100);
   if(key==0)
   {
      getkey();
   }
  else
  {
    key=key;
  }
  oldkey=key;
  //Serial.println(key);
  return(key); 
}
byte getkey0()
{//this is the function for position
  
  getkey();
  if (key==11 || key==10 || key==12)
  {
  key0=key;
  Serial.println("key0: ");
  Serial.println(key0);
  return(key0);
  
    }/*if (key==0)
  {
    getkey0();
    }*/
  
    else
    {
      Serial.println("loop");
      getkey0();
      }
  

  }

  byte getkey1()
{//this is the brightness
  getkey();
  if (key==0)
  {
    getkey1();
  }
  else if (key==11 || key==12 || key==10)
  {
   key1=0;
  }
  else
  {
  key1=key;
  }
  Serial.println("key1: ");
  Serial.println(key1);
  return(key1);
  }
  //*******************
byte getkey2()
{
  //this is the color
  getkey();
  
  key2=key;
   
  Serial.println("key2: ");
  Serial.println(key2);
  return(key2);
  }

  byte getkey3()
{
  //this is the pattern
  getkey();
  
  key3=key;
   
  Serial.println("key3: ");
  Serial.println(key3);
  return(key3);
  }
  
void set()
  {
   Serial.println("this is set");
   chooseColor();
   Serial.println("this is set back from chooseColor");
   keytest();
   turnon();//this will choose pattern and turn on LED
   Serial.println("this is the function set back from turnon");
  keytest();
  set();//this effectively works as a loop
  }
  
void keytest()
  {//this tests if a key is pressed during the set function, if so it goes to getkey0()
    key = keypad.getKey();//tests for pressed button
    if(key != 0)//if button is pressed
    {
      Serial.println("you made it back to Main Loop");
      loop();//if a button is pressed then go to the start of the main loop}
      
  }
  else
  {
    return;//if no button is pressed, return to set function
    }
  }

int chooseColor(){
 Serial.println("made it to chooseColor"); 
 switch(key2){
  case 1: //red
    R= 255;
    G=0;
    B=0;
    break;
  
  case 2: //orange
    R=200;
    G=58;
    B=0;
    break;

  case 3: //yellow
    R= 255;
    G=255;
    B=0;
    break;
  
  case 4: //green
    R=0;
    G=255;
    B=0;
    break;

  case 5: //blue
    R=0;
    G=0;
    B=255;
    break;
  
  case 6: //purple
    R=30;
    G=0;
    B=180;
    break;
  
  case 7: //white
    R= 250;
    G=255;
    B=255;
    break;
  
  case 8: //pink
    R=255;
    G=105;
    B=180;
    break;

  case 9: //light blue
    R=0 ;
    G=255;
    B=255;
    break;
  
  case 10: //off
    R=0;
    G=0;
    B=0;
    break;
  
  case 11: //off
    R=0;
    G=0;
    B=0;
    break;

    case 12: //off
    R=0;
    G=0;
    B=0;
    break;
    } 
    Serial.println("below chooseColor switch");
    return;
  }
void turnon(){
  Serial.println("made it to turnon");
  /*r=11*key1*R/100;//11*brightness(from key1)*colorvalue(from key2)/100
  //Serial.println(r);
  g=11*key1*G/100;
  b=11*key1*B/100;
  key31=key3+12;*/
  r=R;
  g=G;
  b=B;
  Serial.println(key3);
  switch(key3){
    case 1://solid
      //keytest();
      Serial.println(r);
      delay(10);
      solid(); 
      delay(10);
      break;

    case 2://chase
      keytest();
      chase(strip.Color(r, g, b)); 
      break; 

    case 3://blinks
      keytest();
      blinks(strip.Color(r, g, b)); 
      break;

    default:
      keytest();
//      solid(strip.Color(0,0,0));
      solid();
      break;  
  }
  Serial.println("made it past turnon switch");
  return;
  
  }

/*void solid(uint32_t c){//this is for solid color
      Serial.println("in solid");
      Serial.println(r);
      for(uint16_t i=0; i<strip.numPixels(); i++) {
          strip.setPixelColor(i  ,r,g,b); // Draw new pixel
          //strip.setPixelColor(i-4, 0); // Erase pixel a few steps back
          strip.show();
          delay(1);
    }
 }
*/
void chase(uint32_t c) {//this is for color to chase
      for(uint16_t i=0; i<strip.numPixels()+4; i++) {
          strip.setPixelColor(i  , c); // Draw new pixel
          strip.setPixelColor(i-4, 0); // Erase pixel a few steps back
          strip.show();
          delay(25);
      }
    }

void blinks(uint32_t c) {//this is for color to blinnk
      
      for(uint16_t i=0; i<strip.numPixels()+4; i++) {
          strip.setPixelColor(i  , c); // Draw new pixel
          //strip.setPixelColor(i-4, 0); // Erase pixel a few steps back
          strip.show();
          delay(25);
      }
     
      for(uint16_t i=0; i<strip.numPixels()+4; i++) {
          strip.setPixelColor(i,0,0,0); // Draw new pixel
          //strip.setPixelColor(i-4, 0); // Erase pixel a few steps back
          strip.show();
          delay(15);
    }}
