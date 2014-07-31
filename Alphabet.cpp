#include "Alphabet.h"

Alphabet3D::Alphabet3D()
{
	std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
	int start = GetTickCount();
	for(int i=0;i<alphabet.size();i++){
		letters.push_back(Letter2D(alphabet.at(i)));
	}
	std::cout << "alphabet loaded in: " << GetTickCount() - start << "ms" << std::endl;
}
void Alphabet3D::drawLetter(char letter, vector3Df offset, Letter2D::letterDrawMode drawMode)
{
	//draw one of the letters
	switch(letter)
	{
	case 'a': case 'A': letters[0].draw(offset, drawMode); break;
	case 'b': case 'B': letters[1].draw(offset, drawMode); break;
	case 'c': case 'C': letters[2].draw(offset, drawMode); break;
	case 'd': case 'D': letters[3].draw(offset, drawMode); break;
	case 'e': case 'E': letters[4].draw(offset, drawMode); break;
	case 'f': case 'F': letters[5].draw(offset, drawMode); break;
	case 'g': case 'G': letters[6].draw(offset, drawMode); break;
	case 'h': case 'H': letters[7].draw(offset, drawMode); break;
	case 'i': case 'I': letters[8].draw(offset, drawMode); break;
	case 'j': case 'J': letters[9].draw(offset, drawMode); break;
	case 'k': case 'K': letters[10].draw(offset, drawMode); break;
	case 'l': case 'L': letters[11].draw(offset, drawMode); break;
	case 'm': case 'M': letters[12].draw(offset, drawMode); break;
	case 'n': case 'N': letters[13].draw(offset, drawMode); break;
	case 'o': case 'O': letters[14].draw(offset, drawMode); break;
	case 'p': case 'P': letters[15].draw(offset, drawMode); break;
	case 'q': case 'Q': letters[16].draw(offset, drawMode); break;
	case 'r': case 'R': letters[17].draw(offset, drawMode); break;
	case 's': case 'S': letters[18].draw(offset, drawMode); break;
	case 't': case 'T': letters[19].draw(offset, drawMode); break;
	case 'u': case 'U': letters[20].draw(offset, drawMode); break;
	case 'v': case 'V': letters[21].draw(offset, drawMode); break;
	case 'w': case 'W': letters[22].draw(offset, drawMode); break;
	case 'x': case 'X': letters[23].draw(offset, drawMode); break;
	case 'y': case 'Y': letters[24].draw(offset, drawMode); break;
	case 'z': case 'Z': letters[25].draw(offset, drawMode); break;
	}
}
vector2Df Alphabet3D::getLetterSize(char letter)
{
	//return the default size of the letter (all default to height 30, with different widths)
	switch(letter)
	{
	case 'a': case 'A': return letters[0].getLetterSize(); break;
	case 'b': case 'B': return letters[1].getLetterSize(); break;
	case 'c': case 'C': return letters[2].getLetterSize(); break;
	case 'd': case 'D': return letters[3].getLetterSize(); break;
	case 'e': case 'E': return letters[4].getLetterSize(); break;
	case 'f': case 'F': return letters[5].getLetterSize(); break;
	case 'g': case 'G': return letters[6].getLetterSize(); break;
	case 'h': case 'H': return letters[7].getLetterSize(); break;
	case 'i': case 'I': return letters[8].getLetterSize(); break;
	case 'j': case 'J': return letters[9].getLetterSize(); break;
	case 'k': case 'K': return letters[10].getLetterSize(); break;
	case 'l': case 'L': return letters[11].getLetterSize(); break;
	case 'm': case 'M': return letters[12].getLetterSize(); break;
	case 'n': case 'N': return letters[13].getLetterSize(); break;
	case 'o': case 'O': return letters[14].getLetterSize(); break;
	case 'p': case 'P': return letters[15].getLetterSize(); break;
	case 'q': case 'Q': return letters[16].getLetterSize(); break;
	case 'r': case 'R': return letters[17].getLetterSize(); break;
	case 's': case 'S': return letters[18].getLetterSize(); break;
	case 't': case 'T': return letters[19].getLetterSize(); break;
	case 'u': case 'U': return letters[20].getLetterSize(); break;
	case 'v': case 'V': return letters[21].getLetterSize(); break;
	case 'w': case 'W': return letters[22].getLetterSize(); break;
	case 'x': case 'X': return letters[23].getLetterSize(); break;
	case 'y': case 'Y': return letters[24].getLetterSize(); break;
	case 'z': case 'Z': return letters[25].getLetterSize(); break;
	default: return vector2Df(30,30); break;
	}
}
void Alphabet3D::drawWord(std::string text, vector3Df offset, Letter2D::letterDrawMode drawMode)
{
	bool red = true;
	//use the offset passed to draw all letters
	vector3Df stringOffset = offset;
	for(int i=0;i<text.size();i++){
		//draw a letter using the current offset and draw mode passed
		drawLetter(text[i],vector3Df(stringOffset.x,stringOffset.y,stringOffset.z),drawMode);
		//update offset after each letter
		stringOffset.x += getLetterSize(text[i]).x;
	}
}