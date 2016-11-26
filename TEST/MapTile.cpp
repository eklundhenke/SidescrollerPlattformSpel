#include "MapTile.h"

MapTile::MapTile(SFMLTexture& TileTexture, float x, float y, int type, bool collision) : SFMLSprite{TileTexture, x, y}, collision{collision}
{
  if(type == 4) tileType = LOCKTILE;
}


bool MapTile::getCollision(){
  return collision;
}
void MapTile::setCollision(bool b){
  collision = b;
  if (b == false && tileType == LOCKTILE) setColor(sf::Color(255, 255, 255, 50));
}
