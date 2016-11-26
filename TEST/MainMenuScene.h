#pragma once
#include "Scene.h"
#include "InputManager.h"
#include "Marker.h"
#include "SFMLTexture.h"
#include "SFMLText.h"
#include <chrono>
class MainMenuScene : public Scene {
public:
  MainMenuScene(InputManager& input); //Constructor
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
  SFMLTexture backgroundTexture{"background.png"};
  SFMLTexture keyTexture{"Items/keyYellow.png"}; //Button selecter
  //Non Marked Button Texture
  SFMLTexture buttonTextureNotMarked{"green_button_NotMarked.png"};
  //marked Button Texture
  SFMLTexture buttonTextureMarked{"green_button_marked.png"};


  SFMLText titelText{"Choose an option",
  (float)(APPLICATION_WIDTH/2-325),30 ,60};// titel text
	SFMLText singelPlayerText{"Single Player",0,0, 35};
	SFMLText multiPlayerText{"Multiplayer",0,0, 35};
	SFMLText exitText{"Exit",0,0, 35};

	Marker keyMarker{keyTexture, 1,
	 (float)(APPLICATION_WIDTH/2 - buttonTextureNotMarked.getSize().x + 70),
	 (float)(buttonTextureNotMarked.getSize().y + 60) }; // button selector
// background
	SFMLSprite backgroundSprite{backgroundTexture, 0, 0};
	//sigelplayer button sprite
  SFMLSprite newGameSinglePlayerButton{buttonTextureMarked,
  	(float)(APPLICATION_WIDTH/2 - buttonTextureNotMarked.getSize().x/2),
    (float)(buttonTextureNotMarked.getSize().y + 50)};
//muktiplayer button sprite
  SFMLSprite newGameMultiplayerButton{buttonTextureNotMarked,
   (float)(APPLICATION_WIDTH/2 - buttonTextureNotMarked.getSize().x/2),
    (float)(buttonTextureNotMarked.getSize().y *3 +50)};
    //exit button sprite
  SFMLSprite exitButton{buttonTextureNotMarked,
   (float)(APPLICATION_WIDTH/2 - buttonTextureNotMarked.getSize().x/2),
    (float)(buttonTextureNotMarked.getSize().y *5 +50)};


};
