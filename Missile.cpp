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
std::vector<std::pair<float,float>> Tip = {{0.0f,.18f}, {-.05f,.14f} ,{+.05f, .14f}};
std::vector<std::pair<float,float>> leftTailFin = {{0.0f,-.12f}, {-0.05f,-.16f},{-0.05f,-.2f},{0.0f,-.15f}};
std::vector<std::pair<float,float>> rightTailFin = {{0.0f,-.12f}, {0.05f,-.16f},{0.05f,-.2f},{0.0f,-.15f}};

Missile::Missile(float x, float y, float velocity, float angle)
    :ComplexGraphicObject(x, y, angle),
    AnimatedObject(x, y, angle, 0.f, 0.f, 0.f),
    Object({0.f,0.f}, 0.f)
{
    std::cout << x << " | " << y << " | " << angle << std::endl;
    setVelocity(velocity, angle);
    //Rectangle(float centerX, float centerY, float angle, float width, float height, float r, float g, float b);
    addPart(std::make_shared<Rectangle>(0,0,0, .02, .3,body.r, body.g, body.b ));
    
    addPart(std::make_shared<Polygon>(0,0,0, 1,1,Tip,body.r, body.g, body.b ));
    addPart(std::make_shared<Polygon>(0,0,0, 1,1,leftTailFin,fin.r, fin.g, fin.b ));
    addPart(std::make_shared<Polygon>(0,0,0, 1,1,rightTailFin,fin.r, fin.g, fin.b ));
    
}

Missile::Missile(float angle)
    :ComplexGraphicObject(0, 0, angle),
    AnimatedObject(0, 0, 0, 0, 0, 0),
    Object({0.f,0.f}, 0.f)
{
    //Rectangle(float centerX, float centerY, float angle, float width, float height, float r, float g, float b);
    addPart(std::make_shared<Rectangle>(0,0,0, .02,.3,body.r, body.g, body.b ));
    
    addPart(std::make_shared<Polygon>(0,0,0, 1,1,Tip,body.r, body.g, body.b ));
    addPart(std::make_shared<Polygon>(0,0,0, 1,1,leftTailFin,fin.r, fin.g, fin.b ));
    addPart(std::make_shared<Polygon>(0,0,0, 1,1,rightTailFin,fin.r, fin.g, fin.b ));
    
}

Missile::Missile()
    :ComplexGraphicObject(0.f, 0.f, 0.f),
    AnimatedObject(0.f,0.f, 0.f, 0.f,0.f, 0.f),
    Object({0.f,0.f}, 0.f)
{
    //Rectangle(float centerX, float centerY, float angle, float width, float height, float r, float g, float b);
    addPart(std::make_shared<Rectangle>(0,0,0, .02,.3,body.r, body.g, body.b ));
    
    addPart(std::make_shared<Polygon>(0,0,0, 1,1,Tip,body.r, body.g, body.b ));
    addPart(std::make_shared<Polygon>(0,0,0, 1,1,leftTailFin,fin.r, fin.g, fin.b ));
    addPart(std::make_shared<Polygon>(0,0,0, 1,1,rightTailFin,fin.r, fin.g, fin.b ));
    
}

