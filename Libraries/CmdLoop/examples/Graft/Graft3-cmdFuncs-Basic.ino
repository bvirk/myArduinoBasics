//! Function description in CommandFuncBox::CommandFuncBox()

namespace cmdFuncs {
	
	int8_t  ver(int argc, char* argv[]) {
		sendf(CmdLoop::version());
		return 0;
	}
	
	int8_t printArgs(int argc, char* argv[]) {
		for (uint8_t i = 0; i < argc; i++)
			sendf(F("%d: >%s<\n"),i,argv[i]);
		return 0;
	}

	int8_t blink(int argc, char* argv[]) {
		if (argc == 3 ) {
			slices::onTime = atoi(argv[1]);
			slices::offTime = atoi(argv[2]);
			return 0;
		}
		return -1;
	}

};
