#include "Argument.h"

Argument::Argument() : _name(string()), _val(strdup("")), _hasVal(false), _isValid(false)
	{

	}


Argument::Argument(string name, char* val) : _name(name), _val(val), _hasVal(true), _isValid(true)
	{

	}

Argument::Argument(string name) : _name(name), _val(strdup("")), _hasVal(false), _isValid(true)
	{

	}

const string& Argument::getName() const{
	return _name;
}

char* Argument::getVal() const{
	return _val;
}


bool Argument::hasVal() const{
	return _hasVal;
}


bool Argument::isValid() const{
	return _isValid;
}


const Argument& Argument::getInvalidArg(){
	static const Argument INVALID_ARG;

	return INVALID_ARG;
}


bool Argument::ArgumentCmp::operator()(const Argument& lhs, const Argument& rhs) const{
	return lhs._name < rhs._name;
}