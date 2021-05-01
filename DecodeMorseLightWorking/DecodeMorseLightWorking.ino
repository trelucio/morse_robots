/*
  Connections:
  Color Sensor(default addr 0x3C *0x1E*)  = Port I2C
  Touch Sensor(TOUCH)                     = Port D7
  *Arduino Address*
  
  NOTE* When using any Core sensor and its accompanying library, the pinMode() function
  should never be used as some sensors change or hold the mode as input/output at 
  certain times to function correctly. All mode initializations are automatically done 
  when the sensor constructor is called. i.e. CORE_TOUCH(). 
    
  Core Spartan language reference can be found at http://modernroboticsinc.com/spartan 
  Arduino language reference can be found at http://arduino.cc/en/Reference/HomePage  
  Windows: USE SERIAL MONITOR -> Ctrl+Shift+M
  Mac:     USE SERIAL MONITOR -> Cmd+Shift+M

  ---------------------------------------------------------------------------------
  DECODE MORSE LIGHT WORKING CODE BY THERESE RELUCIO
  Networking, Databases, and Cryptograph: Spring 2021
  Professor: Dr. Hochberg
  
  1. Color Sensor Robot receives transmitted lights from Color Beacon Robot
  2. Sensor Robot prints to Serial while receiving light signals
  3. When Sensor Robot sees YELLLOW, Serial prints "&" and ends reading
  4. Sensor Robot prints encrypted message . - / + and &
  4. Sensor Robot translates encrypted message

  COLOR  || SYMBOL || MEANING
  RED    ||   .    || Equivalent of "dot in Morse Code
  BLUE   ||   -    || Equivalent of "dash" in Morse Code
  WHITE  ||   /    || Separates individual symbols of same letter (e.g., ./- => .- => A)
  GREEN  ||   +    || Separates individual letters
  YELLOW ||   &    || End of Message token

  * Current version does not work with spaces in message...yet.

  Link to Morse Code Alphabet: https://www.codebug.org.uk/learn/step/540/morse-code-alphabet/
-------------------------------------------------------------------------------------------*/
#include "CORE.h"

// Create an instance of the class CORE_COLOR_SENSOR named color using the default I2C address
CORE_COLOR_SENSOR color;

// Interval at which to read light/speed at which (milliseconds)
const int interval = 20;  

void setup(){
  // Initialize serial communications at 9600 baud
  Serial.begin(9600);
  
  // Set the mode and rate of the color Sensor to PASSIVE at 60Hz
  color.colorSetup(color.PASSIVE, color.SIXTY);

  // Initialize empty string encoded for string of . - + &
  String encoded = ""; 

  // Reads and prints to serial colors sensed in real time
  Serial.print("Currently reading:\n");

  // Read transmitted lights until yellow light ("&"" token)
  while (encoded.substring(encoded.length()-1, encoded.length()) != "&"){  
    if (millis() % interval >= 0 && millis() % interval <= 1){
      encoded += getColor(); // append symbol read in getColor to encoded
      Serial.print(encoded);
    }
  }

  // Prints encoded string
  Serial.println("\nEncoded: " + encoded);

  // Parse encoded string and simplify to single symbols
  String parsed = parse(encoded);
  Serial.println("\nSimplified: " + parsed);

  // Decode encoded string to English
  Serial.println("\nDecoded Message: " + decode(parsed));
}


String getColor() {
  int val = color.getColorNumber();
  String colorSymbol = "";
  
  if (val == 10) // RED = "."
    colorSymbol = ".";
  else if (val == 3) // BLUE = "-"
    colorSymbol = "-";
  //else if (val == 2) // PURPLE = "_"
    //colorSymbol = "_";
  else if (val == 11 || val == 12 || val == 1) // WHITE = "/"
    colorSymbol = "/";
  else if (val == 4 || val == 5 || val == 6) //  GREEN = "+"
    colorSymbol = "+";
  else if (val == 9) // YELLOW = "&" = END
    colorSymbol = "&";
  
  //Serial.print(colorSymbol);
  return colorSymbol;
}

