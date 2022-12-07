#include <LiquidCrystal.h>
#include <Servo.h>

// Variable: RGB LED
const int r_1 = 6, g_1 = 3, b_1 = 5;  // RGB LED pins
unsigned int r_1_cc, g_1_cc, b_1_cc, r_2_cc, g_2_cc, b_2_cc;  // color code
unsigned int r_1_cc_temp, g_1_cc_temp, b_1_cc_temp;  // previous color value

// Variable: Buzzer
const int buzzer = 2;  // Buzzer pin
unsigned long buzzer_start_time;  // start time for buzzer
const int buzzer_duration=200;  // buzzer sound duration

// Variable: LCD
const int rs = 12, en = 11, d4 = 7, d5 = 8, d6 = 9, d7 = 13;  // LCD Pins
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Variable: Servo
Servo myservo;
const int servo_pin = 10;  // servo pin
unsigned int servo_pos;  // servo position
unsigned int servo_pos_temp;  // previous servo position 

// Variable: Others
unsigned int level = 0;

void clearLCD(int column, 
              int row){
  lcd.setCursor(column, row);
  lcd.print("               ");
}

void startBuzzer(unsigned long start_time){
  // Buzzer function
  if (millis()-start_time<=buzzer_duration){
    digitalWrite(buzzer, HIGH);
  }else{
    digitalWrite(buzzer, LOW);
  }
}

void dataSend(unsigned int r, 
              unsigned int g, 
              unsigned int b, 
              unsigned int angle,
              unsigned int level) {
  // Send data to pc
  Serial.print(r);
  Serial.print(' ');
  Serial.print(g);
  Serial.print(' ');
  Serial.print(b);
  Serial.print(' ');
  Serial.print(angle);
  Serial.print(' ');
  Serial.print(level);
  Serial.print("\n");
}

void setup () {
  // Initialize: serial: 
  Serial.begin(9600);
  
  // Initialize: RGB LED: 
  pinMode(r_1 , OUTPUT); 
  pinMode(g_1 , OUTPUT); 
  pinMode(b_1 , OUTPUT);
  r_1_cc=0, g_1_cc=0, b_1_cc=0;// Store previous state of RGB LED.
//  r_1_cc_temp = 0;
//  g_1_cc_temp = 0;
//  b_1_cc_temp = 0;

  // Initialize: Buzzer: 
  pinMode(buzzer , OUTPUT);
  
  // Initialize: LCD
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Level: ");
  lcd.setCursor(0, 1);
  lcd.print("Degree: ");

  // Initialize: Servo
  myservo.attach(servo_pin);
  servo_pos=0;
//  servo_pos_temp = 0;
}

void loop () {
  char *r_1_buff, *g_1_buff, *b_1_buff, *servo_pos_buff;
  int len;
  String serialReceive;

  // Read string from Serial port
  serialReceive = Serial.readStringUntil('\n');

  len = serialReceive.length();
  char buf[len+1];

  // Change message to char 
  serialReceive.toCharArray(buf, sizeof(buf));
  r_1_buff = strtok(buf," ");
  r_1_cc = atoi(r_1_buff);
  g_1_buff = strtok(NULL," ");
  g_1_cc = atoi(g_1_buff);
  b_1_buff = strtok(NULL," ");
  b_1_cc = atoi(b_1_buff);
  servo_pos_buff = strtok(NULL," ");
  servo_pos = atoi(servo_pos_buff);
  
  r_1_cc = constrain(r_1_cc, 0, 255);
  g_1_cc = constrain(g_1_cc, 0, 255);
  b_1_cc = constrain(b_1_cc, 0, 255);
  servo_pos = constrain(servo_pos, 0, 180);

  lcd.setCursor(7, 0);
  if (servo_pos == 0) {
    level = 0;
    lcd.print('0');
  }else if (servo_pos == 36) {
    level = 1;
    lcd.print('1');
  }else if (servo_pos == 72) {
    level = 2;
    lcd.print('2');
  }else if (servo_pos == 108) {
    level = 3;
    lcd.print('3');
  }else if (servo_pos == 144) {
    level = 4;
    lcd.print('4');
  }else if (servo_pos == 180) {
    level = 5;
    lcd.print('5');
  }
//  // Write LCD Row0 (LED)
//  lcd.setCursor(7, 0);
//  lcd.print(r_1_cc);
//  lcd.setCursor(9, 0);
//  lcd.print(g_1_cc);
//  lcd.setCursor(13, 0);
//  lcd.print(b_1_cc);
  
  // Write LCD Row1 (Servo)
  lcd.setCursor(8, 1);
  lcd.print(servo_pos);
  lcd.print(" deg");
  
  // Start LED
  analogWrite(r_1 , r_1_cc); 
  analogWrite(g_1 , g_1_cc); 
  analogWrite(b_1 , b_1_cc);
  if ((r_1_cc != r_1_cc_temp) or 
      (g_1_cc != g_1_cc_temp) or 
      (b_1_cc != b_1_cc_temp)){
//    clearLCD(5, 0);  // Clear LCD data
    buzzer_start_time = millis();  // Start buzzer
  }
  startBuzzer(buzzer_start_time); // Buzzer function

  // Start servo
  if (servo_pos != servo_pos_temp){
    myservo.write(servo_pos);  // Change position of servo
    delay(300);
    clearLCD(7, 0);  // Clear LCD data
    clearLCD(8, 1);  // Clear LCD data
  }

  // Send data to pc
  dataSend(r_1_cc, g_1_cc, b_1_cc, servo_pos, level);
  
  // Store previous state.
  r_1_cc_temp = r_1_cc;
  g_1_cc_temp = g_1_cc;
  b_1_cc_temp = b_1_cc;
  servo_pos_temp = servo_pos;
}
