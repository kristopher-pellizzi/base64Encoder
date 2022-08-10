#include "InteractiveInputFunctor.h"

istream& InteractiveInputFunctor::operator()(istream& input, char* buffer, std::streamsize size){
	return input.get(buffer, size);
}