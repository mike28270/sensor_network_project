// pins for the LEDs:
const int r_1 = 11; 
const int g_1 = 9; 
const int b_1 = 10;
const int r_2 = 6; 
const int g_2 = 3; 
const int b_2 = 5;

int r_1_cc=0, g_1_cc=0, b_1_cc=0, r_2_cc=0, g_2_cc=0, b_2_cc=0;  // color code
int r_1_cc_temp=255, g_1_cc_temp=255, b_1_cc_temp=255;  // color previous value

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
}

void loop () {
  char *r_1_buff, *g_1_buff, *b_1_buff, *r_2_buff, *g_2_buff, *b_2_buff;
  int len;
  String serialReceive;
  // if there’s any serial available, read it:   
  while (Serial.available()) {
    // look for the next valid integer in the incoming serial stream:
    serialReceive = Serial.readStringUntil('\n');
    
    len = serialReceive.length();
    char buf[len+1];
    serialReceive.toCharArray(buf, sizeof(buf));
    r_1_buff = strtok(buf," ");
    r_1_cc = atoi(r_1_buff);
    g_1_buff = strtok(NULL," ");
    g_1_cc = atoi(g_1_buff);
    b_1_buff = strtok(NULL," ");
    b_1_cc = atoi(b_1_buff);
    
    r_1_cc = constrain(r_1_cc, 0, 255);
    g_1_cc = constrain(g_1_cc, 0, 255); 
    b_1_cc = constrain(b_1_cc, 0, 255);
    
    // fade the red, green, and blue legs of the LED:
    analogWrite(r_1 , r_1_cc); 
    analogWrite(g_1 , g_1_cc); 
    analogWrite(b_1 , b_1_cc);
    analogWrite(r_2 , r_1_cc); 
    analogWrite(g_2 , g_1_cc); 
    analogWrite(b_2 , b_1_cc);

    if ((r_1_cc != r_1_cc_temp) or 
        (g_1_cc != g_1_cc_temp) or 
        (b_1_cc != b_1_cc_temp)){
//      Serial.print("Insert Table: ");
      Serial.print(r_1_cc);
      Serial.print(' ');
      Serial.print(g_1_cc);
      Serial.print(' ');
      Serial.print(b_1_cc);
    }
    r_1_cc_temp = r_1_cc;
    g_1_cc_temp = g_1_cc;
    b_1_cc_temp = b_1_cc;
    Serial.print("\n");
    //delay(100);
  }
}
