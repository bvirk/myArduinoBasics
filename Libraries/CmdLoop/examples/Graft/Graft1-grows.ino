//! The place to grow what becomes libraries

/*
struct CmdFs {
#define COMMANDS_COUNT 2
	static void kurt() { sendf("kurt\n"); }
	static void egon() { sendf("egon\n"); }
	struct CmdArr {
		PGM_P p;
		void (*f)(void);
		CmdArr() {}
		void init(void (*g)(void), const __FlashStringHelper *ffmt) {
			p = (reinterpret_cast<PGM_P>(ffmt));
			f=g;
		} 
	} cmds[COMMANDS_COUNT];
	CmdFs() {
		int i=0;							
								// kurt korer starkt
		cmds[i++].init( kurt, F("kurt" // args 
		
		));cmds[i++].init( egon,F("egon" // args
		
		));
	}
};

*/
