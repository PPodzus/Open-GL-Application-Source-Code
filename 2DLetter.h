#pragma once
#ifndef LETTER3D_H_
#define LETTER3D_H_

#include <Windows.h>
#include <gl\GL.h>
#include <gl\glut.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>
#include <time.h>

namespace gn
{
	std::string noWhiteSpaceString(std::string s);
	bool isNumber(const std::string s);
	//string to numeric type
	template <typename T> bool ston(std::string s, T &number)
	{
		//handling negative numbers
		if(s.at(0) == '-')
		{
			if(isNumber(s.substr(1,s.length()-1)))
			{
				number = std::stoi(s);
				return true;
			}
		}
		if(isNumber(s))
		{
			number = std::stoi(s);
			return true;
		}
		return false;
	}
}
//container struct with xyz float coordinates
class vector3Df
{
public:
	float x,y,z;
	vector3Df();
	vector3Df(float x, float y, float z);
};
//container struct with xyz float coordinates
class vector2Df
{
public:
	float x,y;
	vector2Df();
	vector2Df(float x, float y);
};
//container for INDEXES of positions of vertices, normals and textutres in a quad
class quad3D
{
public:
	int vertices[4];
	int vertexTexture[4];
	quad3D();
	quad3D(int pos1, int pos2, int pos3, int pos4);
};
//container for INDEXES of positions of vertices, normals and textutres in a triangle
class triangle3D
{
public:
	int vertices[3];
	int vertexTexture[3];
	triangle3D();
	triangle3D(int pos1, int pos2, int pos3);
};
class Letter2D
{
	vector2Df letterSize;
	bool textures;
	std::string name;
	std::vector<vector3Df> vertices;
	std::vector<vector2Df> vertexTexture;

	std::vector<quad3D> quads;
	std::vector<triangle3D> tris;
public:
	enum letterDrawMode{LSDMODE,RAINBOWMODE,NONE};
	vector2Df getLetterSize(){return letterSize;}
	Letter2D(char name);
	void draw(vector3Df offset = vector3Df(), letterDrawMode drawMode = letterDrawMode::NONE);
};
#endif // LETTER3D_H