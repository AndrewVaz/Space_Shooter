/* Andrew Vaz
    Project 1:  Play || Space Shooter
    DESN30146 Interactive Objects and Environments 1: Products
*/
//------------------------------ Base of code is from Combined Demo by Marc MERLIN <marc_soft@merlins.org> ---------------------- START
#include "Arduino_SensorKit.h"

// Added LED2 - LED4
#define LED4 13
#define LED3 12
#define LED2 11
#define LED1 10
//------------------------------ Base of code is from Combined Demo by Marc MERLIN <marc_soft@merlins.org> ---------------------- END

// Base of code is from Combined Demo by Marc MERLIN <marc_soft@merlins.org>
#define BUTTON  4
bool button_state;

//------------------------------ Base of code is from Doug Whitton Sept 2021 Pot1-p5serialcontrol ------------------------------- START
int potentiometer = A0; //Assign to pin A0
//------------------------------ Base of code is from Doug Whitton Sept 2021 Pot1-p5serialcontrol ------------------------------- END


int start = 0;
int btnp = 0; // for button presses
int randnum;
int sum = 0;
int tries = 0;


void setup() {

  Serial.begin(9600);

  randNumb();
  
  //------------------------------ Base of code is from Doug Whitton Sept 2021 Pot1-p5serialcontrol ------------------------------- START
  pinMode(potentiometer, INPUT); // Sets the pinmode to input
  Oled.begin(); // Starting the oled screen
  Oled.setFlipMode(true); // Rotating the screen so the OLEDed content is facing us
  Oled.setFont(u8x8_font_chroma48medium8_r); // font
  Oled.setCursor(3, 3); // Setting the line the text will be OLEDed
  Oled.println("Press Button");
  //------------------------------ Base of code is from Doug Whitton Sept 2021 Pot1-p5serialcontrol ------------------------------- END
}

void randNumb() {
  //-------------------- Base of code is from https://www.arduino.cc/reference/en/language/functions/random-numbers/random/-------- START
  // If you need help to understand this code watch this -> https://www.youtube.com/watch?v=carW87rGe7c&ab_channel=UdemyTech
  randomSeed(analogRead(A1)); // Getting analog value from a non connected port to create a seed at every start instance
  // random seed is needed for the random number otherwise rand # will always display the same numbers every reset
  // I dislike random numbers >:(
  randnum = random(1, 180); // randnum will be the target number the user has to determine from rotating the POT
  //-------------------- Base of code is from https://www.arduino.cc/reference/en/language/functions/random-numbers/random/-------- END
}

// Flashy flashy :)
void flashy() {
  digitalWrite(LED1, HIGH);
  delay(100);
  digitalWrite(LED2, HIGH);
  delay(100);
  digitalWrite(LED3, HIGH);
  delay(100);
  digitalWrite(LED4, HIGH);
  delay(100);
  digitalWrite(LED1, LOW);
  delay(100);
  digitalWrite(LED2, LOW);
  delay(100);
  digitalWrite(LED3, LOW);
  delay(100);
  digitalWrite(LED4, LOW);
}

//--------------------------------------------------------------------------------------- START
// Decides the direction the lights start from
// If the number is smaller than the POT the lights start from the right
// If the number is larger than the POT the light start from the left
int on1(int x, int y) {
  if (x > y) {
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);
  }
  else  {
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, HIGH);
  }
}

int on2(int x, int y) {
  if (x > y) {
    digitalWrite(LED1, HIGH);
    delay(100);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);
  }
  else {
    digitalWrite(LED2, LOW);
    digitalWrite(LED1, LOW);
    delay(100);
    digitalWrite(LED4, HIGH);
    delay(100);
    digitalWrite(LED3, HIGH);
  }
}

int on3(int x, int y) {
  if (x > y) {
    digitalWrite(LED1, HIGH);
    delay(100);
    digitalWrite(LED2, HIGH);
    delay(100);
    digitalWrite(LED3, HIGH);
    digitalWrite(LED4, LOW);
  }
  else {
    digitalWrite(LED1, LOW);
    delay(100);
    digitalWrite(LED4, HIGH);
    delay(100);
    digitalWrite(LED3, HIGH);
    delay(100);
    digitalWrite(LED2, HIGH);
  }
}

int on4(int x, int y) {
  if (x > y) {
    digitalWrite(LED1, HIGH);
    delay(100);
    digitalWrite(LED2, HIGH);
    delay(100);
    digitalWrite(LED3, HIGH);
    delay(100);
    digitalWrite(LED4, HIGH);
  }
  else {
    digitalWrite(LED4, HIGH);
    delay(100);
    digitalWrite(LED3, HIGH);
    delay(100);
    digitalWrite(LED2, HIGH);
    delay(100);
    digitalWrite(LED1, HIGH);
  }
}
//--------------------------------------------------------------------------------------- END
void off4() {
  digitalWrite(LED1, LOW);
  delay(100);
  digitalWrite(LED2, LOW);
  delay(100);
  digitalWrite(LED3, LOW);
  delay(100);
  digitalWrite(LED4, LOW);
}

// UFO :)
void ufo() {
  Oled.setCursor(2, 0);
  Oled.println("<O>");
  delay(100);
  Oled.clearDisplay();

  Oled.setCursor(6, 1);
  Oled.println("<O>");
  Oled.setCursor(6, 2);
  delay(50);
  Oled.println("/ \\");
  Oled.setCursor(5, 3);
  delay(50);
  Oled.println("/   \\");
  delay(100);
  Oled.clearDisplay();

  Oled.setCursor(10, 0);
  Oled.println("<O>");
  delay(100);
  Oled.clearDisplay();
}

// Pew Pew :)
void shoot() {
  Oled.setCursor(2, 6);
  Oled.println("/");
  Oled.setCursor(1, 7);
  Oled.println("/");

  Oled.setCursor(14, 6);
  Oled.println("\\");
  Oled.setCursor(15, 7);
  Oled.println("\\");
  delay(50);
  Oled.clearDisplay();
}
