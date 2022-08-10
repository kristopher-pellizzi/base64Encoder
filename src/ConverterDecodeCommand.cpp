#include "ConverterDecodeCommand.h"

void ConverterDecodeCommand::operator()(istream& input, ostream& output){
	#ifdef DEBUG
	cout << "Decode Command" << endl;
	#endif
	decode(input, output);
}