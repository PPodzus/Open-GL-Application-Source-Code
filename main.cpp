#include "2DLetter.h"
#include "Alphabet.h"

const std::string myID = "PAWELPODZUS"; //upper A-Z only!
std::string randomString = "";
vector3Df myIDRotation = vector3Df(0.0f,0.0f,0.0f), myIDRotationRates = vector3Df(0.25f,0.25f,0.25f);
vector3Df myIDposition = vector3Df(-30.0f,-15.0f,-100.0f), myIDpositionRates = vector3Df(1,1,1); //X needs chance if myID length changes
std::string pieces[6] = {"[1] LSD Mode (Warning, flashing lights)","[2] Rainbow Mode","[R] Randomizing",
								"Rotate axis x: [A],[D] Rotate axis y: [W],[S] Rotate axis z: [Q],[E] Reset: [F]",
								"Move in axis x:[J],[L] Move in axis y:[I],[K] Move in axis z:[U].[O]",
								"Press [0] to exit"};
int randomState = 0;
int lastTick = GetTickCount();
bool randomizing = true;
Letter2D::letterDrawMode drawMode = Letter2D::letterDrawMode::NONE;
int drawModeTime = 0;
bool* keyStates = new bool[256];
Alphabet3D alphabet;


void keyPressed(unsigned char key, int x, int y)
{
	keyStates[key] = true;
}
void keyReleased(unsigned char key, int x, int y)
{
	keyStates[key] = false;
}
void specialKeyPressed(int key, int x, int y) {
  keyStates[key] = true;
}
void specialKeyReleased(int key, int x, int y) {
 keyStates[key] = false;
}
void keyboardOperations()
{
	if(keyStates['1'] && ((GetTickCount() -	drawModeTime) > 200)){
		if(drawMode == Letter2D::letterDrawMode::LSDMODE)
			drawMode = Letter2D::letterDrawMode::NONE;
		else
			drawMode = Letter2D::letterDrawMode::LSDMODE;
		drawModeTime = GetTickCount();
		std::cout << "LSDMODE" << std::endl;
	}
	if(keyStates['2'] && ((GetTickCount() - drawModeTime) > 200)){
		if(drawMode == Letter2D::letterDrawMode::RAINBOWMODE)
			drawMode = Letter2D::letterDrawMode::NONE;
		else
			drawMode = Letter2D::letterDrawMode::RAINBOWMODE;
		drawModeTime = GetTickCount();
		std::cout << "RAINBOWMODE" << std::endl;
	}
	if(keyStates['r'] && !randomizing){
		randomizing = true;
		randomState = 0;
		randomString = "";
		for(int i=0;i<myID.size();i++)
		{
			int random = 0;
			while(random < 65)
				random = rand()%91;
			randomString += (char)random;
		}
	}
	if(keyStates['j'])
		myIDposition.x -= myIDpositionRates.x;
	if(keyStates['l'])
		myIDposition.x += myIDpositionRates.x;
	if(keyStates['k'])
		myIDposition.y -= myIDpositionRates.y;
	if(keyStates['i'])
		myIDposition.y += myIDpositionRates.y;
	if(keyStates['u'])
		myIDposition.z += myIDpositionRates.z;
	if(keyStates['o'])
		myIDposition.z -= myIDpositionRates.z;

	if(keyStates['s'])
		myIDRotation.x += myIDRotationRates.x;
	if(keyStates['w'])
		myIDRotation.x -= myIDRotationRates.x;
	if(keyStates['d'])
		myIDRotation.y += myIDRotationRates.y;
	if(keyStates['a'])
		myIDRotation.y -= myIDRotationRates.y;
	if(keyStates['q'])
		myIDRotation.z += myIDRotationRates.z;
	if(keyStates['e'])
		myIDRotation.z -= myIDRotationRates.z;
	if(keyStates['f']){
		myIDRotation = vector3Df(0,0,0);
		myIDposition = vector3Df(25.0f,-15.0f,-100.0f);
	}
	if(keyStates['0'])
		exit(0);
}

