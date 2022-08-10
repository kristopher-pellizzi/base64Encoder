#include "InputFunctor.h"

#ifndef INTERACTIVEINPUTFUNCTOR
#define INTERACTIVEINPUTFUNCTOR

struct InteractiveInputFunctor : public InputFunctor{
	istream& operator()(istream& input, char* buffer, std::streamsize size) override;
};

#endif //INTERACTIVEINPUTFUNCTOR