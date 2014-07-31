#include "2DLetter.h"

std::string gn::noWhiteSpaceString(std::string s)
{
	if(s == "")
		return "";
	else
	{
		std::string whitespace = " \t";
		int strStart = s.find_first_not_of(whitespace);
		int strEnd = s.find_last_not_of(whitespace);
		int strLength = strEnd - strStart+1;
		s = s.substr(strStart,strLength);
		return s;
	}
}
bool gn::isNumber(const std::string s)
{
	if(s.at(0) == '-')
	{
		const std::string a = s.substr(1,s.npos);
		int i = !a.empty() && std::find_if(a.begin(), 
			a.end(), [](char c) { return !std::isdigit(c); }) == a.end();
		return i*(-1);
	}
	else
	{
		return !s.empty() && std::find_if(s.begin(), 
			s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
	}
}

vector3Df::vector3Df()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}
vector3Df::vector3Df(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

vector2Df::vector2Df()
{
	this->x = 0;
	this->y = 0;
}
vector2Df::vector2Df(float x, float y)
{
	this->x = x;
	this->y = y;
}

quad3D::quad3D()
{
	vertices[0] = 0;
	vertices[1] = 0;
	vertices[2] = 0;
	vertices[3] = 0;
	vertexTexture[0] = 0;
	vertexTexture[1] = 0;
	vertexTexture[2] = 0;
	vertexTexture[3] = 0;

}
quad3D::quad3D(int pos1, int pos2, int pos3, int pos4)
{
	vertices[0] = pos1;
	vertices[1] = pos2;
	vertices[2] = pos3;
	vertices[3] = pos4;
	vertexTexture[0] = 0;
	vertexTexture[1] = 0;
	vertexTexture[2] = 0;
	vertexTexture[3] = 0;
}

triangle3D::triangle3D()
{
	vertices[0] = 0;
	vertices[1] = 0;
	vertices[2] = 0;
	vertexTexture[0] = 0;
	vertexTexture[1] = 0;
	vertexTexture[2] = 0;
}
triangle3D::triangle3D(int pos1, int pos2, int pos3)
{
	vertices[0] = pos1;
	vertices[1] = pos2;
	vertices[2] = pos3;
	vertexTexture[0] = 0;
	vertexTexture[1] = 0;
	vertexTexture[2] = 0;
}

Letter2D::Letter2D(char name)
{
	this->name = name;
	//open appropriate file with data
	std::ifstream inFile(std::string("Letters/" + this->name + ".txt"));
	float tempX, tempY, tempZ;
	int faceFormat = -1;
	std::string temp = "";
	std::stringstream ss;
	letterSize.x = 30.0f; //default width
	letterSize.y = 30.0f;
	textures = false;
	while(inFile){
		std::getline(inFile,temp);
		ss.str("");
		ss.clear();
		ss << temp;
		std::getline(ss,temp,' ');
		if(temp == "v"){
			//vertices
			ss >> tempX >> tempY >> tempZ;
			vertices.push_back(vector3Df(tempX,tempY,tempZ));
		}
		else if(temp == "w"){
			//letter width
			ss >> tempX;
			letterSize.x = tempX;
		}
		else if(temp == "vt"){
			//vertex texture coordinate
			ss >> tempX >> tempY;
			vertexTexture.push_back(vector2Df(tempX,tempY));
			if(!textures)
				textures = true;
		}
		else if(temp == "f"){
			//trangle/quad
			std::string tempA = "",tempB = "",tempC = "",tempD = "";
			int verts[4] = {-1,-1,-1,-1};
			int tex[4] = {-1,-1,-1,-1};
			//read polygon data
			ss >> tempA >> tempB >> tempC >> tempD;
			//if we have vertex texture coordinates, use slash as separator for face indexes
			if(textures){
				verts[0] = std::stoi(tempA.substr(0,tempA.find('/')));
				gn::ston(gn::noWhiteSpaceString(tempA.substr(tempA.find('/')+1,tempA.size())),tex[0]);

				verts[1] = std::stoi(tempB.substr(0,tempB.find('/')));
				gn::ston(gn::noWhiteSpaceString(tempB.substr(tempB.find('/')+1,tempB.size())),tex[1]);
								
				verts[2] = std::stoi(tempC.substr(0,tempC.find('/')));
				gn::ston(gn::noWhiteSpaceString(tempC.substr(tempC.find('/')+1,tempC.size())),tex[2]);
				if(tempD != ""){
					verts[3] = std::stoi(tempD.substr(0,tempD.find('/')));
					gn::ston(gn::noWhiteSpaceString(tempD.substr(tempD.find('/')+1,tempD.size())),tex[3]);
				}
			}
			else
			{
				//if we don't have texture coords, read all vertices
				verts[0] = std::stoi(tempA);
				verts[1] = std::stoi(tempB);
				verts[2] = std::stoi(tempC);
				if(tempD != "")
					verts[3] = std::stoi(tempD);
			}
			//if we can't read 4th variable, we are a triangle
			if(tempD == ""){
				triangle3D newTri(verts[0]-1,verts[1]-1,verts[2]-1); //-1 for array compatibility
				newTri.vertexTexture[0] = tex[0]-1;
				newTri.vertexTexture[1] = tex[1]-1;
				newTri.vertexTexture[2] = tex[2]-1;
				tris.push_back(newTri);
			}
			else
			{
				//we must be a quad otherwise
				quad3D newQuad(verts[0]-1,verts[1]-1,verts[2]-1,verts[3]-1); //-1 for array compatibility
				newQuad.vertexTexture[0] = tex[0]-1;
				newQuad.vertexTexture[1] = tex[1]-1;
				newQuad.vertexTexture[2] = tex[2]-1;
				newQuad.vertexTexture[3] = tex[3]-1;
				quads.push_back(newQuad);
			}
		}
	}
}
void Letter2D::draw(vector3Df offset, letterDrawMode drawMode)
{
	GLfloat one[] = {1,1,1};
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, one);
	float r = 0,g = 0,b = 0;
	//if draw mode is set to whole letter in random color, generate a random color now
	if(drawMode == letterDrawMode::RAINBOWMODE){
		r = (rand()%256),g = (rand()%256),b = (rand()%256);
		glColor3f((float)r/256.0f,(float)g/256.0f,(float)b/256.0f);
	}
	//draw all quads found in this letter
	for(int i=0;i<quads.size();i++){
		glBegin(GL_QUADS);
		for(int j=0;j<4;j++){
			//if the mode is set to all vertices in random color, generate a random color now
			if(drawMode == letterDrawMode::LSDMODE){
				r = (rand()%256),g = (rand()%256),b = (rand()%256);
				glColor3f((float)r/256.0f,(float)g/256.0f,(float)b/256.0f);
			}
			//draw the quad
			glVertex3f(vertices[quads[i].vertices[j]].x+offset.x,
				vertices[quads[i].vertices[j]].y+offset.y,
				vertices[quads[i].vertices[j]].z+offset.z);
			if(textures)
				glTexCoord2d(vertexTexture[quads[i].vertexTexture[j]].x,vertexTexture[quads[i].vertexTexture[j]].y);
		}
		glEnd();
	}
	//repeat process for all triangles
	for(int i=0;i<tris.size();i++){
		glBegin(GL_TRIANGLES);
		for(int j=0;j<3;j++){
			//if the mode is set to all vertices in random color, generate a random color now
			if(drawMode == letterDrawMode::LSDMODE){
				r = (rand()%256),g = (rand()%256),b = (rand()%256);
				glColor3f((float)r/256.0f,(float)g/256.0f,(float)b/256.0f);
			}
			//draw the triangle
			glVertex3f(vertices[tris[i].vertices[j]].x+offset.x,
				vertices[tris[i].vertices[j]].y+offset.y,
				vertices[tris[i].vertices[j]].z+offset.z);
			if(textures)
				glTexCoord2d(vertexTexture[tris[i].vertexTexture[j]].x,vertexTexture[tris[i].vertexTexture[j]].y);
		}
		glEnd();
	}
}