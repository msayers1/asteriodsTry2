//
//  main.cpp
//
//	This project summarizes all the basic OpenGL + glut stuff
//	and graphic class material that we have discussed so far.
//	And then it adds a few things:
//		o For class hierarchy, look at comments about virtual
//			functions and destructors.
//		o mouse motion and mouse passive motion callback functions
//		o display of textual information in OpenGL + glut
//
//	Very basic interface with limited keyboard action:
//		- 'q' or ESC exits the app,
//		- 'c' switches between "creation" and "test" modes for mouse clicks
//		- 'm' toggles on/off mouse motion tracking (button pressed)
//		- 'p' toggles on/off passive mouse motion tracking (no button pressed)
//		- 'e' toggles on/off mouse exit/enter
//		- 's' toggles score on/off
//		- 't' toggles on/off text 2nd line of overlay display
//		- 'b' toggles on/off text background display
//		- 'i' activates the input of a second text string
//			(input from the terminal)
//		- 'u' toggles on/off showing absolute bounding boxes
//		- 'r' toggles on/off showing relative bounding boxes
//
//		- clicking the mouse anywhere in the window on mouse down will print out
//			pixel location of the click, convstd::shared_ptr<Ship> ersion in world coordinates, and
//			conversion back to pixels (for verification); on mouse up
//				o In creation mode, will create a random Rectangle or Ellipse,
//					with random likelihood of being animated
//				o In "test" mode, will check if there is a GraphicObject at the
//					click location, and delete the object if this is the case
//
//	Initial aspect ratio of the window is preserved when the window
//	is resized.
//	Pay attention to what I do there for the radius random generator.
//
//  Created by Jean-Yves Hervé on 2023-10-04.
//
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <list>
#include <memory>
#include <random>
#include <chrono>
#include <ctime>
#include <cstring>
//
#include "glPlatform.h"
#include "World.h"
#include "Game.h"
#include "Ellipse.h"
#include "Rectangle.h"
#include "Ship.h"
#include "Missile.h"
#include "Asteriod.h"
#include "BoundingBox.h"
// #include "AnimatedEllipse.h"
// #include "AnimatedRectangle.h"

using namespace std;
using namespace earshooter;

//--------------------------------------
#if 0
#pragma mark Custom data types
#endif
//--------------------------------------

//	I like to setup my meny item indices as enmerated values, but really
//	regular int constants would do the job just fine.
//	Note that in modern C++, it's generally advised to use "scoped enums", which
//	are declared as "enum class NameOfType".  I agree and do so in general, but
//	here these are meant to be used with my glut interface, and it's really
//	bothersome to do the casting to int each each time.

enum MenuItemID {	SEPARATOR = -1,
					//
					QUIT_MENU = 0,
					OTHER_MENU_ITEM,
					SOME_ITEM = 10
};

enum TextColorSubmenuItemID {	FIRST_TEXT = 11,
								RED_TEXT = 11,
								GREEN_TEXT,
								WHITE_TEXT,
								MAGENTA_TEXT,
								//
								MAX_COUNT_TEXT
};
const int NUM_TEXT_COLORS = MAX_COUNT_TEXT - FIRST_TEXT;

enum BackgroundColorSubmenuItemID {	FIRST_BGND = 21,
									LIGHT_GREY_BGND = 21,
									DARK_GREY_BGND,
									GREEN_BGND,
									BLUE_BGND,
									BROWN_BGND,
									//
									MAX_COUNT_BGND
};
const int NUM_BGND_COLORS = MAX_COUNT_BGND - FIRST_BGND;

enum FontSize {
					SMALL_FONT_SIZE = 0,
					MEDIUM_FONT_SIZE,
					LARGE_FONT_SIZE,
					//
					NUM_FONT_SIZES
};

enum AppMode {
				CREATION_MODE = 0,
				TEST_MODE
};

//--------------------------------------
#if 0
#pragma mark Function prototypes
#endif
//--------------------------------------
void initWorld();
void setupShip();
void printMatrix(const GLfloat* m);
void displayTextualInfo(const string& infoStr, int textRow);
void displayTextualInfo(const char* infoStr, int textRow);
void myDisplayFunc(void);
void myResizeFunc(int w, int h);
void myMouseHandler(int b, int s, int x, int y);
void myMouseMotionHandler(int x, int y);
void myMousePassiveMotionHandler(int x, int y);
void myEntryHandler(int state);
void myKeyHandler(unsigned char c, int x, int y);
void myMenuHandler(int value);
void mySubmenuHandler(int colorIndex);
void myTimerFunc(int val);
void applicationInit();

//--------------------------------------
#if 0
#pragma mark Constants
#endif
//--------------------------------------
const int INIT_WIN_X = 10, INIT_WIN_Y = 32;

const float World::X_MIN = -20.f;
const float World::X_MAX = +20.f;
const float World::Y_MIN = -20.f;
const float World::Y_MAX = +20.f;
const float World::WIDTH = World::X_MAX - World::X_MIN;
const float World::HEIGHT = World::Y_MAX - World::Y_MIN;
//
//	I set my speed range in terms of the time it takes to go across the window
const float MIN_SPEED = World::WIDTH/20.f;
const float MAX_SPEED = World::WIDTH/5.f;

