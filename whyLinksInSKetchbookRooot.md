For those of us which cli of cmd.exe and totalcommander is the preferred alternative to startmenu and desktop links, the root of sketchbook is convenient place to have links to all.
It is possible because the Arduini IDE don't care as every sketches/libraries goes in subfolders.

Identifying placement of Arduino.h and subsequent from 

- lines 23-32
    - #include <stdlib.h>
    - #include <stdbool.h>
    - #include <string.h>
    - #include <math.h>
    - 
    - #include <avr/pgmspace.h>
    - #include <avr/io.h>
    - #include <avr/interrupt.h>
    - 
    - #include "binary.h"

places from where they are included reveals 3 include libraries I chose to name

- quote_inlude
- gcc_include
- avr_include
