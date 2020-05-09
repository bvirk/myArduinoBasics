Programming is power at our fingertips - using expressions of some condensed expressivity. We can't be that verbose

    Serial.print("the air temperature is ");
    Serial.print(airTemp);
    Serial.println(" degrees.");

Why isn't there a sendf in Arduino? We are not printing, we are sending. Two or three thing that properbly got hand in hand.

- easy to understand 1 paramter functions
- nice reference implementation of classes Print,Stream and HardwareSerial
- uses flash in favour of ram - especially when F("the air temperature is ") is used
    
It cost's to use something that is evaluated runtime, ram for buffering and clockcycles for processing. Things have to be quantified and use selective.
    
A full blown sendf would properly implement all %f specifier of printf using varaidic templates of C++11 - I am too lazy to try that.

A quick test and following internet seach reveals that printf and is't cousins, as standard setup in arduino IDE, don't include formating floats.

Instead of envestigating the cost of changing compilig switches, we simple makes some worarounds which price in RAM usage is obvious.

To be able to overload for flashing the format string seemed affordable - implementing a non standard conversion specifier for - let say %S - for doing

    sendf("%S<n",F("I m flashed"));
    
is left to when need occures - the example makes no sense it itself because the string is litteral.