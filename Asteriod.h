// Asteriod.h
#ifndef ASTERIOD_H
#define ASTERIOD_H

#include "ComplexGraphicObject.h"
#include "AnimatedObject.h"
#include "Polygon.h"
#include "Rectangle.h"
#include "Ellipse.h"

namespace earshooter
{
	class Asteriod : public ComplexGraphicObject, public AnimatedObject
    {
        private:
        
    	protected:				
			void updateAbsoluteBox_() const;

        public:
            Asteriod(float x, float y, float velocity, float angle);
            ~Asteriod() = default;
            
            //disabled constructors & operators
            Asteriod(const Asteriod& obj) = delete;	// copy
            Asteriod(Asteriod&& obj) = delete;		// move
            Asteriod& operator = (const Asteriod& obj) = delete;	// copy operator
            Asteriod& operator = (Asteriod&& obj) = delete;			// move operator

    };
}
#endif // ASTERIOD_H
