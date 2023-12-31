//
//  ComplexGraphicObject.cpp
//  Template Project
//
//  Created by Jean-Yves Hervé on 2023-10-05.
//

#include <stdio.h>

#include <cmath>
#include <iostream>
#include "glPlatform.h"
#include "ComplexGraphicObject.h"


using namespace std;
using namespace earshooter;

ComplexGraphicObject::ComplexGraphicObject(const WorldPoint& pt, float angle)
	:	Object(pt, angle),
		GraphicObject(pt, angle)
{
	float maxX, maxY, minX, minY;
	if(partList_.size() > 0){
		std::shared_ptr<BoundingBox> boundingBox = partList_[0]->getRelativeBox();
		maxX = boundingBox->getXmax();
		maxY = boundingBox->getYmax();
		minX = boundingBox->getXmin();
		minY = boundingBox->getYmin();
		if(partList_.size() > 1){
			for(auto obj: partList_){
				boundingBox = partList_[0]->getRelativeBox();
				float nextMaxX = boundingBox->getXmax();
				float nextMaxY = boundingBox->getYmax();
				float nextMinX = boundingBox->getXmin();
				float nextMinY = boundingBox->getYmin();

				maxX = max(nextMaxX, maxX);
				maxY = max(nextMaxY,maxY);
				minX = min(nextMinX,minX);
				minY = min(nextMinY,minY);
			}
		}
	}
	

	// cout << minX << " | " <<  maxX << " | " <<  minY << " | " <<  maxY << endl;
	setRelativeBoundingBox_(minX, maxX, minY, minY);
	
}
ComplexGraphicObject::ComplexGraphicObject(float x, float y, float angle)
	:	Object(x, y, angle),
		GraphicObject(x, y, angle)
{
}

void ComplexGraphicObject::addPart(shared_ptr<GraphicObject> part)
{
	partList_.push_back(part);
}


void ComplexGraphicObject::draw_() const
{
	//	save the current coordinate system (origin, axes, scale)
	glPushMatrix();
	
	//	move to the center of the disk
	glTranslatef(getX(), getY(), 0.f);
	glRotatef(getAngle(), 0.f, 0.f, 1.f);
		
	for (auto obj : partList_)
		obj->draw();
		
	//	restore the original coordinate system (origin, axes, scale)
	glPopMatrix();
}

bool ComplexGraphicObject::isInside(const WorldPoint& pt) const
{
	bool check = false;
	//std::cout << "Inside Complex Graphic Object isInside: " <<  pt.x << "," <<  pt.y << " | " <<  getX() << "," <<  getY() << std::endl;
	WorldPoint localPt = {(pt.x - getX()), pt.y - getY()};
	// return false;
	// bool insideSelf;
	// std::shared_ptr<BoundingBox> boundingBox = getRelativeBox();
	// float height = boundingBox->getYmax() - boundingBox->getYmin();
	// float width = boundingBox->getXmax(); - boundingBox->getXmin();

	// float dx = pt.x - getX(), dy = pt.y - getY();
	// 	if (getAngle() != 0.f)
	// 	{
	// 		float ca = cosf(getAngle()), sa = sinf(getAngle());
	// 		float rdx = ca * dx + sa*dy;
	// 		float rdy = -sa *dx + ca*dy;
	// 		std::cout << "Inside Rectangle with Angle isInside: " << ((rdx >= -width/2 ) && (rdx <= width/2 ) &&
	// 			(rdy >= -height/2 ) && (rdy <= +height/2 )) << " | " << rdx << "," << rdy << " | " << width << "," << height << " | " << ca << "," << sa << " | " << pt.x << "," <<  pt.y << std::endl;
		
	// 		insideSelf = (rdx >= -width/2 ) && (rdx <= width/2 ) &&
	// 			(rdy >= -height/2 ) && (rdy <= +height/2 );
		
	// 	}
	// 	else
	// 		std::cout << "Inside Rectangle without Angle isInside: " << ((pt.x >= getX() - width/2 ) && (pt.x <= getX() + width/2 ) &&
	// 			(pt.y >= getY() - height/2 ) && (pt.y <= getY() + height/2 )) << " | " << getX() << "," << getY() << " | " << width << "," << height << " | " << pt.x << "," <<  pt.y << std::endl;
	// 		insideSelf = (pt.x >= getX() - width/2 ) && (pt.x <= getX() + width/2 ) &&
	// 			(pt.y >= getY() - height/2 ) && (pt.y <= getY() + height/2 );

	// if(insideSelf){
		for (auto obj : partList_)
			check = check || obj->isInside(localPt);
		return check;
	// } else {
	// 	return false;
	// }
		
}

