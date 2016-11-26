#pragma once
#include "Player.h"
#include "Entity.h"
class Goal : public Entity
  {

private:
bool goal = false;
public:
  Goal(SFMLTexture& texture, float x, float y) : Entity{texture}
  {
    setPosition(x, y);
  };

  bool logic(Player& p1, Player& p2)
  {
    if (p1.getGlobalBounds().intersects(getGlobalBounds()) || p2.getGlobalBounds().intersects(getGlobalBounds()))
    {
      return true;
    }
    return false;
  }
  bool getGoal(){return goal;}
  void setGoal(bool set) {goal = set;}

};
