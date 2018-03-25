# Ner Memorial Plaque Lighting System

[![build status](https://gitlab.com/chabad360/ner/badges/master/pipeline.svg)](https://gitlab.com/chabad360/ner/pipelines)

The Ner Memorial Plaque Lighting System is a controller for Memorial Boards in situations like this:
![](https://www.bcd-urbex.com/wp-content/uploads/2014/02/IMG_8063_4_5_6_7_tonemapped2.jpg)
It is designed to be easily integrated in to any sort of board as long as there is access to the LEDs in the back.

## Setup
 1. Bill of Materials:

| Name           | Amount       |
| -------------- | ------------ |
|4x4 Keypad      |1             |
|220 Ohm Resistor|1 for each LED|
|Orange LED      |Max 52 +1     |
|Arduino Mega    |1             |

2. Run the [ner-number-generator](https://gitlab.com/chabad360/ner-number-generator)
3. Replace lines `45` through `50` with the output.
4. Upload the sketch and send it to the arduino mega.
5. Follow the diagram to setup the arduino:
![](layout.jpg)