A certain standpoint about user interfaces for devices like arduino shall here be preached. Prior in history such things would not have worked without buttons or keyboard as input and some visual output. Today things has a serial connection - wired og air carried. Buttons and screens costs as hardware, design and programming time.


When programming a microprocessor in c/c++, the function is the name of the elementary composed action. Remoted procedure calls is calling such a brick remotely.


Such an interface has the benefit of potentially being a brick in a bigger system, where communication is automated, layered or filtered to other concepts made possible by the more powerfull connected devices.


A simple scheme is make procedure like commands in linux terminal or windows console. Main functions taken array of strings as parameter and returning an exit level. A configuration can make it choiceable to call an autoexec command after reset.


Terminal talking can be done in character or line unit. Because I chose line, and a simple dump terminal is used, a convenient 'repeat last' command (being a single dot) is implemented.


An arduino solves jobs dealing with reading sensors and controlling attached electronics. That involves doing many things at the same time following some time involving logic.


We use libraries which dependts on interrupt. The most simple OS, is to avoid interrupt at the level where we ties things together, and just extend the loop with millis() value dependt branching in code. I made a mechanism with function called slices that have the responsible to 'pass the baton on' for next slice getting thread of execution on next millis() value dependt invocation in main loop. The slice can adjust the delay formed by the value millis() compares to in main loop. Slices is an array of function pointers and sceduling goes in ring when each time calls next() as last statement.


Error conditions can occur and includes, on an Arduino, all from hardware conditions to programming error. No room for c++ exceptions on a 2k bytes ram device and no user to take verbose action when Arduino solves it mechanical job.


I have the idea that an Arduino application shall be reset robust - in other words - a reset must have a predictet place in the big run.
The simplest is a one time denoted error code. It can be registrated because a timestamp has been sendt from terminal and it can not be overwritten before a new timestamp is sendt. It survives reset, as opposed to time readout, with an intact time of the error number that was set. It uses 11 bytes of EEPROM and would, if the numbers of registated error events should be more than one, use 4 bytes more for each error.


Some sort of signaling an error must be performed. The 'blink' led on pin13 is reserved that use. The blink led is given a double information job, by signaling 'all is good' by a slow steady blinking - an indication of that thread of execution travels through those array of function pointers that forms slices.     

