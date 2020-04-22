# Customisation and needed library

1.8.9 on windows xp. Someone must certainly earlier have taken the steps I do here, but It just lies aheah.

### Installation

Having had an earlier version, just unpack the Arduino IDE zip and check registry values.

### Settings (file->settings)

- Sketchbook folder
- enable verbose output 

### Shortcut in root of Sketchbook

Seems no harme to use root of Sketchbook as links collection as any Sketches/Libraries goes in subfolders.

Identifying placement of Arduino.h and subsequent places from where they are included.

#### lines 23-32

    #include <stdlib.h>
    #include <stdbool.h>
    #include <string.h>
    #include <math.h>
    
    #include <avr/pgmspace.h>
    #include <avr/io.h>
    #include <avr/interrupt.h>
    
    #include "binary.h"

Naming the tre include libraries links residing in Sketchbook and cross referensed in there back to Sketchbook root.

- quote_inlude
- gcc_include
- avr_include

link to arduino.exe

hyperterminal - settings of shorcut

- emulering
    - tty
- ascii transmit
    - send newline
    - local echo
- ascii recieve
    - add newline


### Libraries

##### cmdLoop

Loop that servers running a command as serial request and still calls a function repeatedly 

##### sendf

We can't be that verbose

    Serial.print("the air temperature is ");
    Serial.print(airTemp);
    Serial.println(" degrees.");

The format facilities of printf must be implemented! A quick test and following internet seach reveals that printf and is't cousins, as standard setup in arduino IDE, don't include formating floats.
Instead of envestigating the cost of changing compilig switches, we simple makes some worarounds which price in RAM usage is obvious.



### Links of interests

##### [arduino reference](https://www.arduino.cc/reference/en/)

