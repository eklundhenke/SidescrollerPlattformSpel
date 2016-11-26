#pragma once
#include "Constants.h"
#include "SFML/Graphics.hpp"
#include "SFMLSprite.h"
#include "SFMLText.h"
#include "Player.h"
#include "DebugInfo.h"
class Scene;
class SFMLRender {

private:
  sf::RenderWindow window; //window
  sf::View screenView{sf::FloatRect{0, 0, APPLICATION_WIDTH, APPLICATION_HEIGHT}} ; //Camera
public:
  SFMLRender();

  bool processEvents(); //Process all inputEvents and returns true if user has requested to exit the program

  void clearFrame(); //Clear old frame

  void displayFrame(); //Display frame

  void drawFrame(Scene* current_scene, float deltaTime); //Draw current scene

  void drawSprite(SFMLSprite& sprite); //Draw a single sprite
  void drawPlayer(Player& sprite);
  void drawText(SFMLText& text); //Draw a text

  void setCameraPosition(float x, float y); //Set camera position

  sf::View& getView(); //Returns camera object

  bool windowIsOpen(); //True if window is open

  void closeWindow(); //Close window

  sf::Vector2<unsigned> getWindowSize();

  sf::Vector2f screenPixelsToMapCord(int x, int y); //Converts screencords to map cords based on camera.

  void drawDebugInfo(DebugInfo& debug);
};
