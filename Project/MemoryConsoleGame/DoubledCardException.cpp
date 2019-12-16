#include "DoubledCardException.h"



DoubledCardException::DoubledCardException()
{
}

const char * DoubledCardException::what() const
{
	return "Some of the cards in the file appear more than once!";
}


DoubledCardException::~DoubledCardException()
{
}