#define SMALL_DISPLAY_FONT    GLUT_BITMAP_HELVETICA_10
#define MEDIUM_DISPLAY_FONT   GLUT_BITMAP_HELVETICA_12
#define LARGE_DISPLAY_FONT    GLUT_BITMAP_HELVETICA_18
const int H_PAD = 10;
const int V_PAD = 5;

const string TEXT_COLOR_STR[NUM_TEXT_COLORS] = {"white",		//	WHITE_TEXT
												"red",			//	RED_TEXT
												"green",		//	GREEN_TEXT
												"magenta"};		//	MAGENTA_TEXT
							
const string BGND_COLOR_STR[NUM_BGND_COLORS] = {"light gray",	//	LIGHT_GREY_BGND
												"dark gray",	//	DARK_GREY_BGND
												"green",		//	GREEN_BGND
												"blue",			//	BLUE_BGND
												"brown"};		//	BROWN_BGND

const GLfloat TEXT_COLOR[NUM_TEXT_COLORS][3] = { {1.f, 1.f, 1.f},	//	WHITE_TEXT
												 {1.f, 0.f, 0.f},	//	RED_TEXT
												 {0.f, .8f, 0.f},	//	GREEN_TEXT
												 {1.f, 0.f, 1.f}};	//	MAGENTA_TEXT
							
const GLfloat BGND_COLOR[NUM_BGND_COLORS][3] = { {.5f, .5f, .5f},	//	LIGHT_GREY_BGND
												 {.3f, .3f, .3f},	//	DARK_GREY_BGND
												 {0.f, .4f, 0.f},	//	GREEN_BGND
												 {0.f, 0.f, .4f},	//	BLUE_BGND
												 {.4f, .2f, 0.f}};	//	BROWN_BGND

const bool displayTextOnLeft = false;
const bool displayTextOnTop = true;
const FontSize fontSize = LARGE_FONT_SIZE;

//--------------------------------------
#if 0
#pragma mark Global variables
#endif
//--------------------------------------

// std::shared_ptr<Missile> missile;
std::shared_ptr<Ship> ship;
//Game Class
Game newGame = Game();
float minAsteriodVelocity = 2;
float maxAsteriodVelocity = 10;

time_t startTime = -1;
int winWidth = 800,
    winHeight = 800;

random_device World::randDev;
default_random_engine World::randEngine(World::randDev());
uniform_real_distribution<double> World::wallDist = uniform_real_distribution<double>(0, 3);
uniform_real_distribution<float> World::speedDist = uniform_real_distribution<float>(2, 10);
uniform_real_distribution<float> World::wxDist = uniform_real_distribution<float>(World::X_MIN, World::X_MAX);
uniform_real_distribution<float> World::wyDist = uniform_real_distribution<float>(World::Y_MIN, World::Y_MAX);
uniform_real_distribution<float> World::objectScaleDist = uniform_real_distribution<float>(World::WIDTH/20, World::WIDTH/10);
uniform_real_distribution<float> World::colorDist(0.f, 1.f);
uniform_real_distribution<float> World::normalDist(0.f, 1.f);
uniform_real_distribution<float> World::angleDegDist(0.f, 360.f);
uniform_real_distribution<float> World::angleRadDist(0.f, 2.f*M_PI);
//	In non-simulation contexts, I like to specify velocities in terms of the time it goes
//	to go cross the world (in seconds).  For simulations, the problem dictates speed.
// re-initialized when the window is resized
uniform_real_distribution<float> World::spinDegDist(360.f/15.f, 360.f/5.f);
// 8 chance out of 10 for an ellipse generated by click to be animated
bernoulli_distribution World::animatedChoiceDist(8.0/10.0f);
bernoulli_distribution World::headsOrTailsDist(0.5f);

// re-initialized when the window is resized
uniform_real_distribution<float> World::radiusDist;

float World::pixelToWorldRatio;
float World::worldToPixelRatio;
float World::drawInPixelScale;

bool trackEntry = false;
bool trackMousePointer = false;
bool trackPassiveMousePointer = false;
bool pointerInWindow = false;
GLint lastX = -1, lastY = -1;

bool scoreDisplay = true;
bool displayText = false;
bool displayBgnd = false;
bool displayAbsoluteBoxes = false;
bool displayRelativeBoxes = false;
string stringLine = "";
const GLfloat* textColor = TEXT_COLOR[0];
const GLfloat* bgndColor = BGND_COLOR[0];

// list<shared_ptr<GraphicObject> > ObjectList;
// list<shared_ptr<AnimatedObject> > animatedObjectList;
std::vector<std::pair<shared_ptr<ComplexGraphicObject>,shared_ptr<AnimatedObject>>> ObjectList;
list<shared_ptr<Asteriod>> AsteriodList;
list<shared_ptr<Missile>> MissileList;

WorldType World::worldType = WorldType::TORUS_WORLD;
// WorldType World::worldType = WorldType::CYLINDER_WORLD;
AppMode appMode = AppMode::CREATION_MODE;

//	reference frames (using 'f' key);
bool World::showReferenceFrames = false;

//--------------------------------------
#if 0
#pragma mark -
#pragma mark Callback functions
#endif
//--------------------------------------


