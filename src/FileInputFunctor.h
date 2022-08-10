#include "InputFunctor.h"

#ifndef FILEINPUTFUNCTOR
#define FILEINPUTFUNCTOR

struct FileInputFunctor : public InputFunctor{
	istream& operator()(istream& input, char* buffer, std::streamsize size) override;
};

#endif //FILEINPUTFUNCTOR