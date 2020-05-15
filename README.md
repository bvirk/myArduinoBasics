### Inital Arduino development steps
The _why_ about subjects, that is felt needed to give the energi and focus of identity, is described in whyXXX.md files. 

This README is a sequence of _what_.


### Installation

1.8.9 on windows xp. Having had an earlier version, the Arduino IDE zip was unpacked and registry values checked.

### Setup
- IDE preferences
    - sketchbook folder
    - +verbose output
    - +external editor
    - -check for update (no  internet)
    
- Links in root of Sketchbook folder
    - inlude files ( traced by Arduino.h )
        - quote_inlude
        - gcc_include
        - avr_include
    - arduino.exe
    - hyperterminal
        - emulering
            - tty
        - ascii transmit
            - send newline
            - local echo
        - ascii recieve
            - add newline
    - preferences
        - console.lines=20


### Reading include files in Jedit Editor with plugin 'Error List'

Macro cyberkis, with marked word, calls:

    void searchDirectories(String word, boolean useRegex, String [] dirs) {
        for (String dir : dirs) {				
            SearchAndReplace.setSearchString(word);
            SearchAndReplace.setAutoWrapAround(false);
            SearchAndReplace.setReverseSearch(false);
            SearchAndReplace.setWholeWord(false);
            SearchAndReplace.setIgnoreCase(false);
            SearchAndReplace.setRegexp(useRegex);
            SearchAndReplace.setSearchFileSet(new DirectoryListSet(dir,"*.h",true));
            SearchAndReplace.hyperSearch(view,false);
        }
    }

when invoked with marked string of characters by:
    ...
    case "find in includes" :
	case "regex find in includes" :
	    boolean useRegex = choice.equals("regex find in includes");
        searchDirectories (kiss, useRegex, new String[] {"C:/Programmer/arduino-1.8.9/hardware" });


### Libraries

- Sendf
- CmdLoop
- Utils
- Templates
- TimedErrorLog


### Links

- [every mans doc](https://www.arduino.cc/reference/en/)
- [avr-libc](https://www.nongnu.org/avr-libc/user-manual/modules.html)
- [Question about memory allocation analysis](https://arduino.stackexchange.com/questions/52921/question-about-memory-allocation-analysis?rq=1)