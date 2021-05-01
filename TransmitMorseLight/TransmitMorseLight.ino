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

  ---------------------------------------------------------------------------------
  TRANSMIT MORSE LIGHT WORKING CODE BY THERESE RELUCIO
  Networking, Databases, and Cryptograph: Spring 2021
  Professor: Dr. Hochberg

  1a. A string is encoded in SETUP() and uploaded to Color Beacon Robot
  1b. To loop light message, use LOOP() and comment out SETUP() body
  2. Encode() function reads string and converts every letter to morse code equivalent of . and -
  3. Each symbol combination (e.g. ".-") is passed to morse2light() function
  4a. Morse2light() converts every "." to a RED light and "-" to a BLUE light
  4b. If multiple symbols are part of the same letter, WHITE will flash (represented by "/" in DecodeMorseLightWorking.ino)
  4c. To separate letters, GREEN will flash (represented by "+" in DecodeMorseLightWorking.ino)
  5. Color beacon transmits lights every 200 ms

  COLOR  || SYMBOL || MEANING
  RED    ||   .    || Equivalent of "dot in Morse Code
  BLUE   ||   -    || Equivalent of "dash" in Morse Code  
  WHITE  ||   /    || Separates individual morse symbols of same letter (e.g., ./- => .- => A)
  GREEN  ||   +    || Separates individual letters/characters in English string
  YELLOW ||   &    || End of Message token

  * Current version does not work with spaces in message...yet.
  * Link to Morse Code Alphabet: https://www.codebug.org.uk/learn/step/540/morse-code-alphabet/

  SAMPLE MESSAGE: "MORSE"
  Message as morse code string: -- --- .-. ... . (with no spaces)
  Message that will show up in DecodeMorseLightWorking (no repeats): -/- + -/-/- + ./-/. + ././. + . &(with no spaces)
  Message in Color Form: blue white blue green
                         blue white blue white blue green
                         red white blue white red green
                         red white red white red green
                         red yellow
-------------------------------------------------------------------------------------------*/
#include "CORE.h"

/* String message -> char to morse -> morse to light */

// Create an instance of class CORE_TRICOLOR named beacon on port S3
CORE_COLOR_BEACON beacon;

// Create an instance of the class CORE_DIGITAL named push on port D7
CORE_DIGITAL push(7);

// Run Morse Code Message ONCE: click reset button on board to run again
void setup(){
  beacon.setColor(beacon.OFF);

  String msg = "MORSE";
  String msg1 = "ARDUINO"; 
  String msg2 = "HAVE A GOOD SUMMER";

  encode(msg);
}

// LIGHT INTERVAL: delay time/light speed in ms; == interval
const int ms = 300;

/* MORSE TO LIGHT FUNCTION
   s = morse string of letter received from encode() function
   returns light flashes on color beacon */
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

    if (s.length() > 1 && i < s.length() - 1){
      beacon.setColor(beacon.WHITE);
      delay(ms);
    }
  }
}

/* ENCODE FUNCTION
   Translate message to string representations of morse code
   Morse string given to morse2light function */
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

    // flash green for next letter if letter isn't the last in string
    if (i < msg.length() - 1){
      beacon.setColor(beacon.GREEN);
      delay(ms); 
    } 
  }
   
  // END OF MESSAGE: YELLOW
  beacon.setColor(beacon.YELLOW);
  delay(ms);
  beacon.setColor(beacon.OFF);
}


// LOOP() TO RUN ON ROBOT
// Enter string, encode, and transmit through color beacon
void loop(){
  /*beacon.setColor(beacon.OFF);

  String msg = "MORSE";
  String msg1 = "ARDUINO"; 
  String msg2 = "HAVE A GOOD SUMMER";

  encode(msg);*/
}
