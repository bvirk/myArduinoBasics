## About simplest practical setup

There is a reason for every thing - also the non inaugurated style at arduino.cc. It differs from this for obvious purposes.

The art of simplicity is targetted against AVR's with limited capabilities like uno and nano - the art where heap usage can't scale, exceptions and rtti are out of question, and all scalability and lifetime of data is carefull handled.  

## printf

All supplied examples shows sequences as

    float temp = ...
    Serial.print("The temperature is:")
    Serial.println(temp);
    
As an internet search immediately reveals, not everyone loves typing that much. Investigation starts:

What is Serial.print ?

Inspecting Arduino.h (which is always included - look at build????? in temp