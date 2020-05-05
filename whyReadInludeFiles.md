My experience of finding information is like that of starting programming Java. Some time elapsed before i figured out that all documentation was part of the development installation - the full class names which points to javadoc.

Arduino.h starts:

#### lines 23-32

    #include <stdlib.h>
    #include <stdbool.h>
    #include <string.h>
    #include <math.h>
    
    #include <avr/pgmspace.h>
    #include <avr/io.h>
    #include <avr/interrupt.h>
    
    #include "binary.h"

And those files reveals 3 include libraries with doxygen documented files. 