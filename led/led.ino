/*
Reading a serial ASCII-encoded string.
This sketch demonstrates the Serial parseInt() function.
It looks for an ASCII string of comma-separated values.
It parses them into ints, and uses those to fade an RGB LED.
Circuit: Common-anode RGB LED wired like so: * Blue cathode: digital pin 9
* Red cathode: digital pin 11
* Green cathode: digital pin 10
* anode: +5V
This example code is in the public domain. */
// pins for the LEDs:
const int r_1 = 11; 
const int g_1 = 10; 
const int b_1 = 9;
const int r_2 = 6; 
const int g_2 = 5; 
const int b_2 = 3;
//const int r_3 = 7; 
//const int g_3 = 6; 
//const int b_3 = 5;

void setup () {
  // initialize serial: 
  Serial.begin(9600);
  // make the pins outputs: 
  pinMode(r_1 , OUTPUT); 
  pinMode(g_1 , OUTPUT); 
  pinMode(b_1 , OUTPUT);
  pinMode(r_2 , OUTPUT); 
  pinMode(g_2 , OUTPUT); 
  pinMode(b_2 , OUTPUT);
  //pinMode(r_3 , OUTPUT); 
  //pinMode(g_3 , OUTPUT); 
  //pinMode(b_3 , OUTPUT);
}

void loop () {
// if there’s any serial available, read it: 
  while (Serial.available()) {
    Serial.println("Serial is ready!"); 
    // look for the next valid integer in the incoming serial stream:
    Serial.print("Input is ");
    int red = Serial.parseInt(); // do it again:
    int green = Serial.parseInt(); // do it again:
    int blue = Serial.parseInt();
    Serial.print("red: "); 
    Serial.print(red);
    Serial.print(" "); 
    Serial.print("green: "); 
    Serial.print(green);
    Serial.print(" "); 
    Serial.print("blue: "); 
    Serial.println(blue);
    
    // look for the newline. That’s the end of your sentence:
    //if (Serial.read() == "\n" or Serial.read() == "\r") {
    //if (blue == 70) {
    if (Serial.read() == -1) {
      Serial.println("Change color"); 
      // constrain the values to 0 - 255 and invert
      // if you’re using a common-cathode LED, just use "constrain(color, 0, 255) ;"
      //red = 255 - constrain(red, 0, 255); 
      //green = 255 - constrain(green, 0, 255); 
      //blue = 255 - constrain(blue, 0, 255);
      red = constrain(red, 0, 255); 
      green = constrain(green, 0, 255); 
      blue = constrain(blue, 0, 255);

       // print the three numbers in one string as hexadecimal:
      Serial.print(red, HEX); 
      Serial.print(green , HEX); 
      Serial.println(blue, HEX);
      
      // fade the red, green, and blue legs of the LED:
      analogWrite(r_1 , red); 
      analogWrite(g_1 , green); 
      analogWrite(b_1 , blue);
      analogWrite(r_2 , red); 
      analogWrite(g_2 , green); 
      analogWrite(b_2 , blue);
      //analogWrite(r_3 , red); 
      //analogWrite(g_3 , green); 
      //analogWrite(b_3 , blue);
    } 
  }
}
