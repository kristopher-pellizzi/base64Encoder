#include "ConverterEncodeInteractiveCommand.h"

void ConverterEncodeInteractiveCommand::operator()(istream& input, ostream& output){
	#ifdef DEBUG
	cout << "Encode_interactive Command" << endl;
	#endif
	encode_interactive(input, output);
}