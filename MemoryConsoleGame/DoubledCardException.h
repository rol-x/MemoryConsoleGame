#pragma once
#include "FileLoadingException.h"

class DoubledCardException :
	public FileLoadingException
{
public:
	DoubledCardException();
	const char * what() const;
	virtual ~DoubledCardException() noexcept;
};