void myDisplayFunc(void)
{
	//	This clears the buffer(s) we draw into.  We will see later this
	//	semester what this really means
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//	There are two "matrix modes" in OpenGL: "projection", which sets up the
	//	camera, and "model view" which we have to be in to do any drawing
	glMatrixMode(GL_MODELVIEW);
	
	//	This says that we start from the origin of the camera, whose coordinates
	//	(in the 2D case) coincide with that of the world's orogin.
	glLoadIdentity();
	glPushMatrix();
	
	//--------------------------
	//	Draw stuff
	//--------------------------
	// glColor3f(1.f, 0.5f, 0.f);
	// glBegin(GL_POLYGON);
	// 	glVertex2f(1.5f, -5.0f);
	// 	glVertex2f(4.f, 1.0f);
	// 	glVertex2f(-1.f, 3.f);
	// glEnd();

	for (auto obj : ObjectList)
	{
		if (obj.first != nullptr)
			obj.first->draw();
	}
	ship->draw();

	if (World::worldType == WorldType::CYLINDER_WORLD || World::worldType == WorldType::TORUS_WORLD)
	{
		glTranslatef(-World::WIDTH, 0, 0);
		for (auto obj : ObjectList)
			{
				if (obj.first != nullptr)
					obj.first->draw();
			
			}
		ship->draw();

		glTranslatef(2*World::WIDTH, 0, 0);
		for (auto obj : ObjectList)
			{
				if (obj.first != nullptr)
					obj.first->draw();

			}
		ship->draw();

	}
	//Torus world to get the 3 above and 3 below. 
	if (World::worldType == WorldType::TORUS_WORLD)
	{
		glTranslatef(0,-World::HEIGHT, 0);
		for (auto obj : ObjectList)
			{
				if (obj.first != nullptr)
					obj.first->draw();
			}
		ship->draw();

		glTranslatef(-World::WIDTH, 0, 0);
		for (auto obj : ObjectList)
			{
				if (obj.first != nullptr)
					obj.first->draw();
			}
		ship->draw();

		glTranslatef(-World::WIDTH, 0, 0);
		for (auto obj : ObjectList)
			{
				if (obj.first != nullptr)
					obj.first->draw();
			}
		ship->draw();


		glTranslatef(0, 2*World::HEIGHT, 0);
		for (auto obj : ObjectList)
			{
				if (obj.first != nullptr)
					obj.first->draw();
			}
		ship->draw();

		glTranslatef(World::WIDTH, 0, 0);
		for (auto obj : ObjectList)
			{
				if (obj.first != nullptr)
					obj.first->draw();
			}
		ship->draw();

		glTranslatef(World::WIDTH, 0, 0);
		for (auto obj : ObjectList)
			{
				if (obj.first != nullptr)
					obj.first->draw();
			}
		ship->draw();	
	}

	glPopMatrix();

	//	Reminder:	Not really needed here, but this is how to display the current
	//				transformation matrix in case you need it.
	static bool isFirstDraw = true;
	if (isFirstDraw)
	{
		GLfloat A[16];
		glGetFloatv(GL_MODELVIEW_MATRIX, A);
		cout << "Back to origin" << endl;
		printMatrix(A);
		isFirstDraw = false;
	}
	
	//	Display textual info
	//---------------------------------
	//	We are back at the world's origin (by the glPopMatrix() just above), in world coordinates.
	//	So we must undo the scaling to be back in pixels, which how text is drawn for now.
	if (true)
	{
	//	First, translate to the upper-left corner
		glTranslatef(World::X_MIN, World::Y_MAX, 0.f);
		
		//	Then reverse the scaling: back in pixels, making sure that y now points down
		// glScalef(World::drawInPixelScale, -World::drawInPixelScale, 1.f);
		glScalef(World::drawInPixelScale, -World::drawInPixelScale, 1.f);


		char statusLine[256];
		char a2ndstatusLine[256];

		WorldPoint mouse = pixelToWorld(lastX, lastY);
		sprintf(a2ndstatusLine, "Runtime: %d s | Mouse last seen at (%f, %f)  ",
								static_cast<int>(time(nullptr)-startTime),
								mouse.x, mouse.y);
		sprintf(statusLine, "GameStatus: %d | Score: %f   |  Number of Lives: %f | structural Integrity: %f |  ",
								newGame.getGameStatus(),
								newGame.getScore(), 
								newGame.getLives(),
								newGame.getShipStructuralIntegrity());
		// sprintf(statusLine, "Runtime: %d s   |   Number of objects: %d   |   Mouse last seen at (%d, %d)",
		// 						static_cast<int>(time(nullptr)-startTime),
		// 						static_cast<int>(ObjectList.size()),
		// 						lastX, lastY);
		if(scoreDisplay)
			displayTextualInfo(statusLine, 0);		//	first row
		if(displayText){
			displayTextualInfo(a2ndstatusLine, 1);		//	second row
		}

		if (stringLine != "")
		displayTextualInfo(stringLine, 2);		//	third row
	}

	//	We were drawing into the back buffer, now it should be brought
	//	to the forefront.
	glutSwapBuffers();
}