/* Parse encoded string: configure to just one symbol (no repeats)
*  by counting maximum 
*/
String parse(String encoded){
  String simple = "";
  int dotCount = 0;
  int dashCount = 0;

  // While character isn't "/" (next symbol) or "+" (end letter token), find majority symbol ("." or "-")
  
  for (int i = 0; i < encoded.length(); i++){
    if (encoded.charAt(i) != '/' || encoded.charAt(i) != '+' || encoded.charAt(i) != '&'){
      switch(encoded.charAt(i)){
        case '.':
          dotCount++;
          break;
        case '-':
          dashCount++;
          break;
      }
    }
    
    if (encoded.charAt(i) == '/' || encoded.charAt(i) == '&'){
      if (dotCount > dashCount)
        simple += ".";
      else if (dashCount > dotCount)
        simple += "-";
      dotCount = 0;
      dashCount = 0;
    }
    if (encoded.charAt(i) == '+'){
      if (dotCount > dashCount)
        simple += ".";
      else if (dashCount > dotCount)
        simple += "-";
      simple += "+";
      dotCount = 0;
      dashCount = 0;
    }
          
  }

  //Serial.println(simple);
  return simple;
}

// Substring until next + 
String decode(String msg){
  String decoded = "";
  for (int i = 0; i < msg.length(); i++){
    if (msg.substring(i,i+4) == "-..."){
      decoded += "B";
      i += 3;
    }
    else if (msg.substring(i,i+4) == "-.-."){
      decoded += "C";
      i += 3;
    }
    else if (msg.substring(i,i+4) == "..-."){
      decoded += "F";
      i += 3;
    }
    else if (msg.substring(i,i+4) == "...."){
      decoded += "H";
      i += 3;
    }
    else if (msg.substring(i,i+4) == ".---"){
      decoded += "J";
      i += 3;
    }
    else if (msg.substring(i,i+4) == ".-.."){
      decoded += "L";
      i += 3;
    }
    else if (msg.substring(i,i+4) == ".--."){
      decoded += "P";
      i += 3;
    }
    else if (msg.substring(i,i+4) == "--.-"){
      decoded += "Q";
      i += 3;
    }
    else if (msg.substring(i,i+4) == "...-"){
      decoded += "V";
      i += 3;
    }
    else if (msg.substring(i,i+4) == "-..-"){
      decoded += "X";
      i += 3;
    }
    else if (msg.substring(i,i+4) == "-.--"){
      decoded += "Y";
      i += 3;
    }
    else if (msg.substring(i,i+4) == "--.."){
      decoded += "Z";
      i += 3;
    }
    else if (msg.substring(i,i+3) == "-.."){
      decoded += "D";
      i += 2;
    }      
    else if (msg.substring(i,i+3) == "--."){
      decoded += "G";    
      i += 2;
    }
    else if (msg.substring(i,i+3) == "-.-"){
      decoded += "K";
      i += 2;
    }
    else if (msg.substring(i,i+3) == "---"){
      decoded += "O";
      i += 2;
    }
    else if (msg.substring(i,i+3) == ".-."){
      decoded += "R";
      i += 2;
    }
    else if (msg.substring(i,i+3) == "..."){
      decoded += "S";
      i += 2;
    }
    else if (msg.substring(i,i+3) == "..-"){
      decoded += "U";
      i += 2;
    }
    else if (msg.substring(i,i+3) == ".--"){
      decoded += "W";
      i += 2;
    }
    else if (msg.substring(i,i+2) == ".."){
      decoded += "I";
      i++;
    }
    else if (msg.substring(i,i+2) == ".-"){
      decoded += "A";
      i++;
    }
    else if (msg.substring(i,i+2) == "--"){
      decoded += "M";
      i++;
    }
    else if (msg.substring(i,i+2) == "-."){
      decoded += "N";
      i++;
    }
    else if (msg.substring(i,i+1) == ".")
      decoded += "E";
    else if (msg.substring(i,i+1) == "-")
      decoded += "T";      
    else if (msg.substring(i,i+1) == " ")
      decoded += " ";
    else
      continue;
  }
  return decoded;
}

void loop(){
  
}
