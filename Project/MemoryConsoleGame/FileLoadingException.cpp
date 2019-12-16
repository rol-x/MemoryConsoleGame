#include "FileLoadingException.h"



FileLoadingException::FileLoadingException()
{
}

const char * FileLoadingException::what() const
{
	return "Due to errors in cards file, the game can't start.";
}


FileLoadingException::~FileLoadingException()
{
}
