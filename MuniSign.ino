 


// Pins for the row drivers
int row1Pin = 1;
int row2Pin = 2;
int row3Pin = 3;
int rowEnable = 4;
int rclockPin = 5;
int clockPin = 6;
int dataPin = 7;
int gdataPin = 8;
// Set the pins to output to the sign
void setup() {
  pinMode(row1Pin, OUTPUT);
  pinMode(row2Pin, OUTPUT);
  pinMode(row3Pin, OUTPUT);
  pinMode(rowEnable, OUTPUT);
  pinMode(rclockPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(gdataPin, OUTPUT);
}

//=== Character Array ===
// Characters are A, B, C, etc.  Only upper case, no symbols.  
byte alphabets[][8] = {
  {0, 04, 10, 17, 17, 31, 17, 17}, //A
  {0, 30, 17, 17, 30, 17, 17, 30}, //B
  {0, 14, 17, 16, 16, 16, 17, 14}, //C
  {0, 28, 18, 17, 17, 17, 18, 28}, //D
  {0, 31, 16, 16, 31, 16, 16, 31}, //E
  {0, 31, 16, 16, 31, 16, 16, 16}, //F
  {0, 14, 17, 16, 16, 19, 17, 14}, //G
  {0, 17, 17, 17, 31, 17, 17, 17}, //H
  {0, 14, 04, 04, 04, 04, 04, 14}, //I
  {0, 07, 02, 02, 02, 02, 10, 14}, //J
  {0, 17, 18, 20, 24, 20, 18, 17}, //K
  {0, 16, 16, 16, 16, 16, 16, 31}, //L
  {0, 10, 21, 21, 21, 17, 17, 17}, //M
  {0, 17, 25, 25, 21, 19, 19, 17}, //N
  {0, 14, 17, 17, 17, 17, 17, 14}, //O
  {0, 30, 17, 17, 30, 16, 16, 16}, //P
  {0, 14, 17, 17, 17, 17, 19, 15}, //Q
  {0, 30, 17, 17, 30, 20, 18, 17}, //R
  {0, 14, 17, 16, 14, 01, 17, 14}, //S
  {0, 31, 04, 04, 04, 04, 04, 04}, //T
  {0, 17, 17, 17, 17, 17, 17, 14}, //U
  {0, 17, 17, 17, 10, 10, 10, 04}, //V
  {0, 17, 17, 17, 21, 21, 21, 10}, //W
  {0, 17, 17, 10, 04, 10, 17, 17}, //X
  {0, 17, 10, 10, 04, 04, 04, 04}, //Y
  {0, 31, 8, 04, 02, 04, 8, 31}, //Z
  {0, 0, 21, 14, 31, 14, 21, 0}, //*
};
byte bitmap[][8] = {  //red characters
  {0, 0,0,0,0,0,0,0},
  {0, 0,0,0,0,0,0,0},
  {0, 0,0,0,0,0,0,0},
  {0, 06,8,16,30,17,17,14}, // Num 6
  {0, 00,00,26,21,21,17,17}, // m
  {0, 0,4,0,4,4,4,4}, // i
  {0, 0,0,22,25,17,17,17}, // n
  {0, 0,0,0,0,0,0,0},
  {0, 14,17,1,2,4,8,31},
  {0, 14,17,1,2,4,8,31},
  {0, 00,00,26,21,21,17,17}, // m
  {0, 0,4,0,4,4,4,4}, // i
  {0, 0,0,22,25,17,17,17}, // n
  {0, 0,0,0,0,0,0,0},
};
byte gbitmap[][8] = {  //green characters
  { 0, 0,0,0,0,0,0,0},
  { 0, 04,14,31,04,04,04,04},
  {0, 0,0,0,0,0,0,0},
  {0, 06,8,16,30,17,17,14}, // Num 6
  {0, 0,0,0,0,0,0,0},
  {0, 0,0,0,0,0,0,0},
  {0, 0,0,0,0,0,0,0},
  {0, 0,0,0,0,0,0,0},
  {0, 14,17,1,2,4,8,31},
  {0, 14,17,1,2,4,8,31},
  {0, 0,0,0,0,0,0,0},
  {0, 0,0,0,0,0,0,0},
  {0, 0,0,0,0,0,0,0},
  {0, 0,0,0,0,0,0,0},
};
void RunSign()
{
  //****************************************************//
  //  Name    : Color Cadaces Driver                    //
  //  Author  : Bob Davis                               //
  //  Date    : 23 February, 2013                       //
  //  Version : 1.0                                     //
  //****************************************************//
  for (int row = 7; row > 0; row--)
  {
    // turn off display
    digitalWrite(rowEnable, HIGH); 
    digitalWrite(rclockPin, LOW); 
    // send serial data to display 14 = number of characters
    for (int character = 0; character < 14; character++)
    {
      for (int shiftbit = 5; shiftbit > -1; shiftbit--){
    if bitRead(gbitmap[character][row],shiftbit) digitalWrite(gdataPin, HIGH); else digitalWrite(gdataPin, LOW);
    if bitRead(bitmap[character][row],shiftbit) digitalWrite(dataPin, HIGH); else digitalWrite(dataPin, LOW);
    digitalWrite(clockPin, HIGH); digitalWrite(clockPin, LOW);
      }
    }
    //latch the data
    digitalWrite(rclockPin, HIGH);
    // set up 74138 row sesection and turn display back on
    if bitRead(row,0) digitalWrite (row1Pin, HIGH); else digitalWrite(row1Pin, LOW);  
    if bitRead(row,1) digitalWrite (row2Pin, HIGH); else digitalWrite(row2Pin, LOW); 
    if bitRead(row,2) digitalWrite (row3Pin, HIGH); else digitalWrite(row3Pin, LOW);
    digitalWrite(rowEnable, LOW);
    // Wait to see what we sent to the display ;
    delayMicroseconds(500); 
  }
}  

//=== L O O P ===
void loop() {
  RunSign();
}
