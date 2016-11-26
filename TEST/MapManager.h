#pragma once
#include "MapTile.h"
#include "map"
#include "string"
#include "SFMLTexture.h"
#include "Entity.h"
#include "Constants.h"
#include "Player.h"
class SFMLRender;
class MapManager{
public:
  MapManager(std::string filePath);
  void loadMapFromFile(std::string filePath); //Loads map from file
  void renderMap(SFMLRender* render); //Renders the map
  void checkMapCollision(Player& entity, float deltaTime); //Used to check if player is falling
  bool tilemap_collisionCheck(sf::Rect<float> playerRect);
  bool checkTileAtPosition(float x, float y);
  MapTile* getTilePtrAtPosition(float x, float y);
private:
  std::map<std::pair<int, int>, MapTile*> mapTiles; //Save all maptiles

  //Tile textures, note that the order is important!
  SFMLTexture tileTexture[5] = {SFMLTexture{"Tiles/grassMid.png"}, SFMLTexture{"Tiles/grassCenter.png"} ,SFMLTexture{"Tiles/signRight.png"}, SFMLTexture{"Tiles/lock_blue.png"}, SFMLTexture{"Tiles/door_closedMid.png"}};

};
