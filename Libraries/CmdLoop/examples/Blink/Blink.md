Blink is _the_ first sample to view - the arduino 'hello world'.
Same with this Blink.
The replacement af blocking delays with a, time looking using milles(), loop is an exercise many arduino programmers might have played with. 
We use libraries other people gradious offers - libraries which is using interrupts. Tying libraies together for making a program is often a simple task compared to write those interrupt dependt libraries.

CmdLoop is such a simple, none interrupt using, Arduino OS, consisting of the main part:

- remote command execution over serial
- round-roby, all same priority, timeslice mechnism


