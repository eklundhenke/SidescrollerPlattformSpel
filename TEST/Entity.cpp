#include "Entity.h"

Entity::Entity(SFMLTexture& texture) : SFMLSprite{texture, 0, 0}{
  xVelocity = 0;
  yVelocity = 0;
}

void Entity::limitSpeed()
{
  if(xVelocity > getMax_Speed())
  {
    xVelocity = getMax_Speed();
  }
  if(xVelocity < -getMax_Speed())
  {
    xVelocity = -getMax_Speed();
  }
  if(yVelocity > getMax_Speed())
  {
    yVelocity = getMax_Speed();
  }
}

void Entity::moveRight(float deltaTime)
{
  //If the player was moving left, slow him down by 15 else accelerate by 60
  if(xVelocity < 0)
  {
    xVelocity += 60 * deltaTime;
  }
  else
  {
    xVelocity += 15 * deltaTime;
  }
}

void Entity::moveLeft(float deltaTime)
{
  //If the player was moving right, slow him down by 15 else accelerate by 60
  if(xVelocity > 0)
  {
    xVelocity -= 60 * deltaTime;
  }
  else
  {
    xVelocity -= 15 * deltaTime;
  }
}

//We are not moving in x axis, slow down
void Entity::retardX(float deltaTime)
{
  if(xVelocity > 0)
  {
    xVelocity -= 50 * deltaTime;
    if(xVelocity < 0)
    {
      xVelocity = 0;
    }
  }
  else if(xVelocity < 0)
  {
    xVelocity += 50 * deltaTime;
    if(xVelocity > 0)
    {
      xVelocity = 0;
    }
  }
}

void Entity::falling(float deltaTime)
{
  //Increase players speed downwards in y-axis
  yVelocity += 30 * deltaTime;
}

void Entity::jump()
{
  //Increase players speed upwards in y-axis
  yVelocity = -15;
}
