#ifndef GAME_H
#define GAME_H

#include <cmath>


class Game {
    private:
        int score_, lives_;
        float shipStructuralIntegrity_;
		bool gameStatus_;
    public:
        Game();
		
        virtual ~Game() = default;
        
        //disabled constructors & operators
		Game(const Game& obj) = delete;	// copy
		Game(Game&& obj) = delete;		// move
		Game& operator = (const Game& obj) = delete;	// copy operator
		Game& operator = (Game&& obj) = delete;		// move operator

		inline void resetGame()
		{
			//give a flag for running the game and stopping the game when 0 lives. 
			gameStatus_ = true;
			score_ = 0;
    		lives_ = 3;
    		shipStructuralIntegrity_ = 100;
		}

		inline bool getGameStatus() const
		{
			//give a flag for running the game and stopping the game when 0 lives. 
			return gameStatus_;
		}

		inline void stopGame()
		{
			//give a flag for running the game and stopping the game when 0 lives. 
			gameStatus_ = false;
		}
        inline float getScore() const
		{
			return score_;
		}
		
		inline void increaseScore(int points)
		{
			score_ = score_ + points;
            if(score_ % 1000 == 0){
                setLives(1);
            }
		}
        inline float getLives() const
		{
			return lives_;
		}
		
		inline void setLives(int liveAdjustment)
		{
			lives_ = lives_ + liveAdjustment;
			if(lives_ == 0){
				stopGame();
			}
				//Game Over
		}

        inline float getShipStructuralIntegrity() const
		{
			return shipStructuralIntegrity_;
		}
		
		inline void setShipStructuralIntegrity(int damage)
		{
			shipStructuralIntegrity_ = shipStructuralIntegrity_ - damage;
			if(shipStructuralIntegrity_ == 0){
				setLives(-1);
				if(lives_ > 0)
				resetShipStructuralIntegrity();
			}
				
		}

		inline void resetShipStructuralIntegrity()
		{
			shipStructuralIntegrity_ = 100;
				
		}

};

#endif  //  GAME_H