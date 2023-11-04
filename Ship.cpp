// Ship.cpp
#include <iostream>
#include <vector>
#include "Ship.h"
#include "ComplexGraphicObject.h"
#include "AnimatedObject.h"

using namespace earshooter;

struct Color {
    // red
    float r;
    // green
    float g;
    // blue
    float b;
};


std::vector<std::pair<float,float>> leftBaseWing = {{0.0f,1.6f}, {-.3f,1.6f} ,{-1.f,-2.0f},{0.0f,-0.5f}};
std::vector<std::pair<float,float>> rightBaseWing = {{0.3f,1.6f}, {0.0f,1.6f},{0.f,-0.5f},{1.0f,-2.0f}};
std::vector<std::pair<float,float>> leftFrontWing = {{0.0f,2.0f},{0.f,1.5f},{-0.9f,1.2f}};
std::vector<std::pair<float,float>> rightFrontWing = {{0.0f,2.0f},{0.f,1.5f},{0.9f,1.2f}};


Ship::Ship()
    :ComplexGraphicObject(0.f, 0.f, 0.f),
    AnimatedObject(0.f,0.f,0.f,0.f,0.f,0.f),
    Object({0.f,0.f}, 0.f)
{
    // Color shipGreyLight = {1.0f, 1.0f, 1.0f};
    Color shipGreyLight = {.37f, .38f, .39f};
    Color thruster = {.41f, .435f, .70f};
    Color cockpit = {.6f, .87f, .87f};
    //Rectangle(float centerX, float centerY, float angle, float width, float height, float r, float g, float b);
    addPart(std::make_shared<Rectangle>(0,-0.8,0, .5f,1,thruster.r, thruster.g, thruster.b ));
    
    addPart(std::make_shared<Polygon>(0,0,0, 1,1,leftBaseWing,shipGreyLight.r, shipGreyLight.g, shipGreyLight.b ));
    addPart(std::make_shared<Polygon>(0,0,0, 1,1,rightBaseWing,shipGreyLight.r, shipGreyLight.g, shipGreyLight.b ));
    addPart(std::make_shared<Polygon>(0,0,0, 1,1,leftFrontWing,shipGreyLight.r, shipGreyLight.g, shipGreyLight.b ));
    addPart(std::make_shared<Polygon>(0,0,0, 1,1,rightFrontWing,shipGreyLight.r, shipGreyLight.g, shipGreyLight.b ));
    		// Ellipse(float centerX, float centerY, float angle, float radiusX, float radiusY,
				// float r, float g, float b);
    addPart(std::make_shared<Ellipse>(0,1,0, .2,.5,cockpit.r, cockpit.g, cockpit.b ));
    
}
    