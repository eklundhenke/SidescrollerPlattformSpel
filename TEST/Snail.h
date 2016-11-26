#pragma once
#include "Entity.h"
#include "Player.h"
#include <math.h>
class Snail : public Entity{
private:
  const float maxSpeed = 2;
  const int scaleFactor = 2; //We want big snails
  SFMLTexture& texture_walk1;
  SFMLTexture& texture_walk2;
  unsigned walkDistance;
  unsigned walkedDistance{0};
  bool moveRight;
  float animationTime{0};
  const float animationSpeed{0.5};
public:
  Snail(SFMLTexture& texture_walk1, SFMLTexture& texture_walk2, float x, float y, unsigned walkDistance, bool movetoright = false) : Entity(texture_walk1), texture_walk1{texture_walk1}, texture_walk2{texture_walk2},walkDistance{walkDistance}, moveRight{movetoright}
  {
    scale(scaleFactor,scaleFactor);
    setPosition(x, y-getGlobalBounds().height);
  };

  int logic(float deltaTime, Player& p1, Player& p2){

    //Simple animation
    animationTime += deltaTime;
    if(animationTime <= animationSpeed/2){
      flipped = false;
      setTexture(texture_walk1, true);
    }else if(animationTime <= animationSpeed){
      flipped = false;
      setTexture(texture_walk2, true);
    }else{
      animationTime = 0;
    }
    //Accelerate snail to left or right
    if(moveRight)
    {
      xVelocity +=  2 * deltaTime;
    }
    else
    {
      xVelocity -=  2 * deltaTime;
    }
    flipImage(xVelocity > 0); //Set image to face the right direction

    //Limit speed
    if(xVelocity > maxSpeed)
    {
      xVelocity = maxSpeed;
    }
    else if(xVelocity < maxSpeed * -1)
    {
      xVelocity = maxSpeed * -1;
    }

    walkedDistance += fabs(xVelocity); //float absolute value
    //Check if we should turn back
    if(walkedDistance > walkDistance){
      walkedDistance = 0;
      moveRight = !moveRight;
    }
    move(xVelocity, yVelocity);

    bool touched = false;
    if(p1.getGlobalBounds().intersects(getGlobalBounds())){
      touched = true;
    }
    if(p2.getGlobalBounds().intersects(getGlobalBounds())){
      if(touched) return 3;
      return 2;
    }
    if (touched) return 1;
    return 0;
  };

};
