#include "FileDoesntExistException.h"



FileDoesntExistException::FileDoesntExistException()
{
}

const char * FileDoesntExistException::what() const
{
	return "The file doesn't exist or cannot be opened";
}


FileDoesntExistException::~FileDoesntExistException()
{
}
