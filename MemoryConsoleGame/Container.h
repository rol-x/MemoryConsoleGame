#pragma once
#include <iostream>
#include <string>

using namespace std;

class Container
{
	int _hSize = 12;
public:
	string Display(string content);
	Container();
	virtual ~Container() = 0;
};

