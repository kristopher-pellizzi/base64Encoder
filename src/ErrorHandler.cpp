#include "ErrorHandler.h"

void exit_error(const char* msg){
	cerr << endl << ansiCode(ANSI_CODE::ANSI_RED) << "[ERROR] " << msg << ansiCode(ANSI_CODE::ANSI_RESET) << endl;
	exit(EXIT_FAILURE);
}

void recoverable_error(const char* msg){
	cerr << endl << ansiCode(ANSI_CODE::ANSI_BRIGHT_YELLOW) << "[WARNING] " << msg << ansiCode(ANSI_CODE::ANSI_RESET) << endl;
}