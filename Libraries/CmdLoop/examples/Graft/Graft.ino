//! Graft - the CmdLoop using Graftplatform

/** The place for
  growing the libraries used in, but not exclusive for, CmdLoop.
  growing CmdLoop itself

ino files

	Graft.ino
		Documentation about files
	Graft1-grows.ino
		Where classes start their life before going in libraries
	Graft2-slices.ino
		The functionality of business logic about electronic input output besides serial communication
	Graft3-cmdFuncs-Basic.ino
		Some basic commands that, in their simplicity, show what CmdLoop commands is. 
	Graft4-cmdFuncs-New.ino
		The commands used in som CmdLoop application
	GraftPlatform.ino
		setup and global object behind the scene.

*/

#include <CmdLoop.h>
#include <Sendf.h>
#include <EEPROM.h>
#include "Graft.h"
#include "TimedErrorLog.h"
#include <avr/pgmspace.h>
#include "Templates.h"

