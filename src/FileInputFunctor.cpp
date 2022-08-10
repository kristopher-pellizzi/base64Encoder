#include "FileInputFunctor.h"

istream& FileInputFunctor::operator()(istream& input, char* buffer, std::streamsize size){
	return input.read(buffer, size);
}