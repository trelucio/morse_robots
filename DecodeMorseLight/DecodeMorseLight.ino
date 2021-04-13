/* GetActiveColor - Color Sensor for use with the Core Spartan Controller
  (c) Modern Robotics Inc. 2015  http://www.modernroboticsinc.com
        
  The Color Sensor uses various channels of color to determine the approximate color of an 
  object. This data includes a color number that corresponds to the color line in the 
  documentation, as well as raw and adjusted readings. Best results will be attained in a 
  well-lit area and the object no more than 7cm away from the sensor. 
  
  This example takes active readings at 60Hz and displays all of the data registers to the serial 
  monitor. In active mode, readings are takenwith the LED lit and readings are taken with the off 
  insequence. The two readings are subtracted to achieve areading for only reflected light. The 
  readings at taken at 60Hz, making the white LED appear as if it is on all the time. Press the 
  TOUCH button to take a single activecolor reading of an object or light source and display the 
  reading values to the serial terminal. Refer to the documentation for more information on 
  calibrating and descriptions of the returned values. 
    
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
-------------------------------------------------------------------------------------------*/
#include "CORE.h"

// Create an instance of the class CORE_COLOR_SENSOR named color using the default I2C address
CORE_COLOR_SENSOR color;

// Create an instance of the class CORE_DIGITAL named push on port D7
CORE_DIGITAL push(7);

// Create four variables to store all the color Sensor readings
int red, green, blue, white;       

// Interval at which to read light/speed at which (milliseconds)
const int interval = 200;  

void setup(){
  // Initialize serial communications at 9600 baud
  Serial.begin(9600);
  
  // Set the mode and sample rate of the color Sensor to PASSIVE at 60Hz (US Standard)
  // Frequency that the Sesnor picks up
  // 1 Hz = 1000 ms; f = 1/T
  color.colorSetup(color.PASSIVE, color.SIXTY);

  /*String msg = "";
  while (msg.substring(msg.length()-3, msg.length()) != "+++"){
    if (millis() % interval >= 0 && millis() % interval <= 1)
      msg += readColor();
  }
  Serial.print(msg);*/
}

// Read Color by finding greatest/strongest color value found in sensor
String readColor(){
   // Get the current values of the three color channels and the white channel.
   color.getColorValue(red, green, blue, white);

   // Color to String Morse
   String msg = ""; 

  if (red > green && red > blue && red > white) // red = "."
    msg += ".";
  else if (blue > red && blue > green && blue > white) // blue = "-"
    msg += "-";
  else if (white > red && white > green && white > blue) // white = " "
    msg += " ";
  else if (green > red && green > blue && green > white) // PRINT CHAR/DECODE
    msg += "+";
    
  return msg;
  //Serial.print(msg);
}

String decode(String msg){
  for (int i = 0; i < msg.length(); i++){
    if (msg.substring(i,i+1) == ".-")
      Serial.print("A");
    else if (msg.substring(i,i+1) == "-...")
      Serial.print("B");
    else if (msg.substring(i,i+1) == "-.-.")
      Serial.print("C");
    else if (msg.substring(i,i+1) == "-..")
      Serial.print("D");
    else if (msg.substring(i,i+1) == ".")
      Serial.print("E");
    else if (msg.substring(i,i+1) == "..-.")
      Serial.print("F");
    else if (msg.substring(i,i+1) == "--.")
      Serial.print("G");
    else if (msg.substring(i,i+1) == "....")
      Serial.print("H");
    else if (msg.substring(i,i+1) == "..")
      Serial.print("I");
    else if (msg.substring(i,i+1) == ".---")
      Serial.print("J");
    else if (msg.substring(i,i+1) == "-.-")
      Serial.print("K");
    else if (msg.substring(i,i+1) == ".-..")
      Serial.print("L");
    else if (msg.substring(i,i+1) == "--")
      Serial.print("M");
    else if (msg.substring(i,i+1) == "-.")
      Serial.print("N");
    else if (msg.substring(i,i+1) == "---")
      Serial.print("O");
    else if (msg.substring(i,i+1) == ".--.")
      Serial.print("P");
    else if (msg.substring(i,i+1) == "--.-")
      Serial.print("Q");
    else if (msg.substring(i,i+1) == ".-.")
      Serial.print("R");
    else if (msg.substring(i,i+1) == "...")
      Serial.print("S");
    else if (msg.substring(i,i+1) == "-")
      Serial.print("T");
    else if (msg.substring(i,i+1) == "..-")
      Serial.print("U");
    else if (msg.substring(i,i+1) == "...-")
      Serial.print("V");
    else if (msg.substring(i,i+1) == ".--")
      Serial.print("W");
    else if (msg.substring(i,i+1) == "-..-")
      Serial.print("X");
    else if (msg.substring(i,i+1) == "-.--")
      Serial.print("Y");
    else if (msg.substring(i,i+1) == "--..")
      Serial.print("Z");
    else if (msg.substring(i,i+1) == " ")
      Serial.print(" ");
    else if (msg.substring(i,i+1) == "+++")
      Serial.println("END OF MESSAGE");
  }
}

void loop(){
  // At interval (time from start of program % interval == 0), readColor()
  if (millis() % interval >= 0 && millis() % interval <= 1){
    color.getColorValue(red, green, blue, white);

    // Color to String Morse
    String msg = ""; 

    if (red > green && red > blue && red > white) // red = "."
      msg += ".";
    else if (blue > red && blue > green && blue > white) // blue = "-"
      msg += "-";
    else if (white > red && white > green && white > blue) // white = " "
      msg += " ";
    else if (green > red && green > blue && green > white) // PRINT CHAR/DECODE
      msg += "+";
      
    Serial.print(msg);
  }
  
}
