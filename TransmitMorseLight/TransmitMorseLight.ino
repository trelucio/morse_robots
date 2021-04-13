/* TransmitMorseLight - Color Beacon for use with Core Spartan system
  (c) Modern Robotics Inc. 2016  http://www.modernroboticsinc.com
      
  The Color Beacon uses an RGB LED to produce over 16 million colors. A color can be
  set by the user via programming or it can be set to RED or BLUE team colors by swiping 
  a magnet over the side of the device.
    
  Connections:
  Color Beacon(default addr 0x4C *0x26*)    = Port I2C
  *Arduino Address*
  
  NOTE* When using any Core sensor and its accompanying library, the pinMode() function
  should never be used as some sensors change or hold the mode as input/output at 
  certain times to function correctly. All mode initializations are automatically done 
  when the sensor constructor is calbeacon. i.e. CORE_TOUCH().
  
  Core Spartan language reference can be found at http://modernroboticsinc.com/spartan  
  Arduino language reference can be found at http://arduino.cc/en/Reference/HomePage  
  Windows: USE SERIAL MONITOR -> Ctrl+Shift+M
  Mac:     USE SERIAL MONITOR -> Cmd+Shift+M
-------------------------------------------------------------------------------------------*/
#include "CORE.h"

// Create an instance of class CORE_TRICOLOR named beacon on port S3
CORE_COLOR_BEACON beacon;

// Create an instance of the class CORE_DIGITAL named push on port D7
CORE_DIGITAL push(7);

void setup(){
// No setup code required
  beacon.setColor(beacon.OFF);

  String msg = "MORSE"; 
  String msg1 = "COMPUTER SCIENCE";
  String msg2 = "THERESE";

  encode(msg);
}

const int ms = 200; //delay time/light speed in ms; == interval

/* 
* MORSE TO LIGHT CODE KEY
* . = RED, - = BLUE
* next letter/char = GREEN, space = WHITE
* END OF MESSAGE = 3 long white flashes
*/

// MORSE TO LIGHT FUNCTION
// s = morse string of letter received from encode function
// returns light flashes on color beacon
void morse2light(String s){
  for (int i = 0; i < s.length(); i++){
    if (s.charAt(i) == '.'){
      beacon.setColor(beacon.RED);
      delay(ms);
    }
    if (s.charAt(i) == '-'){
      beacon.setColor(beacon.BLUE);
      delay(ms);
    }
    if (s.charAt(i) == ' '){
      beacon.setColor(beacon.WHITE);
      delay(ms);
    }
    beacon.setColor(beacon.OFF);
    delay(ms);
  }
  // NEXT CHAR: flash green
  beacon.setColor(beacon.GREEN);
  delay(ms);    
  beacon.setColor(beacon.OFF);
  delay(ms);
}

// ENCODE FUNCTION
// Translate message to string representations of morse code
// Morse string given to morse2light function
void encode(String msg){
  for (int i = 0; i < msg.length(); i++){
      switch(msg.charAt(i)){
        case 'A':
            morse2light(".-");
            break;
        case 'B':
            morse2light("-...");
            break;
        case 'C':
            morse2light("-.-.");
            break;
        case 'D':
            morse2light("-..");
            break;
        case 'E':
            morse2light(".");
            break;
        case 'F':
            morse2light("..-.");
            break;
        case 'G':
            morse2light("--.");
            break;
        case 'H':
            morse2light("....");
            break;
        case 'I':
            morse2light("..");
            break;
        case 'J':
            morse2light(".---");
            break;
        case 'K':
            morse2light("-.-");
            break;
        case 'L':
            morse2light(".-..");
            break;
        case 'M':
            morse2light("--");
            break;
        case 'N':
            morse2light("-.");
            break;
        case 'O':
            morse2light("---");
            break;
        case 'P':
            morse2light(".--.");
            break;
        case 'Q':
            morse2light("--.-");
            break;
        case 'R':
            morse2light(".-.");
            break;
        case 'S':
            morse2light("...");
            break;
        case 'T':
            morse2light("-");
            break;
        case 'U':
            morse2light("..-");
            break;
        case 'V':
            morse2light("...-");
            break;
        case 'W':
            morse2light(".--");
            break;
        case 'X':
            morse2light("-..-");
            break;
        case 'Y':
            morse2light("-.--");
            break;
        case 'Z':
            morse2light("--..");
            break;
        }
  }

  // END OF MESSAGE: 3 Blinks of GREEN
  beacon.setColor(beacon.GREEN);
  delay(ms);
  beacon.setColor(beacon.OFF);
  delay(ms);
  beacon.setColor(beacon.GREEN);
  delay(ms);
  beacon.setColor(beacon.OFF);
  delay(ms);
  beacon.setColor(beacon.GREEN);
  delay(ms);
  beacon.setColor(beacon.OFF);
  delay(ms);
}

/* 
* MORSE2LIGHT CODE KEY
* . = RED, - = BLUE
* next letter/char = GREEN, space = WHITE
* SAMPLE MESSAGE: "MORSE"
* Message as morse code string: -- --- .-. ... . (with no spaces)
*  lights should flash: blue blue green 
*                       blue blue blue green 
*                       red blue red green 
*                       red red red green
*                       red green
*                       green green green 
*/

// LOOP()/ MAIN FUNCTION TO RUN ON ROBOT
// Enter string, encode, and transmit through color beacon
void loop(){
  /*beacon.setColor(beacon.OFF);

  String message = "MORSE"; 
  String message2 = "COMPUTER SCIENCE";

  encode(message);*/
}
