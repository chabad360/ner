/*	 The Ner Memorial Plaque Lighting System is a modern system for controlling the light on a memorial plaque
     Copyright (C) 2016  Mendel Greenberg

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


#include <Key.h>
#include <Keypad.h>

const byte ROWS = 4; // Four rows
const byte COLS = 4; // Four columns

char keys[ROWS][COLS] =  /* Define the Keymap */ {
    {'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'*','0','#','D'}
};

byte rowPins[ROWS] = { A8, A9, A10, A11 }; // Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.

byte colPins[COLS] = { A12, A13, A14, A15 }; // Connect keypad COL0, COL1, COL2 and COL3 to these Arduino pins.

Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS ); // Create the Keypad

String num; // The LED we are trying to reach (used by the keypad)
 
#define fli A1 // The indicator LED
int leds[51] /* All our LEDs (in the addressable mode) */ = { 0, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51}; //An array of all the leds
String nums[51] /* All our LEDs (the way we type them) */ = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "23", "24", "25", "26", "27", "28", "29", "30", "31", "32", "33", "34", "35", "36", "37", "38", "39", "40", "41", "42", "43", "44", "45", "46", "47", "48", "49", "50", "51" }; //An array of identifiers for them

void setup()
{
	// Initialize all LEDs
	for (int i = 0; i <= nums->length(); i++)
	{
		pinMode(leds[i], OUTPUT);
		digitalWrite(leds[i], LOW);
		break;
	}
  
    pinMode(fli, OUTPUT);
	digitalWrite(fli, LOW);
}

void loop()
{
    char key = kpd.getKey();
    if(key)  // Check for a valid key.
    {
        switch (key)
        {
            case '0':
				addNum("0");
                break;
            case '1':
				addNum("1");
                flash();
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
				toggle("all", HIGH);
				break;
            case 'B':
				for (int i = 0; i <= nums->length(); i++) // run through all entries in nums
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
				toggle(num, HIGH);
				num = "\0";
				break;
            case '*':
				if (num != NULL)
				{
					toggle(num, LOW);
					num = "\0"
				} else {
					toggle("all", LOW);
				}
				num = "\0";
				break;
        }
    }
}

void addNum(String nta)
{
	num = num + nta;
	flash;
}

void flash() // flash indicator
{
    digitalWrite(fli, HIGH);
    delay(100);
    digitalWrite(fli, LOW);
    delay(100);
    digitalWrite(fli, HIGH);
    delay(100);
    digitalWrite(fli, LOW);
}

void toggle( String num, int HL )
{
	for (int i = 0; i <= nums->length(); i++) // run through all entries in nums
	{
		if (num == nums[i] || num == "all")
		{
			digitalWrite(leds[i], HL);
			break;
		}
	}
}