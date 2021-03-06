/*	 The Ner Memorial Plaque Lighting System is a modern system for controlling the lights on a memorial board
     Copyright (C) 2016-18  Mendel Greenberg

     This program is free software: you can redistribute it and/or modify
     it under the terms of the GNU General Public License as published by
     the Free Software Foundation, either version 3 of the License, or
     any later version.

     This program is distributed in the hope that it will be useful,
     but WITHOUT ANY WARRANTY; without even the implied warranty of
     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
     GNU General Public License for more details.

     You should have received a copy of the GNU General Public License
     along with this program.  If not, see <http://www.gnu.org/licenses/>
*/


// Ner Memorial Plaque Lighting System

#include <Keypad.h>

#pragma region keypad
const byte ROWS = 4; // Four rows on the Keypad
const byte COLS = 4; // Four columns on the Keypad

char keys[ROWS][COLS] =  /* Define the Keymap */ {
    {'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'*','0','#','D'}
};

byte rowPins[ROWS] = { A8, A9, A10, A11 }; // Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.

byte colPins[COLS] = { A12, A13, A14, A15 }; // Connect keypad COL0, COL1, COL2 and COL3 to these Arduino pins.

Keypad kpd = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS); // Create the Keypad.

String num; // The LED we are trying to reach (used by the keypad).
#pragma endregion

#define indicator A1 // The indicator LED.

#pragma region LEDs
#define amount 51 // The amount of LEDs, necessary to turn them on.

/* All our LEDs (in the addressable mode) */ int leds[amount] = { 53 /* This is LED number 1 but because we use serial, we need to have it at another pin, and 53 works */, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51 };

/* All our LEDs (the way we type them) */ String nums[amount] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "23", "24", "25", "26", "27", "28", "29", "30", "31", "32", "33", "34", "35", "36", "37", "38", "39", "40", "41", "42", "43", "44", "45", "46", "47", "48", "49", "50", "51", };
#pragma endregion

void setup()
{
	// Initialize all LEDs
	for (int i = 0; i <= amount; i++)
	{
		pinMode(leds[i], OUTPUT);
		digitalWrite(leds[i], LOW);
	}

	Serial.begin(9600); // Useful when you want to add outside communication to the system (e.x. testing, RPi, etc.)

	// Initialize indicator LED
    pinMode(indicator, OUTPUT);
	digitalWrite(indicator, LOW);

}

void loop()
{
	char key;
	key	= kpd.getKey(); // Get the key from the keypad...
	if (Serial.available() == true) // or from serial.
	{
		key = Serial.read();
	}

    if(key)  // If there is a key:
    {
        switch (key) // Then... it depends on the key:
        {
            case '0':
				addNum("0");
                break;
            case '1':
				addNum("1");
                break;
            case '2':
				addNum("2");
                break;
            case '3':
				addNum("3");
                break;
            case '4':
				addNum("4");
                break;
            case '5':
				addNum("5");
                break;
            case '6':
				addNum("6");
                break;
            case '7':
				addNum("7");
                break;
            case '8':
				addNum("8");
                break;
            case '9':
				addNum("9");
                break;
            case 'A':
				state("all", HIGH); // Toggle them all!!!
				break;
            case 'B':
				// Running this loop is more efficient than running state(), but this feature might be useless, I don't remember why I added it. ~chabad360
				for (int i = 0; i <= amount; i++) // run through all entries in 'nums'
				{
					digitalWrite(leds[i], HIGH);
					delay(1000);
					digitalWrite(leds[i], LOW);
				}
				break;
            case 'C':
				break;
            case 'D':
                break;
            case '#':
				state(num, HIGH); // Toggle the specified LED
				num = "\0";
				break;
            case '*':
				if (num != NULL)
				{
					state(num, LOW); // Either toggle the specified LED
					num = "\0";
				} else {
					state("all", LOW); // or if no LED is specified then turn them all off
				}
				num = "\0";
				break;
        }
    }
}

#pragma region addNum()
/*
	void addNum(nta)
	Desc: Concatenates the number 'nta' to 'num', used in our switch/case.
	Args: String nta: The number to concatenate.
*/
void addNum(String nta)
{
	num = num + nta;
	flash;
}
#pragma endregion

#pragma region flash()
/*
	void flash()
	Desc: Flashes the indicator LED twice.
*/
void flash()
{
    digitalWrite(indicator, HIGH);
    delay(100);
    digitalWrite(indicator, LOW);
    delay(100);
    digitalWrite(indicator, HIGH);
    delay(100);
    digitalWrite(indicator, LOW);
}
#pragma endregion


#pragma region state()
/* 
	void state(num, HL)
	Desc: toggles LED 'num' to state 'HL'.
	Args: String num: The LED to toggle (in the 'nums' array format).
		  int HL: The state to set the LED to, can be HIGH or LOW.
*/
void state( String num, int HL )
{
	for (int i = 0; i <= amount; i++) // Run through all entries in 'nums'
	{
		if (num == nums[i] || num == "all")
		{
			digitalWrite(leds[i], HL);
		}
	}
}
#pragma endregion