void myResizeFunc(int w, int h)
{
	winWidth = w;
    winHeight = h;
	
	World::setScalingRatios(winWidth, winHeight);
	if (winWidth != w || winHeight != h)
	{
		glutReshapeWindow(winWidth, winHeight);
	}
	
	//	This calls says that I want to use the entire dimension of the window for my drawing.
	glViewport(0, 0, winWidth, winHeight);

	//	Here I create my virtual camera.  We are going to do 2D drawing for a while, so what this
	//	does is define the dimensions (origin and units) of the "virtual world that my viewport
	//	maps to.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//	Here I define the dimensions of the "virtual world" that my
	//	window maps to
	gluOrtho2D(World::X_MIN, World::X_MAX, World::Y_MIN, World::Y_MAX);

	//	When it's done, request a refresh of the display
	glutPostRedisplay();
 }

void myMenuHandler(int choice)
{
	switch (choice)
	{
		//	Exit/Quit
		case QUIT_MENU:
			exit(0);
			break;
		
		//	Do something
		case OTHER_MENU_ITEM:
			break;
		
		default:	//	this should not happen
			break;
	
	}

    glutPostRedisplay();
}

//  in this example my submenu selection indicates the keyboard handling
//  function to use.
void mySubmenuHandler(int choice)
{
	switch (choice)
	{
		case RED_TEXT:
		case GREEN_TEXT:
		case WHITE_TEXT:
		case MAGENTA_TEXT:
			textColor = TEXT_COLOR[choice - FIRST_TEXT];
			break;
			
		case LIGHT_GREY_BGND:
		case DARK_GREY_BGND:
		case GREEN_BGND:
		case BLUE_BGND:
		case BROWN_BGND:
			bgndColor = BGND_COLOR[choice - FIRST_BGND];
			break;
		
		default:
			break;
	}
}

//	This function is called when a mouse event occurs.  This event, of type s
//	(up, down, dragged, etc.), occurs on a particular button of the mouse.
//
void myMouseHandler(int button, int state, int ix, int iy)
{
	switch (button)
	{
		case GLUT_LEFT_BUTTON:
			if (state == GLUT_DOWN)
			{
				//	do something
//				cout << "Click at: (" << ix << ", " << iy << ")" << endl;
//				WorldPoint wPt = pixelToWorld(ix, iy);
//				cout << "Corresponding world point: (" << wPt.x << ", " <<
//						wPt.y << ")" << endl;
//				PixelPoint pPt = worldToPixel(wPt.x, wPt.y);
//				cout << "Back to pixels: (" << pPt.x << ", " <<
//						pPt.y << ")" << endl;
				
			}
			else if (state == GLUT_UP)
			{
				// WorldPoint clickPt = pixelToWorld(ix, iy);
				
				// if (appMode == AppMode::TEST_MODE)
				// {
				// 	shared_ptr<GraphicObject> objHit = nullptr;
				// 	for (auto obj : ObjectList)
				// 	{
				// 		if (obj->isInside(clickPt)) {
				// 			cout << "Clicked inside object" << endl;
				// 			objHit = obj;
				// 			break;
				// 		}
				// 	}
				// 	if (objHit != nullptr)
				// 	{
				// 		ObjectList.remove(objHit);
				// 		//	animated object list.  I will search by index.
				// 		int hitIndex = objHit->getIndex();
				// 		shared_ptr<AnimatedObject> animatedHit = nullptr;
				// 		for (auto obj : animatedObjectList)
				// 		{
				// 			if (obj->getIndex() == hitIndex)
				// 			{
				// 				animatedHit = obj;
				// 				break;
				// 			}
				// 		}
				// 		if (animatedHit != nullptr)
				// 		{
				// 			animatedObjectList.remove(animatedHit);
				// 		}
				// 	}
				// }
				// //	Creation mode
				// else
				// {
				// 	//----------------
				// 	//	ellipse
				// 	//----------------
				// 	if (headsOrTails())
				// 	{
				// 		//	create a randomly-colored ellipse centered at the click location
				// 		WorldPoint clickPt = pixelToWorld(ix, iy);
				// 		if (isAnimated())
				// 		{
				// 			shared_ptr<AnimatedEllipse> ell  = make_shared<AnimatedEllipse>(
				// 					clickPt,								//	{x, y}
				// 					randomAngleDeg(),						//	angle
				// 					randomObjectScale()*0.5f,				//	h radius
				// 					randomObjectScale()*0.5f,				//	v radius
				// 					randomVelocity(MIN_SPEED, MAX_SPEED),	//	{vx, vy}
				// 					randomSpinDeg(),						//	spin
				// 					randomColor(),							//	red
				// 					randomColor(),							//	green
				// 					randomColor());							//	blue
				// 			animatedObjectList.push_back(ell);
				// 			ObjectList.push_back(ell);
				// 		}
				// 		else
				// 		{
				// 			ObjectList.push_back(make_shared<Ellipse>(
				// 					clickPt,								//	{x, y}
				// 					randomAngleDeg(),						//	angle
				// 					randomObjectScale()*0.5f,				//	h radius
				// 					randomObjectScale()*0.5f,				//	v radius
				// 					randomColor(),							//	red
				// 					randomColor(),							//	green
				// 					randomColor()));						//	blue
				// 		}
				// 	}
				// 	//----------------
				// 	//	Rectangle
				// 	//----------------
				// 	else
				// 	{ship
				// 		//	create a randomly-colored ellipse centered at the click location
				// 		WorldPoint clickPt = pixelToWorld(ix, iy);
				// 		if (isAnimated())
				// 		{
				// 			shared_ptr<AnimatedRectangle> rect = make_shared<AnimatedRectangle>(
				// 					clickPt,								//	{x, y}
				// 					randomAngleDeg(),						//	angle
				// 					randomObjectScale(),					//	width
				// 					randomObjectScale(),					//	height
				// 					randomVelocity(MIN_SPEED, MAX_SPEED),	//	{vx, vy}
				// 					randomSpinDeg(),						//	spin
				// 					randomColor(),							//	red
				// 					randomColor(),							//	green
				// 					randomColor());							//	blue
				// 			animatedObjectList.push_back(rect);
				// 			ObjectList.push_back(rect);
				// 		}
				// 		else
				// 		{
				// 			ObjectList.push_back(make_shared<Rectangle>(
				// 					clickPt,								//	{x, y}
				// 					randomAngleDeg(),						//	angle
				// 					randomObjectScale(),					//	width
				// 					randomObjectScale(),					//	height
				// 					randomColor(),							//	red
				// 					randomColor(),							//	green
				// 					randomColor()));						//	blue
				// 		}
						
				// 	}
				
				// }
			}
		break;
		
		case GLUT_RIGHT_BUTTON:
			break;
		
		default:
		break;
	}
}

