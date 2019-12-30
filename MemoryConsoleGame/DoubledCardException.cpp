#include "DoubledCardException.h"



DoubledCardException::DoubledCardException()
{
}

const char * DoubledCardException::what() const
{
	return "For given board size, some of the cards in the file appear more than once!";
}


DoubledCardException::~DoubledCardException()
{
}
