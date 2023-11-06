// Asteriod.cpp
#include <iostream>
#include <vector>
#include "Asteriod.h"
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

Color asteriodColor = {.2235f, .2510f, .2157f};
// std::vector<std::pair<float,float>> asteriodVertices = {{0.0f,0.9f}, {-.25f,0.7f} ,{+.25f, 0.7f}};

Asteriod::Asteriod(float x, float y, float velocity, float angle)
    :ComplexGraphicObject(x, y, angle),
    AnimatedObject(x, y, angle, 0.f, 0.f, 0.f),
    Object({x,y}, angle)
{
    // std::cout << x << " | " << y << " | " << angle << std::endl;
    setVelocity(velocity, angle + 90);
    // addPart(std::make_shared<Polygon>(0,0,0, 1,1,asteriodVertices,asteriodColor.r, asteriodColor.g, asteriodColor.b ));
    addPart(std::make_shared<Ellipse>(0,0,0, 3,3,asteriodColor.r, asteriodColor.g, asteriodColor.b ));
    setRelativeBoundingBox_(-3.0f, 3.0f, -3.0f, 3.0f);
    setAbsoluteBoundingBox_(-3.0f, 3.0f, -3.0f, 3.0f);
}


void Asteriod::updateAbsoluteBox_() const
{
    // std::cout << getX() << " | "<< getY() << std::endl;
	float selfXmin = getRelativeBox()->getXmin() + getX();
	float selfXmax = getRelativeBox()->getXmax() + getX();
	float selfYmin = getRelativeBox()->getYmin() + getY();
	float selfYmax = getRelativeBox()->getYmax() + getY();
	
	
	setAbsoluteBoundingBox_(selfXmin, selfXmax,
							selfYmin, selfYmax);
}