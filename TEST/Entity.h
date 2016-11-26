#pragma once
#include "SFMLSprite.h"
#include "SFMLTexture.h"
#include "Constants.h"
class Entity : public SFMLSprite{
private:
  const int max_speed{10};
public:
  float xVelocity, yVelocity = 0; //Velocity
  bool isFalling{false};
  void updateTexture();
  void limitSpeed();
  const int getMax_Speed(){return max_speed;};
  void moveRight(float deltaTime);
  void moveLeft(float deltaTime);
  void retardX(float deltaTime);
  void falling(float deltaTime);
  void jump();
protected:
  bool flipped = false;
  Entity(SFMLTexture& texture);
  virtual void flipImage(bool flip)
  {
    if(flip && !flipped)
    {
      setTextureRect(sf::IntRect(getLocalBounds().width, 0, getLocalBounds().width * -1, getLocalBounds().height));
    }else if(!flip && flipped){
      setTextureRect(sf::IntRect(0, 0, getLocalBounds().width, getLocalBounds().height));
    }
    flipped = flip;
  }
};
