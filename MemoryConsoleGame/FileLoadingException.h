#pragma once
#include <exception>

class FileLoadingException :
	public std::exception
{
public:
	FileLoadingException();
	const char * what() const;
	virtual ~FileLoadingException() noexcept;
};