void drawID(bool &randomize)
{
	//calculating time since last frame (including cycle left-over miliseconds)
	int index = 0, cycles = 0;
	int currentTick = GetTickCount();
	int frameTime = currentTick - lastTick;
	cycles = frameTime / 100;
	//if the randomizing has been turned on
	if(randomize){
		for(int c=0;c<cycles;c++){
			//for each cycle, determine the amount of ID letters before drawing random ones.
			index = randomState /10;
			randomString = "";
			if(randomState >= myID.size()*10){
				randomize = false;
				goto fullWord;
			}
			/*if(randomState >=70){
				//if we reached last stage of the randomization, reset all data
				randomize = false;
				randomString = "";
				goto fullWord;
			}
			else if(randomState >=60){
				index = 7;
				randomString = "";
			}
			else if(randomState >=50){
				index = 6;
				randomString = "";
			}
			else if(randomState >=40){
				index = 5;
				randomString = "";
			}
			else if(randomState >=30){
				index = 4;
				randomString = "";
			}
			else if(randomState >=20){
				index = 3;
				randomString = "";
			}
			else if(randomState >=10){
				index = 2;
				randomString = "";
			}
			else if(randomState >=0){
				index = 1;
				randomString = "";
			}*/
			//pass letters from ID to an empty string
			for(int i=0;i<index;i++){
				randomString += myID[i];
			}
			randomState++;
			int tempIndex = index;
			//pass random uppercase letter for all remaining ID letters
			for(;tempIndex<myID.size();tempIndex++)
			{
				int random = 0;
				while(random < 65)
					random = rand()%91;
				randomString += (char)random;
			}
		}
		//reset color to white and draw the random combination onto the screen
		glColor3f(1,1,1);
		alphabet.drawWord(randomString,vector3Df(-125,0,0),drawMode);
	}
	else{
fullWord:
		//reset color to white and draw the ID onto the screen
		glColor3f(1,1,1);
		alphabet.drawWord(myID,vector3Df(-125,0,0),drawMode);
	}
	int leftOver = frameTime - (cycles * 100);
	lastTick = currentTick - (leftOver);
}
void drawHUD()
{
	//if the current drawing mode is all-vertices random, make this string green
	if(drawMode == Letter2D::letterDrawMode::LSDMODE)
		glColor3f(0,1,0);
	else
		//otherwise make it red
		glColor3f(1,0,0);
	//position the string on the screen
	glRasterPos2f(-200,100);
	int len = pieces[0].length();
	//draw string using the Time News Roman 24 font
	for (int i = 0; i < len; i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, pieces[0][i]);
	}
	//if the current drawing mode is random color per letter, make this string green
	if(drawMode == Letter2D::letterDrawMode::RAINBOWMODE)
		glColor3f(0,1,0);
	else
		//otherwise make it red
		glColor3f(1,0,0);
	//position the string on the screen
	glRasterPos2f(-200,90);
	len = pieces[1].length();
	//draw string using the Time News Roman 24 font
	for (int i = 0; i < len; i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, pieces[1][i]);
	}
	if(randomizing)
		glColor3f(0,1,0);
	else
		glColor3f(1,0,0);
	//position the string on the screen
	glRasterPos2f(-200,80);
	len = pieces[2].length();
	//draw string using the Time News Roman 24 font
	for (int i = 0; i < len; i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, pieces[2][i]);
	}

	//For displaying controls, keep the strings white
	glColor3f(1,1,1);
	glRasterPos2f(-200,-80);
	//position the string on the screen
	len = pieces[3].length();
	//draw string using the Time News Roman 24 font
	for (int i = 0; i < len; i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, pieces[3][i]);
	}
	//position the string on the screen
	glRasterPos2f(-200,-69);
	len = pieces[4].length();
	//draw string using the Time News Roman 24 font
	for (int i = 0; i < len; i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, pieces[4][i]);
	}
	//position the string on the screen
	glRasterPos2f(120,110);
	len = pieces[5].length();
	//draw string using the Time News Roman 24 font
	for (int i = 0; i < len; i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, pieces[5][i]);
	}
}
void reshape(int width, int height)
{
	glViewport(0,0,(GLsizei)width,(GLsizei)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90, (GLfloat)width/(GLfloat)height,1.0,500.0f);
	glMatrixMode(GL_MODELVIEW);
}
void display()
{
	//update keyboard status
	keyboardOperations();
	/*if the draw mode is set to all-vertices random, color the background to a random
	color as well*/
	if(drawMode == Letter2D::letterDrawMode::LSDMODE){
		float r = (rand()%256),g = (rand()%256),b = (rand()%256);
		glClearColor((float)r/256.0f,(float)g/256.0f,(float)b/256.0f,1.0f);
	}
	else
		glClearColor(0.0f,0.0f,0.0f,1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	GLfloat diffuse[] = {1,1,1};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glTranslatef(myIDposition.x,myIDposition.y,myIDposition.z);
	glRotatef(myIDRotation.x,1,0,0);
	glRotatef(myIDRotation.y,0,1,0);
	glRotatef(myIDRotation.z,0,0,1);
	drawID(randomizing);
	glLoadIdentity();
	glTranslatef(25.0f,-15.0f,-100.0f);
	drawHUD();
	glutSwapBuffers();
}

void initialize()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_COLOR_MATERIAL);
}
int main(int argc, char **argv)
{
	//Initializing open GL
	for(int i=0;i<256;i++)
		keyStates[i] = false;
	srand(time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(800,450);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Epic Interactive 3D Text Window");
	initialize();
	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutKeyboardFunc(keyPressed);
	glutKeyboardUpFunc(keyReleased);
	glutSpecialFunc(specialKeyPressed);
	glutSpecialUpFunc(specialKeyReleased);
	glutReshapeFunc(reshape);

	glutMainLoop();
	return 0;
}