void myMouseMotionHandler(int ix, int iy)
{
	if (trackMousePointer)
	{
		cout << "Active mouse at (" << ix << ", " << iy << ")" << endl;
	}
}
void myMousePassiveMotionHandler(int ix, int iy)
{
	lastX = ix;
	lastY = iy;
	pointerInWindow = (ix >= 0 && ix < winWidth && iy >= 0 && iy < winHeight);

	if (trackPassiveMousePointer)
	{
		cout << "Passive mouse at (" << ix << ", " << iy << ")" << endl;
	}

}
void myEntryHandler(int state)
{
	if (trackEntry)
	{
		if (state == GLUT_ENTERED)
		{
			pointerInWindow = true;
			cout << "===> Pointer entered" << endl;
		}
		else	// GLUT_LEFT
		{
			pointerInWindow = false;
			cout << "<=== Pointer exited" << endl;
		}
	}
}


//	This callback function is called when a keyboard event occurs
//
void myKeyHandler(unsigned char c, int x, int y)
{
	// silence warning
	(void) x;
	(void) y;
	std::shared_ptr<Missile> missile;
	switch (c)
	{
		case 'q':
		case 27:
			exit(0);
			break;
		
		case 'm':
			trackMousePointer = !trackMousePointer;
			break;

		case 'p':
			trackPassiveMousePointer = !trackPassiveMousePointer;
			break;
			
		case 'e':
			trackEntry = !trackEntry;
			break;
			
		case 'i':
			cout << "Enter a new line of text: ";
			getline(cin, stringLine);
			break;
			
		case 't':
			displayText = !displayText;
			break;	
		case 's':
			scoreDisplay = !scoreDisplay;
			break;
			

		case 'b':
			displayBgnd = !displayBgnd;
			break;

			// Left Spin
		case 'a':
			// std::cout << "I pressed a and my spin is" << ship->getSpin() << std::endl;
			ship->setSpin((ship->getSpin() + 1));
			// std::cout << "After I pressed a and my spin is" << ship->getSpin() << std::endl;
			break;
		// Right Spin
		case 'd':
			ship->setSpin((ship->getSpin() - 1));
			break;
		// Thrust
		case 'w':
			ship->setVelocityWithGraphicObjectAngle((ship->getVelocity() + .1));
			break;
		// Fire
		case ' ':
			// cout << "fire!" << ship->getX()  << " | " << ship->getY()  << ship->getAngle() << std::endl;
			missile = ship->Fire();
			// std::shared_ptr<Missile> missile = make_shared<Missile>((ship->getAngle()));
			//std::shared_ptr<Missile> missile = make_shared<Missile>();
			ObjectList.push_back(make_pair(missile,missile));
			MissileList.push_back(missile);
			break;


		// case 'c':
		// 	if (appMode == AppMode::CREATION_MODE)
		// 		appMode = AppMode::TEST_MODE;
		// 	else
		// 		appMode = AppMode::CREATION_MODE;
		// 	break;
		case 'f':
			World::showReferenceFrames = !World::showReferenceFrames;
			break;
		case 'u':
			displayAbsoluteBoxes = !displayAbsoluteBoxes;
			if (displayAbsoluteBoxes)
				displayRelativeBoxes = false;
			GraphicObject::drawAbsoluteBoxes(displayAbsoluteBoxes);
			break;
			
		case 'r':
			displayRelativeBoxes = !displayRelativeBoxes;
			if (displayRelativeBoxes)
				displayAbsoluteBoxes = false;
			GraphicObject::drawRelativeBoxes(displayRelativeBoxes);
			break;
		case 'n':
			(*ship).resetShip();
			newGame.resetGame();
			ObjectList.clear();
			AsteriodList.clear();
			MissileList.clear();
			break;
			
		default:
			break;
	}
}

