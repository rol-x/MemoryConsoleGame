#pragma once
#include "Console.h"
#include <string>

using namespace std;

class TextPosition
{
public:
	static void CenterOutput(string output);
	static void RightAlignOutput(string output);
	TextPosition();
	~TextPosition();
};

