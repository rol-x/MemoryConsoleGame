#pragma once
#include "FileLoadingException.h"

class FileTooSmallException : public FileLoadingException
{
public:
	FileTooSmallException();
	const char * what() const;
	virtual ~FileTooSmallException() noexcept;
};