void mySpecialKeyHandler(int key, int x, int y)
{

	//Use the arrow keys to control the displacements of Frogger. Please note that you cannot use the
	// regular glutKeyboardFunc() callback setup to handle the arrow keys. Instead you must use	
	// the glutSpecialFunc() callback setup (and GLUT KEY UP, GLUT KEY LEFT, etc. for the
	// key code, an int rather than an unsigned char).
	switch(key){
		case GLUT_KEY_UP:
			ship->setVelocityWithGraphicObjectAngle((ship->getVelocity() + .1));
			// cout << "Up" << endl;
			break;
		case GLUT_KEY_LEFT:
			ship->setSpin((ship->getSpin() + 1));
			// cout << "Left" << endl;			
			break;
		case GLUT_KEY_RIGHT:
			ship->setSpin((ship->getSpin() - 1));
			// cout << "Right" << endl;
			break; 
	}
}

void myTimerFunc(int value)
{
	static int frameIndex=0;
	

	static chrono::high_resolution_clock::time_point lastTime = chrono::high_resolution_clock::now();

	//	"re-prime the timer"
	glutTimerFunc(1, myTimerFunc, value);

		
	//	 do something (e.g. update the state of animated objects)
	chrono::high_resolution_clock::time_point currentTime = chrono::high_resolution_clock::now();
	float dt = chrono::duration_cast<chrono::duration<float> >(currentTime - lastTime).count();
	if(newGame.getGameStatus())
	{	
		for (auto obj : ObjectList)
		{
			if (obj.second != nullptr)
				obj.second->update(dt);
		}
		ship->update(dt);

		for (auto ast : AsteriodList)
		{
			//Check for ship collision
		}
		bool hitStatus = false;
		if (frameIndex % 100 == 0)
		{
			auto ast = AsteriodList.begin();
			auto mis = MissileList.begin();
			while(ast != AsteriodList.end())
			{
				std::shared_ptr<BoundingBox> asteriodBoundingBox = (*ast)->getAbsoluteBox();
				if(MissileList.size() > 0)
				{
					while(mis != MissileList.end())
					{
						if((*ast)->collision(asteriodBoundingBox)){
							// std::cout << "Hit" << std::endl;
							newGame.increaseScore(100);
							auto needle = std::remove_if(ObjectList.begin(), ObjectList.end(), [&](const std::pair<std::shared_ptr<ComplexGraphicObject>, std::shared_ptr<AnimatedObject>>& pair) {
							return (pair.first == (*mis));
							});
							ObjectList.erase(needle);
							MissileList.erase(mis);
							hitStatus = true;
							break;
						}else{
							if((*mis)->checkFuel()){
								// std::cout << "Hit" << std::endl;
								auto needle = std::remove_if(ObjectList.begin(), ObjectList.end(), [&](const std::pair<std::shared_ptr<ComplexGraphicObject>, std::shared_ptr<AnimatedObject>>& pair) {
								return (pair.first == (*mis));
								});
								ObjectList.erase(needle);
								MissileList.erase(mis);
								break;
							}
							++mis;
						}
					}
					if(hitStatus){
						auto needle = std::remove_if(ObjectList.begin(), ObjectList.end(), [&](const std::pair<std::shared_ptr<ComplexGraphicObject>, std::shared_ptr<AnimatedObject>>& pair) {
						return (pair.first == (*ast));
						});
						ObjectList.erase(needle);
						AsteriodList.erase(ast);
						break;
					}
				}

				// cout << "Checking for collision" << endl;
				if((*ast)->collision(ship->getAbsoluteBox())){
					// std::cout << "Collision" << std::endl;
					newGame.setShipStructuralIntegrity(2);
					float angle = (*ast)->getAngle();
					float reverseAngle;
					if (angle > 180)
						reverseAngle = angle - 180;
					if (angle <= 180)
						reverseAngle = angle + 180;
					(*ast)->setVelocity((*ast)->getVelocity(), reverseAngle);
				}
			
				++ast;
			}
		}
		lastTime = currentTime;
		// if (frameIndex % 100 == 0)
		// {
		// 	if(AsteriodList.size() > 0){
		// 		ast = AsteriodList.begin();

		// 		while(ast != AsteriodList.end())
		// 		{
		// 			if((*ast)->collision(ship->getAbsoluteBox())){
		// 				std::cout << "Collision" << std::endl;
		// 				newGame.setShipStructuralIntegrity(2);
		// 				float angle = (*ast)->getAngle();
		// 				float reverseAngle;
		// 				if (angle > 180)
		// 					reverseAngle = angle - 180;
		// 				if (angle <= 180)
		// 					reverseAngle = angle + 180;
		// 				(*ast)->setVelocity((*ast)->getVelocity(), reverseAngle);
		// 			}
		// 		}
		// 	}
		// }

		// return WorldPoint{ World::wxDist(World::randEngine),
		// 					   World::wyDist(World::randEngine)};
		if(frameIndex % 3000 == 0){
			int wall = randomWall();
			float ranVelocity = randomSpeed();
			float ranAngle = randomAngleDeg();
			std::shared_ptr<Asteriod> bob;
			switch(wall){
				case 0:
					bob = make_shared<Asteriod>( World::wxDist(World::randEngine), World::Y_MAX, ranVelocity, ranAngle);
					ObjectList.push_back(make_pair(bob,bob));
					AsteriodList.push_back(bob);
					break;
				case 1:
					bob = make_shared<Asteriod>( World::X_MAX, World::wyDist(World::randEngine), ranVelocity, ranAngle);
					ObjectList.push_back(make_pair(bob,bob));
					AsteriodList.push_back(bob);
					break;
				case 2:
					bob = make_shared<Asteriod>( World::wxDist(World::randEngine), World::Y_MIN, ranVelocity, ranAngle);
					ObjectList.push_back(make_pair(bob,bob));
					AsteriodList.push_back(bob);
					break;
				case 3:
					bob = make_shared<Asteriod>( World::X_MIN, World::wyDist(World::randEngine), ranVelocity, ranAngle);
					ObjectList.push_back(make_pair(bob,bob));
					AsteriodList.push_back(bob);
					break;			
			}
		}
	}	//	And finally I perform the rendering
	
	if (frameIndex++ % 10 == 0)
	{
		glutPostRedisplay();
	}

}

