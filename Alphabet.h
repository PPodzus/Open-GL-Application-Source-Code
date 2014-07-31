#pragma once
#ifndef ALPHABET_H_
#define ALPHABET_H_

#include "2DLetter.h"

class Alphabet3D
{
	std::vector<Letter2D> letters;
public:
	Alphabet3D();
	vector2Df getLetterSize(char letter);
	void drawLetter(char letter, vector3Df offset = vector3Df(),Letter2D::letterDrawMode = Letter2D::letterDrawMode::NONE);
	void drawWord(std::string text, vector3Df offset = vector3Df(), Letter2D::letterDrawMode drawMode = Letter2D::letterDrawMode::NONE);
};
#endif //ALPHABET_H_