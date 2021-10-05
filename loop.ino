/* Andrew Vaz
    Project 1:  Play || Space Shooter
    DESN30146 Interactive Objects and Environments 1: Products
*/

void loop() {  
  button_state = digitalRead(BUTTON);

  //------------------------------ Base of code is from Doug Whitton Sept 2021 Pot1-p5serialcontrol ------------------------------- START
  int sensor_value = analogRead(potentiometer); //Read the value from the potentiometer connected to the A0 pin

  // (Changed the value places, so the POT value grows from clockwise and decreases counter-clockwise [0 to 180] )
  int value = map(sensor_value, 0, 1023, 180, 0); //Map the value from 0, 1023 to 180, 0
  //------------------------------ Base of code is from Doug Whitton Sept 2021 Pot1-p5serialcontrol ------------------------------- END

  // I only want this to happen once at the start
  if ((button_state == true) && start == 0)
  {
    Oled.clearDisplay();
    start++;
  }

  if (start > 0)
  {
    // Inital start sequence to let the user know the game has started
    if (start == 1)
    {
      // Flashing light for days
      do {
        Oled.setCursor(0, 3);
        Oled.print("Welcome to"); // Print the Values
        Oled.setCursor(0, 4);
        Oled.println("Space shooter"); // Print the Values

        flashy();

        start++;

      } while (start < 5); // After a count of 5 this loop stops

      Oled.clearDisplay();
      start = 2;
    }

    // This statement OLEDs the rules on the OLED screen
    else if (start == 2) {
      // When nothing is pressed OLED the first set of rules
      if (btnp <= 0) {
        // Oled OLED is 15 across x 7 down ****
        // Oled.print("OOOOOOOOOOOOOOO"); // Print the Values
        Oled.setCursor(0, 0);  // This stops the OLED from cycling
        Oled.println("Play guide:"); // Print the Values
        Oled.println("Rotate POT"); // Print the Values
        Oled.println("Hold Button"); // Print the Values
        Oled.println("Shoot UFO"); // Print the Values
        Oled.println("10 Tries"); // Print the Values
        Oled.println(""); // Print the Values
        Oled.println("PRESS BUTTON ->"); // Print the Values
      }

      // Clear the screen and makes 2nd statment true
      if (btnp == 1) {
        Oled.clearDisplay();
        btnp = 2;
      }
      // When button is pressed OLED the second set of rules
      if (btnp == 2) {
        Oled.setCursor(0, 0); // This stops the OLED from cycling. I despise this line >:(
        Oled.println("Lights: "); // Print the Values
        Oled.println("Range of UFO"); // Print the Values
        Oled.println("1 = within 60"); // Print the Values
        Oled.println("2 = within 40"); // Print the Values
        Oled.println("3 = within 20"); // Print the Values
        Oled.println("4 = within 5"); // Print the Values
        Oled.println("PRESS BUTTON ->"); // Print the Values
      }

      // Clear the screen and makes 3nd statment true
      if (btnp == 3) {
        Oled.clearDisplay();
        start = 3;
        btnp = 0;
      }

      // These statements have to remain in the bottom
      // because the second statment triggers automatically
      // if its under the btnp = 2 statment
      if (button_state == true && btnp == 0)
      {
        btnp = 1;
      }
      else  if (button_state == true && btnp == 2) // I despise this statment >:(
      {
        btnp = 3;
      }
    }
    else if (start == 3) {

      if (btnp <= 0) {
        Oled.setCursor(3, 3);
        Oled.println("Start Game");
        flashy();
        delay(1000);
        Oled.clearDisplay();
        btnp = 1;
      }
      else if (btnp == 2) {
        start = 1;
        btnp = 0;
      }
      
      if (btnp == 1) {

        if (button_state == true && tries <= 9) {
          shoot();
          tries++;

          if ((value > randnum) && !(value + 2 == randnum || value - 2 == randnum)) {
            sum = value - randnum;
            if (sum >= 0 && sum <= 5)
            {
              on4(value, randnum);
            }
            else if (sum > 5 && sum <= 40) {
              on3(value, randnum);
            }
            else if (sum > 40 && sum <= 60) {
              on2(value, randnum);
            }
            else if (sum > 60) {
              on1(value, randnum);
            }
            else
            {
              off4();
            }
          }
          else if ((value < randnum) && !(value + 2 == randnum || value - 2 == randnum)) {
            sum = randnum - value;
            if (sum >= 0 && sum <= 5)
            {
              on4(value, randnum);
            }
            else if (sum > 5 && sum <= 40) {
              on3(value, randnum);
            }
            else if (sum > 40 && sum <= 60) {
              on2(value, randnum);
            }
            else if (sum > 60) {
              on1(value, randnum);
            }
            else
            {
              off4();
            }
          }
          else {
            delay(1000);
            Oled.clearDisplay();
            Oled.setCursor(3, 3);
            Oled.println("Our Savior");
            Oled.setCursor(6, 4);
            Oled.println(":)");
            delay(3000);
            btnp = 2;
          }
        }
        ufo();
        if (tries == 10) {
          delay(1000);
          Oled.clearDisplay();
          Oled.setCursor(2, 3);
          Oled.println("MOOOOOOO!!!");
          Oled.setCursor(6, 4);
          Oled.println(":(");
          delay(3000);
          Oled.clearDisplay();
          Oled.setCursor(3, 3);
          Oled.println("NOOOOOOOO");
          Oled.setCursor(1, 4);
          Oled.println("OUR COWSSS!!!");
          delay(2000);
          btnp = 2;
          Oled.clearDisplay();
        }
      }
    }
  }
}
