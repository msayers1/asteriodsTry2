//
//   Polygon.cpp
//   Prog01Version1
//
//   
//  Hope for being able to do different polygons. 
//
//   Created by Michael Sayers on 9/22/2023 
//   Modified from Class Code Examples from CS406 Jean-Yves Hervé
//

#include <cmath>
#include <vector>
#include <utility>
#include <iostream>
#include "glPlatform.h"
#include "Polygon.h"
#include "World.h"

using namespace std;
using namespace earshooter;

//Basic sequence of vertices to create a polygon. 
Polygon::Polygon(float centerX, float centerY, float angle, float scaleX, float scaleY,std::vector<std::pair<float,float>> vertexVector,
				float red, float green, float blue)
	:	GraphicObject(centerX, centerY, angle),
		Object(centerX,centerY,angle),
		_scaleX(scaleX),
		_scaleY(scaleY),
        _vertexVector(vertexVector),
		_red(red),
		_green(green),
		_blue(blue)
{
	float maxX = vertexVector[0].first;
	float maxY = vertexVector[0].second;
	float minX = vertexVector[0].first;
	float minY = vertexVector[0].second;
	for(pair<float,float> coord : vertexVector){
		maxX = max(coord.first,maxX);
		maxY = max(coord.second,maxY);
		minX = min(coord.first,minX);
		minY = min(coord.second,minY);
	}

	// cout << minX << " | " <<  maxX << " | " <<  minY << " | " <<  maxY << endl;
	setRelativeBoundingBox_(minX, maxX, minY, minY);
}
//Implementiation of different shapes like lines. 
// Polygon::Polygon(float centerX, float centerY, float angle, float scaleX, float scaleY,std::vector<std::pair<float,float>> vertexVector,
// 				float red, float green, float blue, int type, float thickness)
// 	:	GraphicObject(centerX, centerY, angle),
// 		_red(red), 
// 		_green(green), 
// 		_blue(blue),
//         _vertexVector(vertexVector),
//         _type(type),
//         _thickness(thickness),
//         _modification(sqrt(pow(thickness,2)/2))
// {
// }
Polygon::~Polygon()
{

}

void Polygon::draw_() const
{
	//	save the current coordinate system (origin, axes, scale)
	glPushMatrix();
	
	//	move to the center of the disk
	glTranslatef(getX(), getY(), 0.f);
		
	// apply rotation
	glRotatef(getAngle(), 0.f, 0.f, 1.f);
	
	//	apply the  scale
	// glScalef(getScaleX(), getScaleY(), 1.f);
	glScalef(_scaleX, _scaleY, 1.f);
	
	glColor3f(_red, _green, _blue);
	glBegin(GL_POLYGON);
			for (int k=0; k<_vertexVector.size(); k++)
				glVertex2f(_vertexVector[k].first,
						   _vertexVector[k].second);
	glEnd();
	
	//	restore the original coordinate system (origin, axes, scale)
	glPopMatrix();
}


bool Polygon::isInside(const WorldPoint& pt) const
{
	float dx = pt.x - getX(), dy = pt.y - getY();
	if (getAngle() != 0.f)
	{
		float ca = cosf(getAngle()), sa = sinf(getAngle());
		float rdx = ca * dx + sa*dy;
		float rdy = -sa *dx + ca*dy;
		// std::cout << "Inside Polygon with Angle isInside: " << ((rdx >= -width_/2 ) && (rdx <= width_/2 ) && (rdy >= -height_/2 ) && (rdy <= +height_/2 )) << " | " << rdx << "," << rdy << " | " << width_ << "," << height_ << " | " << ca << "," << sa << " | " << pt.x << "," <<  pt.y << std::endl;
	
		return (rdx >= -width_/2 ) && (rdx <= width_/2 ) &&
			   (rdy >= -height_/2 ) && (rdy <= +height_/2 );
	
	}
	else
		// std::cout << "Inside Polygon without Angle isInside: " << ((pt.x >= getX() - width_/2 ) && (pt.x <= getX() + width_/2 ) && (pt.y >= getY() - height_/2 ) && (pt.y <= getY() + height_/2 )) << " | " << getX() << "," << getY() << " | " << width_ << "," << height_ << " | " << pt.x << "," <<  pt.y << std::endl;
		return (pt.x >= getX() - width_/2 ) && (pt.x <= getX() + width_/2 ) &&
			   (pt.y >= getY() - height_/2 ) && (pt.y <= getY() + height_/2 );
}

void Polygon::updateAbsoluteBox_() const
{
	//	I could probably do it smarter/faster if I took the time to
	//	think about it, but I am being lazy :-)
	float ca = cosf(getAngleRad()), sa = sinf(getAngleRad());
	float x1 = +0.5f * (ca*width_ + sa*height_),
		  x2 = +0.5f * (ca*width_ - sa*height_),
		  x3 = -x1,
		  x4 = -x2;
	float y1 = +0.5f * (sa*width_ + ca*height_),
		  y2 = +0.5f * (sa*width_ - ca*height_),
		  y3 = -y1,
		  y4 = -y2;
	setAbsoluteBoundingBox_(min(min(min(x1, x2), x3), x4), max(max(max(x1, x2), x3), x4),
							min(min(min(y1, y2), y3), y4), max(max(max(y1, y2), y3), y4));
}