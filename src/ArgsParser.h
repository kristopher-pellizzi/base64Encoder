#include <string>
#include <iostream>
#include <cstdlib>
#include <deque>
#include <strstream>
#include <fstream>
#include <map>

#include "Argument.h"

#define P(k, v) std::pair<string, Argument>(k, v)

using std::string;
using std::cerr;
using std::endl;
using std::strstream;
using std::ifstream;
using std::ofstream;
using std::map;
using std::deque;
using std::cout;

class ArgsParser{
	private:
		int _argc;
		char** _argv;
		int _pos;

		map<string, Argument, Argument::ArgumentCmp> _args;

		deque<string> _errorList;

		char** parseArg(char** arg);
		char** parseShortOpt(char** arg);
		char** parseLongOpt(char** arg);
		char** parsePos(char** arg);
		char* extractRequiredVal(char* arg);

		void appendError(strstream& err);
		void INVALID_ARGUMENT_ERROR(char* arg);
		void INVALID_SYNTAX_ERROR(char* arg, strstream& msg);
		void MISSING_REQUIRED_VALUE_ERROR(char* arg);

	public:
		ArgsParser(int argc, char* argv[]);

		void parseArgs();
		const Argument& getArgument(const char* argName);
		const Argument& getPositionalArgument(int i);
};