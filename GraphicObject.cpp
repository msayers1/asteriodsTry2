//
//  GraphicObject.cpp
//  Template Project
//
//  Created by Jean-Yves Hervé on 2023-10-05.
//

#include <iostream>
#include "glPlatform.h"
#include "GraphicObject.h"

using namespace earshooter;
using namespace std;

bool GraphicObject::drawAbsoluteBoxes_ = false;
bool GraphicObject::drawRelativeBoxes_ = false;


GraphicObject::GraphicObject(float x, float y, float angle)
	:	Object(x, y, angle),
		absoluteBox_(nullptr),
		relativeBox_(nullptr)
{}

GraphicObject::GraphicObject(const WorldPoint& pt, float angle)
	:	Object(pt, angle),
		absoluteBox_(nullptr),
		relativeBox_(nullptr)
{}

void GraphicObject::draw() const
{
	draw_();

	//	Unfortunately, we are back in the parent reference frame, so we need to
	//	apply the object's relative transformation again
	if (drawAbsoluteBoxes_)
	{
		// forces an update of the box
		getAbsoluteBox();
		
		glPushMatrix();
		glTranslatef(getX(), getY(), 0.f);
		//	no rotation for the absolute box
		absoluteBox_->draw();
		glPopMatrix();
	}
	if (drawRelativeBoxes_ && relativeBox_ != nullptr)
	{
		glPushMatrix();
		glTranslatef(getX(), getY(), 0.f);
		glRotatef(getAngle(), 0.f, 0.f, 1.f);
		relativeBox_->draw();
		glPopMatrix();
	}
}

void GraphicObject::setAbsoluteBoundingBox_(float xmin, float xmax, float ymin, float ymax) const 
{
	if (absoluteBox_ != nullptr)
	{
		absoluteBox_->setDimensions(xmin, xmax, ymin, ymax);
	}
	else
	{
		absoluteBox_ = make_shared<BoundingBox>(xmin, xmax, ymin, ymax);
	}
}

void GraphicObject::setAbsoluteBoundingBox_(const WorldPoint& cornerUL, const WorldPoint& cornerLR) const 
{
	if (absoluteBox_ != nullptr)
	{
		absoluteBox_->setDimensions(cornerUL, cornerLR);
	}
	else
	{
		absoluteBox_ = make_shared<BoundingBox>(cornerUL, cornerLR);
	}
}

void GraphicObject::setRelativeBoundingBox_(float xmin, float xmax, float ymin, float ymax) const 
{
	if (relativeBox_ != nullptr)
	{
		relativeBox_->setDimensions(xmin, xmax, ymin, ymax);
	}
	else
	{
		relativeBox_ = make_shared<BoundingBox>(xmin, xmax, ymin, ymax);
	}
}

void GraphicObject::setRelativeBoundingBox_(const WorldPoint& cornerUL, const WorldPoint& cornerLR) const 
{
	if (relativeBox_ != nullptr)
	{
		relativeBox_->setDimensions(cornerUL, cornerLR);
	}
	else
	{
		relativeBox_ = make_shared<BoundingBox>(cornerUL, cornerLR);
	}
}


void GraphicObject::setAbsoluteBoundingBoxColor_(ColorIndex color) const 
{
	if (absoluteBox_ != nullptr)
	{
		absoluteBox_->setColor(color);
	}
}

void GraphicObject::setRelativeBoundingBoxColor_(ColorIndex color) const 
{
	if (relativeBox_ != nullptr)
	{
		relativeBox_->setColor(color);
	}
}

const std::shared_ptr<BoundingBox> GraphicObject::getAbsoluteBox() const
{
	if (absoluteBox_ == nullptr){
		// float selfXmin = relativeBox_->getXmin() + getX();
		// float selfXmax = relativeBox_->getXmax() + getX();
		// float selfYmin = relativeBox_->getYmin() + getY();
		// float selfYmax = relativeBox_->getYmax() + getY();
		// absoluteBox_ = make_shared<BoundingBox>(selfXmin,selfXmax,selfYmin,selfYmax);
		absoluteBox_ = make_shared<BoundingBox>();
	}
	
		
		
	updateAbsoluteBox_();

	return absoluteBox_;
}

void GraphicObject::updateAbsoluteBox_() const
{
	float selfXmin = relativeBox_->getXmin() + getX();
	float selfXmax = relativeBox_->getXmax() + getX();
	float selfYmin = relativeBox_->getYmin() + getY();
	float selfYmax = relativeBox_->getYmax() + getY();
	float width = selfXmax - selfXmin;
	float height = selfYmax - selfYmin;
	float ca = cosf(getAngleRad()), sa = sinf(getAngleRad());
	float x1 = +0.5f * (ca*width + sa*height),
		  x2 = +0.5f * (ca*width - sa*height),
		  x3 = -x1,
		  x4 = -x2;
	float y1 = +0.5f * (sa*width + ca*height),
		  y2 = +0.5f * (sa*width - ca*height),
		  y3 = -y1,
		  y4 = -y2;
	// cout << "Update" << " | " << getX() << " | " << getY() << " | " << x1 << " | " << x2 << " | " << x3 << " | " << x4 << " | " << y1 << " | " << y2 << " | " << y3 << " | " << y4 << endl;

	setAbsoluteBoundingBox_(min(min(min(x1, x2), x3), x4), max(max(max(x1, x2), x3), x4),
							min(min(min(y1, y2), y3), y4), max(max(max(y1, y2), y3), y4));
}

bool GraphicObject::collision(std::shared_ptr<BoundingBox> otherBB){
	// cout << "Check: " << (absoluteBox_->getYmax() < otherBB->getYmin() || absoluteBox_->getYmin() < otherBB->getYmax()) << " | " << getX() << " | " << getY() << " | " << absoluteBox_->getYmax() << " | " << otherBB->getYmin() << " | " << absoluteBox_->getYmin() << " | " << otherBB->getYmax() << " | " <<  (absoluteBox_->getXmax() < otherBB->getXmin() || absoluteBox_->getXmin() < otherBB->getXmax()) << " | " <<  absoluteBox_->getXmax() << " | " <<  otherBB->getXmin() << " | " <<  absoluteBox_->getXmin() << " | " <<  otherBB->getXmax() << endl;
	// WorldPoint selfUL = (*relativeBox_).getCornerUL(); // max y min x
	// WorldPoint selfLR = (*relativeBox_).getCornerLR(); // min y max x
	// WorldPoint otherUL = (*otherBB).getCornerUL();
	// // WorldPoint otherLR = (*otherBB).getCornerLR();
	// float selfXmin = relativeBox_->getXmin() + getX();
	// float selfXmax = relativeBox_->getXmax() + getX();
	// float selfYmin = relativeBox_->getYmin() + getY();
	// float selfYmax = relativeBox_->getYmax() + getY();
	updateAbsoluteBox_();
	if(absoluteBox_->getYmax() < otherBB->getYmin() || absoluteBox_->getYmin() > otherBB->getYmax()){
		return false;
	}
	if(absoluteBox_->getXmax() < otherBB->getXmin() || absoluteBox_->getXmin() > otherBB->getXmax()){
		return false;
	}
	return true;
}
