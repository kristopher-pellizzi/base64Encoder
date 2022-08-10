#include "ArgsParser.h"

ArgsParser::ArgsParser(int argc, char** argv) : 
			_argc(argc), 
			_argv(argv), 
			_pos(0)
	{

	}


void ArgsParser::appendError(strstream& err){
	_errorList.push_back(err.str());
}


void ArgsParser::INVALID_ARGUMENT_ERROR(char* arg){
	strstream err;
	err << "Argument \"" << arg << "\" not recognized" << endl;
	appendError(err);
}


void ArgsParser::INVALID_SYNTAX_ERROR(char* arg, strstream& msg){
	strstream err;
	err 
		<< "Invalid syntax for argument \"" << arg << "\"." << endl
		<< msg.rdbuf();
	appendError(err);
}


void ArgsParser::MISSING_REQUIRED_VALUE_ERROR(char* arg){
	strstream err;
	err
		<< "Argument \"" << arg << "\" requires a value" << endl;
	appendError(err);
}


void ArgsParser::parseArgs(){
	char** curr = &_argv[1];

	while(*curr != NULL){
		curr = parseArg(curr);
	}

	if(_errorList.size() > 0){
		for(auto iter = _errorList.begin(); iter != _errorList.end(); ++iter){
			cerr << *iter;
		}

		exit(EXIT_FAILURE);
	}
}

char** ArgsParser::parseArg(char** arg){
	// Optional args
	if(**arg == '-'){
		if((*arg)[1] == '-')
			return parseLongOpt(arg);
		
		return parseShortOpt(arg);
	}
	// Positional args
	return parsePos(arg);
}


char* ArgsParser::extractRequiredVal(char* arg){
	if(arg == NULL){
		MISSING_REQUIRED_VALUE_ERROR(arg);
	}

	return arg;
}


char** ArgsParser::parseLongOpt(char** arg){
	string argName(*arg);
	argName = argName.substr(2);

	#ifdef DEBUG
	cout << "Parsing long optional argument " << argName << ": ";
	#endif

	if(argName == "output"){
		char* val = extractRequiredVal(*(arg + 1));
		#ifdef DEBUG
		cout << val << endl;
		#endif
		_args.insert(P(argName, Argument(argName, val)));

		return arg + 2;
	}
	
	if(argName == "input"){
		char* val = extractRequiredVal(*(arg + 1));
		#ifdef DEBUG
		cout << val << endl;
		#endif
		_args.insert(P(argName, Argument(argName, val)));

		return arg + 2;
	}

	if(argName == "interactive"){
		#ifdef DEBUG
		cout << "<NO_VALUE>" << endl;
		#endif
		_args.insert(P(argName, Argument(argName)));

		return arg + 1;
	}

	if(argName == "padding"){
		char* val = extractRequiredVal(*(arg + 1));
		#ifdef DEBUG
		cout << val << endl;
		#endif
		_args.insert(P(argName, Argument(argName, val)));

		return arg + 2;
	}

	if(argName == "no-padding"){
		#ifdef DEBUG
		cout << "<NO_VALUE>" << endl;
		#endif
		_args.insert(P(argName, Argument(argName)));

		return arg + 1;
	}

	if(argName == "decode"){
		#ifdef DEBUG
		cout << "<NO_VALUE>" << endl;
		#endif
		_args.insert(P(argName, Argument(argName)));

		return arg + 1;
	}

	if(argName == "no-delimiter"){
		#ifdef DEBUG
		cout << "<NO_VALUE>" << endl;
		#endif
		_args.insert(P(argName, Argument(argName)));

		return arg + 1;
	}
	
	INVALID_ARGUMENT_ERROR(*arg);
	return arg + 1;
}


char** ArgsParser::parseShortOpt(char** arg){
	char name = (*arg)[1];

	#ifdef DEBUG
	cout << "Parsing short optional argument " << name << ": ";
	#endif

	if((*arg)[2] != '\0'){
		strstream err;
		err 
			<< "Short optional arguments must have a length of 1 character (hyphen excluded)." << endl
			<< "Example: \"-f\"" << endl;
		INVALID_SYNTAX_ERROR(*arg, err);
	}

	switch(name){
		case 'i':
			{
				string argName("input");
				char* val = extractRequiredVal(*(arg + 1));
				#ifdef DEBUG
				cout << val << endl;
				#endif
				_args.insert(P(argName, Argument(argName, val)));

				return arg + 2;
			}

		case 'o':
			{
				string argName("output");
				char* val = extractRequiredVal(*(arg + 1));
				#ifdef DEBUG
				cout << val << endl;
				#endif
				_args.insert(P(argName, Argument(argName, val)));

				return arg + 2;
			}

		case 't':
			{
				string argName("interactive");
				#ifdef DEBUG
				cout << "<NO_VALUE>" << endl;
				#endif
				_args.insert(P(argName, Argument(argName)));

				return arg + 1;
			}

		case 'p':
			{
				string argName("padding");
				char* val = extractRequiredVal(*(arg + 1));
				#ifdef DEBUG
				cout << val << endl;
				#endif
				_args.insert(P(argName, Argument(argName, val)));

				return arg + 2;
			}

		case 'd':
			{
				string argName("decode");
				#ifdef DEBUG
				cout << "<NO_VALUE>" << endl;
				#endif
				_args.insert(P(argName, Argument(argName)));

				return arg + 1;
			}

		default:
			INVALID_ARGUMENT_ERROR(*arg);
			return arg + 1;
	}
}


char** ArgsParser::parsePos(char** arg){
	char* val = *arg;
	strstream nameStream;
	nameStream << "pos" << ++_pos;
	string name;
	nameStream >> name;
	#ifdef DEBUG
	cout << "Parsing positional argument " << _pos << ": " << val << endl;
	#endif
	_args.insert(P(name, Argument(name, val)));

	return arg + 1;
}


const Argument& ArgsParser::getArgument(const char* name){
	auto argIter = _args.find(string(name));

	const Argument& ret = argIter != _args.end() ? argIter->second : Argument::getInvalidArg();

	#ifdef DEBUG
	cout << "Looking for " << name << endl;
	cout << "Returning " << (!ret.isValid() ? "invalid argument" : ret.getName()) << endl;
	#endif

	return ret;
}


const Argument& ArgsParser::getPositionalArgument(int i){
	strstream nameStream;
	nameStream << "pos" << i;
	string name;
	nameStream >> name;
	auto argIter = _args.find(name);

	const Argument& ret = argIter != _args.end() ? argIter->second : Argument::getInvalidArg();

	return ret;
}



