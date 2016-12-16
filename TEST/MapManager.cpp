#include "MapManager.h"
#include "fstream"
#include "SFMLRender.h"
#include "Constants.h"
MapManager::MapManager(std::string filePath){
  loadMapFromFile(filePath);
}

void MapManager::loadMapFromFile(std::string filePath){
  for (auto it = mapTiles.begin(); it != mapTiles.end(); ++it){
    delete it->second;
  }
  mapTiles.clear();
  std::ifstream file;
  file.open("map.txt", std::ifstream::in);
  int type;
  int x = 0, y = 0;
  int tileCount = 0;
  if(file.is_open()){
    while(file >> type){
      if(type != 0)
      {
        bool collision = !(type == 3);
        mapTiles.emplace(std::pair<int, int>{x,y}, new MapTile{tileTexture[type-1],x*TILE_SIZE,y*TILE_SIZE,type,collision});
        tileCount++;
      }
      if(file.peek() == '\n')
      {
        x = 0;
        y += 1;
      }
      else
      {
        x += 1;
      }
    }
    file.close();
  }else{
    std::cout << "Couldn't open map file " + filePath << std::endl;
  }
  std::cout << "Loaded " << tileCount << " tiles" << std::endl;
}

void MapManager::renderMap(SFMLRender* render){
  for (auto it = mapTiles.begin(); it != mapTiles.end(); ++it){
    render->drawSprite(*(it->second));
  }
}

void MapManager::checkMapCollision(Player& player, float deltaTime){
  sf::Vector2<float> oldPosition = player.getPosition();
  player.move(player.xVelocity, 0); //Move x
  if(tilemap_collisionCheck(player.getGlobalBounds())){
    player.setPosition(oldPosition);
    player.xVelocity = 0;
  }
  oldPosition = player.getPosition();
  player.move(0, player.yVelocity); //Move y
  if(tilemap_collisionCheck(player.getGlobalBounds())){
    player.setPosition(oldPosition);
    if(player.yVelocity >0){

      player.isFalling = false;
    }
    player.yVelocity = 0;
  }else{
    player.isFalling = true;
  }
}

bool MapManager::checkTileAtPosition(float x, float y){
  int a = x / TILE_SIZE;
  int b = y / TILE_SIZE;

  auto it = mapTiles.find(std::pair<int, int>(a, b));
  if(it != mapTiles.end() && it->second->getCollision()) {
    return true;
  }
  return false;
}

bool MapManager::tilemap_collisionCheck(sf::Rect<float> playerRect){
  float x = playerRect.left;
  float y = playerRect.top;
  float w = playerRect.width;
  float h = playerRect.height;

  return checkTileAtPosition(x, y) || checkTileAtPosition(x+w, y) || checkTileAtPosition(x, y+h) || checkTileAtPosition(x+w, y+h) || checkTileAtPosition(x, y+h/2) || checkTileAtPosition(x+w, y+h/2);
}

MapTile* MapManager::getTilePtrAtPosition(float x, float y){
  int a = x / TILE_SIZE;
  int b = y / TILE_SIZE;

  auto it = mapTiles.find(std::pair<int, int>(a, b));
  if(it != mapTiles.end() && it->second->getCollision()) {
    return it->second;
  }
  return nullptr;
}
