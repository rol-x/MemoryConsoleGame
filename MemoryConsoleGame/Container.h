#pragma once
#include <iostream>
#include <string>

using namespace std;

class Container
{
	int _hSize = 15;
public:
	string Display(string content);
	Container();
	virtual ~Container() = 0;
};

