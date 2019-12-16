#include "FileTooSmallException.h"



FileTooSmallException::FileTooSmallException()
{
}

const char * FileTooSmallException::what() const
{
	return "The file with cards doesn't have as many cards!";
}


FileTooSmallException::~FileTooSmallException()
{
}
