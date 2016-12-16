#include "MainMenuScene.h"
#include "SFMLRender.h"
MainMenuScene::MainMenuScene(InputManager& input) : Scene{MAINMENUSCENE, input}{}

void MainMenuScene::renderScene(SFMLRender* render, float deltaTime){
  render->setCameraPosition(APPLICATION_WIDTH / 2, APPLICATION_HEIGHT /2);
   //Reset camera position (Needed if we return from gamescene)
  render->drawSprite(backgroundSprite);
  render->drawSprite(newGameSinglePlayerButton); //Draw the button
  render->drawSprite(newGameMultiplayerButton); //multiplayer button
  render->drawSprite(exitButton); //Draw the exit button
  render->drawSprite(keyMarker); //Draw marker
  render->drawText(titelText); // spelets titel
  render->drawText(singelPlayerText);
  render->drawText(multiPlayerText);
  render->drawText(exitText);
  centerText(singelPlayerText, newGameSinglePlayerButton);//centers the texts
  centerText(multiPlayerText, newGameMultiplayerButton);
  centerText(exitText, exitButton);
}


SCENES MainMenuScene::updateScene(float deltaTime){
	return returnValue;
}


void MainMenuScene::keyPress(sf::Keyboard::Key key) {

	//using namespace std::chrono;
	//high_resolution_clock::time_point now = high_resolution_clock::now();
	// checks for up press and if we have waited more
	//then 0,5 sec so that the marker dont move to fast
	//duration<double> time_span = duration_cast<duration<double>>(now - start_time);
	if (key == sf::Keyboard::Up)
	{    //if the marker is att place 2 or 3 we can move up
		if ((keyMarker.getMarkerPos() == 2) || (keyMarker.getMarkerPos() == 3))
		{
			keyMarker.move(0, -195);
			//start_time = high_resolution_clock::now();
			if (keyMarker.getMarkerPos() == 2)
			{
				keyMarker.setMarkerPos(1);
				//changes the look of the button
				newGameSinglePlayerButton.setTexture(buttonTextureMarked);
				newGameMultiplayerButton.setTexture(buttonTextureNotMarked);
			}
			else
			{
				keyMarker.setMarkerPos(2);
				exitButton.setTexture(buttonTextureNotMarked);
				newGameMultiplayerButton.setTexture(buttonTextureMarked);
			}
		}
	}
	else if (key == sf::Keyboard::Down)
	{//if the marker is att place 1 or 2 we can move down
		if ((keyMarker.getMarkerPos() == 1) || (keyMarker.getMarkerPos() == 2))
		{
			keyMarker.move(0, 195);
			//start_time = high_resolution_clock::now();
			if (keyMarker.getMarkerPos() == 2)
			{
				keyMarker.setMarkerPos(3);
				newGameMultiplayerButton.setTexture(buttonTextureNotMarked);
				exitButton.setTexture(buttonTextureMarked);
			}
			else
			{
				keyMarker.setMarkerPos(2);
				newGameSinglePlayerButton.setTexture(buttonTextureNotMarked);
				newGameMultiplayerButton.setTexture(buttonTextureMarked);
			}
		}
	}
	else if (key == sf::Keyboard::Return)
	{
		if (keyMarker.getMarkerPos() == 1)
		{
			returnValue = GAMESCENE;
		}
		else if (keyMarker.getMarkerPos() == 2)
		{
			returnValue = GAMESCENEMULTI;  //---Change to multiplayerscene when its done
		}
		else
		{
			returnValue = EXITGAME;
		}
	}
	//returnValue = MAINMENUSCENE; //Do nothing
}