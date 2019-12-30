#include "TextPosition.h"

void TextPosition::CenterOutput(string output)
{
	int margin = (Console().GetConsoleWidth() - output.length()) / 2;
	for (int i = 0; i < margin; i++)
		cout << " ";
	cout << output;
}

void TextPosition::RightAlignOutput(string output)
{
	int margin = Console().GetConsoleWidth() - output.length();
	for (int i = 0; i < margin; i++)
		cout << " ";
	cout << output;
}

TextPosition::TextPosition()
{
}


TextPosition::~TextPosition()
{
}
