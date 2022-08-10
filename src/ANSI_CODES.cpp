#include "ANSI_CODES.h"

char* ansiCode(ANSI_CODE code){
	switch(code){
		case ANSI_CODE::ANSI_RESET:
			return strdup("\x1b[0m");

		case ANSI_CODE::ANSI_RED:
			return strdup("\x1b[31m");

		case ANSI_CODE::ANSI_BRIGHT_YELLOW:
			return strdup("\x1b[93m");
	}
} 