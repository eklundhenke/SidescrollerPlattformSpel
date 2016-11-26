#pragma once
#include "SFML/Window/Mouse.hpp"
#include "SFML/Graphics/View.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include "GameScene.h"
#include "MapTile.h"
#include "Constants.h"
#include "math.h"
class DebugInfo{
private:
  GameScene* game_ptr{nullptr};
  SFMLText tileInfoText{"N/A", 0, 0, 20};
  sf::RectangleShape rectangle{};
public:
  DebugInfo(){
    rectangle.setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
    rectangle.setPosition(-200, -200);
  }
  void setGameScenePtr(GameScene* ptr){game_ptr = ptr;}

  void updateInfo(sf::RenderWindow& window, sf::View& camera){
    if(game_ptr == nullptr) return;
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mapCords = window.mapPixelToCoords({mousePos.x,mousePos.y});
    MapTile* tile = game_ptr->mapmgr.getTilePtrAtPosition(mapCords.x, mapCords.y);
    if (tile == nullptr) return;
    tileInfoText.setString("(" + std::to_string((int)tile->getPosition().x/70) + "," + std::to_string((int)tile->getPosition().y/70) + ") - cords " + std::to_string((int)mapCords.x) + " , " + std::to_string((int)mapCords.y));
    tileInfoText.setPosition(mapCords.x, mapCords.y);
    rectangle.setPosition(tile->getPosition().x,tile->getPosition().y);

  }

  SFMLText& getTileText(){return tileInfoText;}
  sf::RectangleShape& getTileRectangle(){return rectangle;};
};
