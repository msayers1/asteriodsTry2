// Ship.h
#ifndef SHIP_H
#define SHIP_H

#include "ComplexGraphicObject.h"
#include "AnimatedObject.h"
#include "Polygon.h"
#include "Rectangle.h"
#include "Ellipse.h"
#include "Missile.h"
namespace earshooter
{
	class Ship : public ComplexGraphicObject, public AnimatedObject
	{
		private:
		
		protected:
					
				void updateAbsoluteBox_() const;
		public:
			Ship();
			~Ship() = default;
			
			//disabled constructors & operators
			Ship(const Ship& obj) = delete;	// copy
			Ship(Ship&& obj) = delete;		// move
			Ship& operator = (const Ship& obj) = delete;	// copy operator
			Ship& operator = (Ship&& obj) = delete;			// move operator


			std::shared_ptr<Missile> Fire();
			void resetShip();
	};
}

#endif // SHIP_H
