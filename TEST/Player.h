#pragma once
#include "Entity.h"
#include <cmath>
class SFMLRender;
class Player : public Entity{
friend SFMLRender;
private:
	int HP{3};
	int tmp_x;
	int tmp_y;
	bool playerStuck{false};
	SFMLTexture& textureStand;
	SFMLTexture& textureJump;
	SFMLTexture (&textureWalk)[11];
	int oneortwo;
	int stuckRight;
	bool dead{false};
  float animationTime{0};
  const float animationSpeed{2};
	SFMLSprite displaySprite{*this};
public:
  Player(SFMLTexture& texture_stand, SFMLTexture& texture_jump, SFMLTexture (&texture_walk)[11], float x, float y, int oneortwo) : Entity{texture_stand}, textureStand{texture_stand}, textureJump{texture_jump}, textureWalk{texture_walk}, oneortwo{oneortwo}{
    setPosition(x, y);
		getTmp_x() = x;
		getTmp_y() = y;
  };
  int getOneorTwo(){return oneortwo;};
	int &getHP(){return HP;};
	int &getTmp_x(){return tmp_x;};
	int &getTmp_y(){return tmp_y;};
	bool &getPlayerStuck(){return playerStuck;};
	int &getStuckRight(){return stuckRight;};
	bool &getDead(){return dead;};
	void flipImage(bool flip)
	{
		if(flip && !flipped)
		{
			displaySprite.setTextureRect(sf::IntRect(displaySprite.getLocalBounds().width, 0, displaySprite.getLocalBounds().width * -1, displaySprite.getLocalBounds().height));
		}else if(!flip && flipped){
			displaySprite.setTextureRect(sf::IntRect(0, 0, displaySprite.getLocalBounds().width, displaySprite.getLocalBounds().height));
		}
		flipped = flip;
	}
void updateTexture(float deltaTime){
	displaySprite.setPosition(getPosition());
	bool lastFlip = flipped;
	if(fabs(yVelocity) > 3)
	{
		displaySprite.setTexture(textureJump, true);
		flipped = false;
		animationTime = 0;
	}else{
		if(xVelocity == 0)
		{
			displaySprite.setTexture(textureStand, true);
			flipped = false;
			animationTime = 0;
		}else{
			animationTime += deltaTime;
			if(animationTime > animationSpeed) animationTime = 0;
			int arraySize = (sizeof(textureWalk) / sizeof(textureWalk[0]) -1);
			if (arraySize < 0) arraySize = 0;
			int animIndex = (animationTime / animationSpeed) * arraySize;
			flipped = false;
			displaySprite.setTexture(textureWalk[animIndex], true);
		}
	}
		if(xVelocity != 0){
		flipImage(xVelocity < 0);
	}else{
		flipImage(lastFlip);
	}
};
protected:


};
