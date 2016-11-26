#include "Entity.h"
#include "Player.h"
#include <math.h>
class Coin : public Entity{
private:
  bool remove{false};
public:
  Coin(SFMLTexture& coin, float x, float y) : Entity(coin)
  {
    setPosition(x, y-getGlobalBounds().height);
  };
  bool &removeCoin(){return remove;};
  int logic(Player& p1, Player& p2)
  {
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
  }
};
