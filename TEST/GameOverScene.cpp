#include "GameOverScene.h"
#include "SFMLRender.h"
GameOverScene::GameOverScene(InputManager& input) : Scene{GAMEOVERSCENE}, inputmgr{input}{}

void GameOverScene::renderScene(SFMLRender* render, float deltaTime)
{
  //Reset camera position (Needed if we return from gamescene)
  render->setCameraPosition(APPLICATION_WIDTH / 2, APPLICATION_HEIGHT /2);

  // Draw the background
  render->drawSprite(backgroundSprite);

  // Draw the buttons
  render->drawSprite(mainMenuButton);
  render->drawSprite(exitButton);

  // Draw the marker
  render->drawSprite(keyMarker);

  // Draw text
  render->drawText(titelText);
  render->drawText(mainMenuText);
  render->drawText(exitText);
  //center text in buttons
  centerText(mainMenuText, mainMenuButton);
  centerText(exitText, exitButton);
}

SCENES GameOverScene::updateScene(float deltaTime){
  using namespace std::chrono;
  high_resolution_clock::time_point now = high_resolution_clock::now();
  duration<double> time_span = duration_cast<duration<double>>( now - start_time);

  // Checking what key is pressed and compare it to the last time a key was pressed
  if ((inputmgr.isKeyPressed(UP) && time_span.count() > 0.5) && (keyMarker.getMarkerPos() == 2))
  {
      keyMarker.move(0,-190);
      start_time = high_resolution_clock::now();
      keyMarker.setMarkerPos(1);
      mainMenuButton.setTexture(buttonTextureMarked);
      exitButton.setTexture(buttonTextureNotMarked);
  }
  else if((inputmgr.isKeyPressed(DOWN) && time_span.count() > 0.5) && (keyMarker.getMarkerPos() == 1))
  {
      keyMarker.move(0,190);
      start_time = high_resolution_clock::now();
      keyMarker.setMarkerPos(2);
      mainMenuButton.setTexture(buttonTextureNotMarked);
      exitButton.setTexture(buttonTextureMarked);
  }
  else if (inputmgr.isKeyPressed(ENTER))
  {
    if (keyMarker.getMarkerPos() == 1)
    {
      return MAINMENUSCENE;
    }
    else
    {
      return EXITGAME;  //---Change to multiplayerscene when its done
    }
  }
  return GAMESCENE; //Do nothing
}
