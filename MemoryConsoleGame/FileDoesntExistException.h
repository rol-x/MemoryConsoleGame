#pragma once
#include "FileLoadingException.h"

class FileDoesntExistException : public FileLoadingException
{
public:
	FileDoesntExistException();
	const char * what() const;
	virtual ~FileDoesntExistException() noexcept;
};

