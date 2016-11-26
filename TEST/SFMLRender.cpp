#include "SFMLRender.h"
#include "Scene.h"
#include "DebugInfo.h"
#include "SFML/Window/VideoMode.hpp"
#include "SFML/System/Vector2.hpp"
  SFMLRender::SFMLRender() : window{sf::VideoMode(APPLICATION_WIDTH, APPLICATION_HEIGHT), APPLICATION_NAME}{
    //window.setFramerateLimit(APPLICATION_LIMIT_FPS);
    window.setVerticalSyncEnabled(APPLICATION_VERTICAL_SYNC_ENABLE);
    window.setPosition(sf::Vector2<int>(sf::VideoMode::getDesktopMode().width/2-APPLICATION_WIDTH/2, sf::VideoMode::getDesktopMode().height/2-APPLICATION_HEIGHT/2));
    window.setView(screenView);
    window.setKeyRepeatEnabled(false);
  }

  bool SFMLRender::processEvents(){
    sf::Event event;
    while (window.pollEvent(event)){ //Loop through event queue
      if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) || event.type == sf::Event::Closed){ //If window X is clicked or ESCAPE is pressed
        return true;
      }
    }
    return false;
  }

  void SFMLRender::clearFrame(){ //Clears the frame
    window.clear();
  }

  void SFMLRender::displayFrame(){
    window.display();
  }

  void SFMLRender::drawFrame(Scene* current_scene, float deltaTime){
    current_scene->renderScene(this, deltaTime);
  }

  void SFMLRender::drawSprite(SFMLSprite& sprite){
    window.draw(sprite);
  }

  void SFMLRender::drawPlayer(Player& sprite){
    window.draw(sprite.displaySprite);
  }
  void SFMLRender::drawText(SFMLText& text){
    window.draw(text);
  }

  void SFMLRender::setCameraPosition(float x, float y){
    screenView.setCenter(x, y);
    window.setView(screenView);
  }

  sf::View& SFMLRender::getView(){
    return screenView;
  }

  /*sf::RenderWindow& SFMLRender::getWindow(){
    return window;
  }*/

  sf::Vector2f SFMLRender::screenPixelsToMapCord(int x, int y){

    return window.mapPixelToCoords({x,y});
  }

  void SFMLRender::closeWindow(){
    window.close();
  }

  bool SFMLRender::windowIsOpen(){
    return window.isOpen();
  }

  sf::Vector2<unsigned> SFMLRender::getWindowSize(){
    return window.getSize();
  }

  void SFMLRender::drawDebugInfo(DebugInfo& debug){
    debug.updateInfo(window, screenView);
    window.draw(debug.getTileRectangle());
    drawText(debug.getTileText());
  }
