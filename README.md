# Customisation and needed library

1.8.9 on windows xp. Someone must certainly earlier have taken the steps I do here, but It just lies aheah.

### Installation

Having had an earlier version, just unpack the Arduino IDE zip and check registry values.

### settings (file->settings)

- Sketchbook folder
- enable verbose output 

### shortcut in root of Sketchbook

Seems no harme to use root of Sketchbook as links collection as any Sketch/Library goes in subfolders.

Identifying placement of Arduino.h and subsequent from included there

#### lines 23-32

    #include <stdlib.h>
    #include <stdbool.h>
    #include <string.h>
    #include <math.h>
    
    #include <avr/pgmspace.h>
    #include <avr/io.h>
    #include <avr/interrupt.h>
    
    #include "binary.h"

tre include libraries. Cross referensed by links:

- quote_inlude
- gcc_include
- avr_include

link to arduino.exe

hyperterminal settings

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



### Links of interests

##### [arduino reference](https://www.arduino.cc/reference/en/)

