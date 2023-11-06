// Missile.h
#ifndef MISSILE_H
#define MISSILE_H

#include "ComplexGraphicObject.h"
#include "AnimatedObject.h"
#include "Polygon.h"
#include "Rectangle.h"
#include "Ellipse.h"

namespace earshooter
{
	class Missile : public ComplexGraphicObject, public AnimatedObject
	{
		private:
			time_t birthTime_;
		
		protected:
					
				void updateAbsoluteBox_() const;
		public:
			Missile(float x, float y, float velocity, float angle);
			Missile(float angle);
			Missile();
			~Missile() = default;
			
			//disabled constructors & operators
			Missile(const Missile& obj) = delete;	// copy
			Missile(Missile&& obj) = delete;		// move
			Missile& operator = (const Missile& obj) = delete;	// copy operator
			Missile& operator = (Missile&& obj) = delete;			// move operator

			// Returns the Tip of the missile as a world point. 
			WorldPoint TipWorldPoint();
			bool checkFuel();

	};
}
#endif // MISSILE_H
