// Missile.cpp
#include <iostream>
#include <vector>
#include "Missile.h"
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

Color body = {.37f, .38f, .39f};
Color fin = {.41f, .435f, .70f};
std::vector<std::pair<float,float>> Tip = {{0.0f,0.9f}, {-.25f,0.7f} ,{+.25f, 0.7f}};
std::vector<std::pair<float,float>> leftTailFin = {{0.0f,-0.6f}, {-0.25f,-0.8f},{-0.25f,-1.0f},{0.0f,-0.75f}};
std::vector<std::pair<float,float>> rightTailFin = {{0.0f,-0.6f}, {0.0f,-0.75f}, {0.25f,-1.0f},{0.25f,-0.8f}};

Missile::Missile(float x, float y, float velocity, float angle)
    :ComplexGraphicObject(x, y, angle),
    AnimatedObject(x, y, angle, 0.f, 0.f, 0.f),
    Object({x,y}, angle),
    birthTime_(time(nullptr))
{
    // std::cout << x << " | " << y << " | " << angle << std::endl;
    setVelocity(velocity, angle + 90);
    //Rectangle(float centerX, float centerY, float angle, float width, float height, float r, float g, float b);
    addPart(std::make_shared<Rectangle>(0,0,0, .1, 1.5f,body.r, body.g, body.b ));
    
    addPart(std::make_shared<Polygon>(0,0,0, 1,1,Tip,body.r, body.g, body.b ));
    addPart(std::make_shared<Polygon>(0,0,0, 1,1,leftTailFin,fin.r, fin.g, fin.b ));
    addPart(std::make_shared<Polygon>(0,0,0, 1,1,rightTailFin,fin.r, fin.g, fin.b ));
    setRelativeBoundingBox_(-.25f, .25f, -1.0f, .9f);
    setAbsoluteBoundingBox_(-.25f, .25f, -1.0f, .9f);
}

Missile::Missile(float angle)
    :ComplexGraphicObject(0, 0, angle),
    AnimatedObject(0, 0, 0, 0, 0, 0),
    Object({0.f,0.f}, 0.f),
    birthTime_(time(nullptr))
{
    //Rectangle(float centerX, float centerY, float angle, float width, float height, float r, float g, float b);
    addPart(std::make_shared<Rectangle>(0,0,0, .02,.3,body.r, body.g, body.b ));
    
    addPart(std::make_shared<Polygon>(0,0,0, 1,1,Tip,body.r, body.g, body.b ));
    addPart(std::make_shared<Polygon>(0,0,0, 1,1,leftTailFin,fin.r, fin.g, fin.b ));
    addPart(std::make_shared<Polygon>(0,0,0, 1,1,rightTailFin,fin.r, fin.g, fin.b ));
    setRelativeBoundingBox_(-.25f, .25f, -1.0f, .9f);
    setAbsoluteBoundingBox_(-.25f, .25f, -1.0f, .9f);
}

Missile::Missile()
    :ComplexGraphicObject(0.f, 0.f, 0.f),
    AnimatedObject(0.f,0.f, 0.f, 0.f,0.f, 0.f),
    Object({0.f,0.f}, 0.f),
    birthTime_(time(nullptr))
{
    //Rectangle(float centerX, float centerY, float angle, float width, float height, float r, float g, float b);
    addPart(std::make_shared<Rectangle>(0,0,0, .02,.3,body.r, body.g, body.b ));
    
    addPart(std::make_shared<Polygon>(0,0,0, 1,1,Tip,body.r, body.g, body.b ));
    addPart(std::make_shared<Polygon>(0,0,0, 1,1,leftTailFin,fin.r, fin.g, fin.b ));
    addPart(std::make_shared<Polygon>(0,0,0, 1,1,rightTailFin,fin.r, fin.g, fin.b ));
    setRelativeBoundingBox_(-.25f, .25f, -1.0f, .9f);
    setAbsoluteBoundingBox_(-.25f, .25f, -1.0f, .9f);
}

bool Missile::checkFuel(){
    if(5 < (static_cast<int>(time(nullptr)-birthTime_))){
        return true;
    } else {
        return false;
    }
}


WorldPoint  Missile::TipWorldPoint(){
    float rad_angle = (getAngle() + 90) * (M_PI/180);
    float x = getX() + .9 * cosf(rad_angle);
    float y = getY() + .9 * sinf(rad_angle);
    WorldPoint tip = {x, y};
    return tip;
}

void Missile::updateAbsoluteBox_() const
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