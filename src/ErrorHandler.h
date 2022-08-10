#include <iostream>
#include <cstdlib>

#include "ANSI_CODES.h"

#ifndef ERRORHANDLER
#define ERRORHANDLER

using std::cerr;
using std::endl;

void exit_error(const char* msg);

void recoverable_error(const char* msg);

#endif //ERRORHANDLER