//--------------------------------------
#if 0
#pragma mark -
#pragma mark Utilities
#endif
//--------------------------------------

void displayTextualInfo(const string& infoStr, int textRow){
	displayTextualInfo(infoStr.c_str(), textRow);
}

void displayTextualInfo(const char* infoStr, int textRow)
{
    //-----------------------------------------------
    //  0.  Build the string to display <-- parameter
    //-----------------------------------------------
    int infoLn = static_cast<int> (strlen(infoStr));

    //-----------------------------------------------
    //  1.  Determine the string's length (in pixels)
    //-----------------------------------------------
    int textWidth = 0, fontHeight=-1;
	switch(fontSize)
	{
		case SMALL_FONT_SIZE:
			fontHeight = 10;
			for (int k=0; k<infoLn; k++)
			{
				textWidth += glutBitmapWidth(SMALL_DISPLAY_FONT, infoStr[k]);
			}
			break;
		
		case MEDIUM_FONT_SIZE:
			fontHeight = 12;
			for (int k=0; k<infoLn; k++)
			{
				textWidth += glutBitmapWidth(MEDIUM_DISPLAY_FONT, infoStr[k]);
			}
			break;
		
		case LARGE_FONT_SIZE:
			fontHeight = 16;
			for (int k=0; k<infoLn; k++)
			{
				textWidth += glutBitmapWidth(LARGE_DISPLAY_FONT, infoStr[k]);
			}
			break;
			
		default:
			break;
	}

    //-----------------------------------------------
    //  2.  get current material properties
    //-----------------------------------------------
    float oldAmb[4], oldDif[4], oldSpec[4], oldShiny;
    glGetMaterialfv(GL_FRONT, GL_AMBIENT, oldAmb);
    glGetMaterialfv(GL_FRONT, GL_DIFFUSE, oldDif);
    glGetMaterialfv(GL_FRONT, GL_SPECULAR, oldSpec);
    glGetMaterialfv(GL_FRONT, GL_SHININESS, &oldShiny);

    glPushMatrix();
	if (displayTextOnTop)
    {
		glTranslatef(0.f, textRow*(fontHeight+2*V_PAD), 0.f);
    }
	else
    {
		glTranslatef(0.f, winHeight - (textRow+1)*(fontHeight+2*V_PAD),0.f);
	}

    //-----------------------------------------------
    //  3.  Clear background rectangle if required
    //-----------------------------------------------
    if (displayBgnd)
    {
		glColor3fv(bgndColor);
		glBegin(GL_POLYGON);
			glVertex2i(0, 0);
			glVertex2i(0, fontHeight + 2*V_PAD);
			glVertex2i(winWidth, fontHeight + 2*V_PAD);
			glVertex2i(winWidth, 0);
		glEnd();
	}
	
	//	Move "up" from current plane, to make sure that we overwrite
	glTranslatef(0.f, 0.f, 0.1f);

    //-----------------------------------------------
    //  4.  Draw the string
    //-----------------------------------------------    
    //	Where do we start drawing from
    int xPos = displayTextOnLeft ? H_PAD : winWidth - textWidth - H_PAD;
    int yPos = fontHeight + V_PAD;

    glColor3fv(textColor);
    int x = xPos;
	switch(fontSize)
	{
		case SMALL_FONT_SIZE:
			for (int k=0; k<infoLn; k++)
			{
				glRasterPos2i(x, yPos);
				glutBitmapCharacter(SMALL_DISPLAY_FONT, infoStr[k]);
				x += glutBitmapWidth(SMALL_DISPLAY_FONT, infoStr[k]);
			}
			break;
		
		case MEDIUM_FONT_SIZE:
			for (int k=0; k<infoLn; k++)
			{
				glRasterPos2i(x, yPos);
				glutBitmapCharacter(MEDIUM_DISPLAY_FONT, infoStr[k]);
				x += glutBitmapWidth(MEDIUM_DISPLAY_FONT, infoStr[k]);
			}
			break;
		
		case LARGE_FONT_SIZE:
			for (int k=0; k<infoLn; k++)
			{
				glRasterPos2i(x, yPos);
				glutBitmapCharacter(LARGE_DISPLAY_FONT, infoStr[k]);
				x += glutBitmapWidth(LARGE_DISPLAY_FONT, infoStr[k]);
			}
			break;
			
		default:
			break;
	}

    //-----------------------------------------------
    //  5.  Restore old material properties
    //-----------------------------------------------
	glMaterialfv(GL_FRONT, GL_AMBIENT, oldAmb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, oldDif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, oldSpec);
	glMaterialf(GL_FRONT, GL_SHININESS, oldShiny);  
    
    //-----------------------------------------------
    //  6.  Restore reference frame
    //-----------------------------------------------
    glPopMatrix();
}

