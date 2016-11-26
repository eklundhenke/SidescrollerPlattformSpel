#pragma once
#include "Scene.h"
#include "InputManager.h"
#include "Marker.h"
#include "Goal.h"
#include "SFMLTexture.h"
#include "SFMLText.h"
#include <chrono>
class GameOverScene : public Scene {
public:
  GameOverScene(InputManager& input); //Constructor
  void renderScene(SFMLRender* render, float deltaTime); //render logic
  SCENES updateScene(float deltaTime); //Scene logic
  std::chrono::high_resolution_clock::time_point start_time;
  //centers the text inside the buttons
  void centerText(SFMLText& text, SFMLSprite& sprite)
  {
    sf::FloatRect textRect = text.getGlobalBounds();
    sf::FloatRect spriteRect = sprite.getGlobalBounds();
    text.setPosition(spriteRect.left + (spriteRect.width/2)-(textRect.width/2),
     spriteRect.top + (spriteRect.height/2) - (textRect.height/2)-15);
  }

private:
  InputManager& inputmgr; //Provides access to inputs
  SFMLTexture backgroundTexture {"backgroundRect.png"};//rect background
  SFMLTexture keyTexture{"Items/keyYellow.png"}; //Button selecter
  //Non Marked Button Texture
  SFMLTexture buttonTextureNotMarked{"green_button_NotMarked.png"};
  //marked Button Texture
  SFMLTexture buttonTextureMarked{"green_button_marked.png"};


  SFMLText titelText{"Game Over",
  (float)(APPLICATION_WIDTH/2 - 200),40, 60}; //titel text
  SFMLText mainMenuText{"Main Menu",0,0, 35};
  SFMLText exitText{"Exit",0,0, 35};

  Marker keyMarker{keyTexture, 1,
   (float)(APPLICATION_WIDTH/2 - buttonTextureNotMarked.getSize().x + 70),
   (float)(buttonTextureNotMarked.getSize().y + 60) }; // button selector
// background
  SFMLSprite backgroundSprite{backgroundTexture,
   (float) (APPLICATION_WIDTH/2 - backgroundTexture.getSize().x/2), 30};
  //sigelplayer button sprite
  SFMLSprite mainMenuButton{buttonTextureMarked,
    (float)(APPLICATION_WIDTH/2 - buttonTextureNotMarked.getSize().x/2),
    (float)(buttonTextureNotMarked.getSize().y + 50)};
    //exit button sprite
  SFMLSprite exitButton{buttonTextureNotMarked,
   (float)(APPLICATION_WIDTH/2 - buttonTextureNotMarked.getSize().x/2),
    (float)(buttonTextureNotMarked.getSize().y *3 +50)};


};
