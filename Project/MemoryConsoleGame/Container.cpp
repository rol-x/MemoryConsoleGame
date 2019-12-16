#include "Container.h"

string Container::Display(string content)
{
	string output = "";
	int indentBefore = (_hSize - content.length()) / 2;
	for (int i = 0; i < indentBefore; i++)
		output += " ";
	output += content;
	int indentAfter = _hSize - content.length() - indentBefore;
	for (int i = 0; i < indentAfter; i++)
		output += " ";
	return output;
}

Container::Container()
{}

Container::~Container()
{}
