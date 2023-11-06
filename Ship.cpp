// Ship.cpp
#include <iostream>
#include <memory>
#include <cmath>
#include <vector>
#include "Ship.h"
#include "ComplexGraphicObject.h"
#include "AnimatedObject.h"
#include "Missile.h"

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
    setRelativeBoundingBox_(-1.f, 1.f, -2.f, 2.f);

    setAbsoluteBoundingBox_(-1.f, 1.f, -2.f, 2.f);
    // Color shipGreyLight = {1.0f, 1.0f, 1.0f};
    Color shipGreyLight = {.37f, .38f, .39f};
    Color thruster = {.41f, .435f, .70f};
    Color orangethrust = {.9804f, .4627f, .0078f};
    Color cockpit = {.6f, .87f, .87f};
    //Rectangle(float centerX, float centerY, float angle, float width, float height, float r, float g, float b);
    // Needed to put in the update otherwise it wouldn't update the part list. 
    // float thrustYPos = -2 - 3 * getVelocity();
    // float thrustYLength = 2 + getVelocity();
    // addPart(std::make_shared<Rectangle>(0,thrustYPos,0, .5f, thrustYLength,orangethrust.r, orangethrust.g, orangethrust.b ));
    addPart(std::make_shared<Rectangle>(0,-0.8,0, .5f,1,thruster.r, thruster.g, thruster.b ));
    addPart(std::make_shared<Polygon>(0,0,0, 1,1,leftBaseWing,shipGreyLight.r, shipGreyLight.g, shipGreyLight.b ));
    addPart(std::make_shared<Polygon>(0,0,0, 1,1,rightBaseWing,shipGreyLight.r, shipGreyLight.g, shipGreyLight.b ));
    addPart(std::make_shared<Polygon>(0,0,0, 1,1,leftFrontWing,shipGreyLight.r, shipGreyLight.g, shipGreyLight.b ));
    addPart(std::make_shared<Polygon>(0,0,0, 1,1,rightFrontWing,shipGreyLight.r, shipGreyLight.g, shipGreyLight.b ));
    		// Ellipse(float centerX, float centerY, float angle, float radiusX, float radiusY,
				// float r, float g, float b);
    addPart(std::make_shared<Ellipse>(0,1,0, .2,.5,cockpit.r, cockpit.g, cockpit.b ));
    
}

std::shared_ptr<Missile> Ship::Fire(){
    float rad_angle = (getAngle() + 90) * (M_PI/180);
    float velocity = getVelocity() + 10;
    float x = getX() + 1.65 * cosf(rad_angle);
    float y = getY() + 1.65 * sinf(rad_angle);
    return std::make_shared<Missile>(x, y, velocity, getAngle());
}
void Ship::resetShip(){
    setX(0);
    setY(0);
    setAngle(0);
    setVelocity(0,0);
    setSpin(0);
}

void Ship::updateAbsoluteBox_() const
{
	float selfXmin = getRelativeBox()->getXmin() + getX();
	float selfXmax = getRelativeBox()->getXmax() + getX();
	float selfYmin = getRelativeBox()->getYmin() + getY();
	float selfYmax = getRelativeBox()->getYmax() + getY();
	float width = selfXmax - selfXmin;
	float height = selfYmax - selfYmin;
	float ca = cosf(getAngleRad()), sa = sinf(getAngleRad());
	float x1 = +0.5f * (ca*width + sa*height) + getX(),
		  x2 = +0.5f * (ca*width - sa*height) + getX(),
		  x3 = x1 - (ca*width + sa*height),
		  x4 = x2 - (ca*width + sa*height);
	float y1 = +0.5f * (sa*width + ca*height) + getY(),
		  y2 = +0.5f * (sa*width - ca*height) + getY(),
		  y3 = y1 - (sa*width + ca*height),
		  y4 = y2 - (sa*width + ca*height);
	// std::cout << "Update" << " | " << getX() << " | " << getY() << " | " << x1 << " | " << x2 << " | " << x3 << " | " << x4 << " | " << y1 << " | " << y2 << " | " << y3 << " | " << y4 << std::endl;

	setAbsoluteBoundingBox_(std::min(std::min(std::min(x1, x2), x3), x4), std::max(std::max(std::max(x1, x2), x3), x4),
							std::min(std::min(std::min(y1, y2), y3), y4), std::max(std::max(std::max(y1, y2), y3), y4));
}