void printMatrix(const GLfloat* m) {
    cout << "((" << m[0] << "\t" << m[4] << "\t" << m[8] << "\t" << m[12] << ")" << endl;
    cout << " (" << m[1] << "\t" << m[5] << "\t" << m[9] << "\t" << m[13] << ")" << endl;
    cout << " (" << m[2] << "\t" << m[6] << "\t" << m[10] << "\t" << m[14] << ")" << endl;
    cout << " (" << m[3] << "\t" << m[7] << "\t" << m[11] << "\t" << m[15] << "))" << endl;
}

void setupShip()
{
	// printf("setupShip\n");
	ship = make_shared<Ship>();
	ObjectList.push_back(make_pair(ship, ship));
}


//--------------------------------------
#if 0
#pragma mark -
#pragma mark Application init and main
#endif
//--------------------------------------

void applicationInit()
{
	// // Create Menus
	// int myMenu;
	
	// //	Submenu for changing keyboard handling function
	// int myTextColorSubmenu = glutCreateMenu(mySubmenuHandler);
	// for (int k=0, t=FIRST_TEXT; k<NUM_TEXT_COLORS; k++, t++)
	// 	glutAddMenuEntry(TEXT_COLOR_STR[k].c_str(), t);
	// int myBgndColorSubmenu = glutCreateMenu(mySubmenuHandler);
	// for (int k=0, b=FIRST_BGND; k<NUM_BGND_COLORS; k++, b++)
	// 	glutAddMenuEntry(BGND_COLOR_STR[k].c_str(), b);

	// // Main menu that the submenus are connected to
	// myMenu = glutCreateMenu(myMenuHandler);
	// glutAddMenuEntry("Quit", MenuItemID::QUIT_MENU);
	// //
	// glutAddMenuEntry("-", MenuItemID::SEPARATOR);
	// glutAddMenuEntry("Other stuff", MenuItemID::OTHER_MENU_ITEM);
	// glutAddMenuEntry("New entry", 64);
	
	// glutAddMenuEntry("-", MenuItemID::SEPARATOR);
	// glutAddSubMenu("Text color:", myTextColorSubmenu);
	// glutAddSubMenu("Background color:", myBgndColorSubmenu);
	// glutAddMenuEntry("-", MenuItemID::SEPARATOR);
	// glutAttachMenu(GLUT_RIGHT_BUTTON);

	// ObjectList.push_back(make_shared<Face>(-3.f, -2.f));

	// ObjectList.push_back(make_shared<Ellipse>(4, 4, 2, 0.f, 1.f, 1.f));
	// ObjectList.push_back(make_shared<Ellipse>(4, -4, 3, 0.f, 1.f, 1.f));


	// ObjectList.push_back(make_shared<Ellipse>(7, 2, 0, 0.3f, .25f, 1.f, 1.f, 1.f));
	// ObjectList.push_back(make_shared<Ellipse>(2, 7, 0, .250f, 0.6f, 0.f, 0.f, 1.f));
	// ObjectList.push_back(make_shared<Ellipse>(6, 5, 45, 2.f, 1.f, 1.f, 1.f, 0.f));

	// ObjectList.push_back(make_shared<Face>(-5.f, -6.f));

	// ObjectList.push_back(make_shared<Rectangle>(-8, 6, 45, 4, 2, 1.f, 1.f, 0.f));

	// ObjectList.push_back(make_shared<Rectangle>(-7, -4, 0, 4, 2, 1.f, 0.f, 0.f));


	// World::worldType = WorldType::BOX_WORLD;
	
	// for (int k=0; k<8; k++)
	// {
	// 	//	create the object
	// 	shared_ptr<SmilingFace> face = make_shared<SmilingFace>();
	// 	//	and add it to both lists
	// 	ObjectList.push_back(face);
	// 	animatedObjectList.push_back(face);
	// }
	
	
	//	time really starts now
	startTime = time(nullptr);
}

void initWorld(){
	World::setScalingRatios(winWidth, winHeight);
}

int main(int argc, char * argv[])
{
	// initiate world
	initWorld();
	setupShip();
	//	Initialize glut and create a new window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	glutInitWindowSize(winWidth, winHeight);
	glutInitWindowPosition(INIT_WIN_X, INIT_WIN_Y);
	glutCreateWindow("Asteriods");
	//	set up the callbacks
	glutDisplayFunc(myDisplayFunc);
	glutReshapeFunc(myResizeFunc);
	glutMouseFunc(myMouseHandler);
	glutMotionFunc(myMouseMotionHandler);
	glutPassiveMotionFunc(myMousePassiveMotionHandler);
	glutEntryFunc(myEntryHandler);
	glutKeyboardFunc(myKeyHandler);
	glutSpecialFunc(mySpecialKeyHandler);
	glutTimerFunc(1,	myTimerFunc,		0);
	//			  time	    name of		value to pass
	//			  in ms		function	to the func
	
	//	Now we can do application-level
	applicationInit();

	//	Now we enter the main loop of the program and to a large extend
	//	"lose control" over its execution.  The callback functions that
	//	we set up earlier will be called when the corresponding event
	//	occurs
	glutMainLoop();
	
	//	This will never be executed (the exit point will be in one of the
	//	callback functions).
	return 0;
}
