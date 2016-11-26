#pragma once
#include "MapTile.h"
#include "Entity.h"
class Key : public Entity{

private:
  MapTile* t1{nullptr};
  MapTile* t2{nullptr};
  MapTile* t3{nullptr};
  bool keyUsed{false};
public:
  Key(SFMLTexture& texture, float x, float y, MapTile* t1, MapTile* t2 = nullptr, MapTile* t3 = nullptr) : Entity{texture}, t1{t1}, t2{t2}, t3{t3}{
    setPosition(x, y);
  }

  bool isUsed(){return keyUsed;}

  void logic(Player& p1, Player& p2)
  {
    if (keyUsed) return;
    if (p1.getGlobalBounds().intersects(getGlobalBounds()) || p2.getGlobalBounds().intersects(getGlobalBounds()))
    {
      if(t1 != nullptr) t1->setCollision(false);
      if(t2 != nullptr) t2->setCollision(false);
      if(t3 != nullptr) t3->setCollision(false);
      keyUsed = true;
    }

  }
};
