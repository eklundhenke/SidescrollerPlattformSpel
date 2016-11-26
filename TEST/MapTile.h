#pragma once
#include "SFMLSprite.h"
#include "Constants.h"
class MapTile : public SFMLSprite{
public:

  MapTile(SFMLTexture& TileTexture, float x, float y, int type, bool collision); //Constructor
  //int getType(){return tileType;};
  bool getCollision();
  void setCollision(bool b);
private:
  enum TILE_BEHAVIOR {NORMAL = 0, LOCKTILE = 4};
  bool collision{false};
  TILE_BEHAVIOR tileType{NORMAL};
};
