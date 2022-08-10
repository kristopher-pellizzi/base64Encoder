#include <cstring>

#ifndef ANSICODE
#define ANSICODE

enum struct ANSI_CODE{
	ANSI_RESET,
	ANSI_RED,
	ANSI_BRIGHT_YELLOW
};


char* ansiCode(ANSI_CODE code);

#endif //ANSICODE