#include "PauseScene.h"
#include "SFMLRender.h"
PauseScene::PauseScene(InputManager& input) : Scene{PAUSESCENE, input}{}

void PauseScene::renderScene(SFMLRender* render, float deltaTime)
{
  //Reset camera position (Needed if we return from gamescene)
  render->setCameraPosition(APPLICATION_WIDTH / 2, APPLICATION_HEIGHT /2);

  // Draw the background
  //render->drawSprite(backgroundSprite);

  // Draw the buttons
  render->drawSprite(resumeButton);
  render->drawSprite(mainMenuButton);
  render->drawSprite(exitButton);

  // Draw the marker
  render->drawSprite(keyMarker);

  // Draw text
  render->drawText(titelText);
  render->drawText(resumeText);
  render->drawText(mainMenuText);
  render->drawText(exitText);
  //center text in buttons
  centerText(resumeText, resumeButton);
  centerText(mainMenuText, mainMenuButton);
  centerText(exitText, exitButton);
}

SCENES PauseScene::updateScene(float deltaTime){
  using namespace std::chrono;
  high_resolution_clock::time_point now = high_resolution_clock::now();
  duration<double> time_span = duration_cast<duration<double>>( now - start_time);

  if (inputmgr.isKeyPressed(UP) && time_span.count() > 0.5)
  {    //if the marker is att place 2 or 3 we can move up
    if ((keyMarker.getMarkerPos() == 2) || (keyMarker.getMarkerPos() == 3))
    {
      keyMarker.move(0,-195);
      start_time = high_resolution_clock::now();
      if (keyMarker.getMarkerPos() == 2)
      {
        keyMarker.setMarkerPos(1);
        //changes the look of the button
        resumeButton.setTexture(buttonTextureMarked);
    mainMenuButton.setTexture(buttonTextureNotMarked);
      }
      else
      {
        keyMarker.setMarkerPos(2);
        exitButton.setTexture(buttonTextureNotMarked);
        mainMenuButton.setTexture(buttonTextureMarked);
      }
    }
  }
  else if(inputmgr.isKeyPressed(DOWN) && time_span.count() > 0.5)
  {//if the marker is att place 1 or 2 we can move down
    if ((keyMarker.getMarkerPos() == 1) || (keyMarker.getMarkerPos() == 2))
    {
      keyMarker.move(0,195);
      start_time = high_resolution_clock::now();
      if (keyMarker.getMarkerPos() == 2)
      {
        keyMarker.setMarkerPos(3);
        mainMenuButton.setTexture(buttonTextureNotMarked);
        exitButton.setTexture(buttonTextureMarked);
      }
      else
      {
        keyMarker.setMarkerPos(2);
    resumeButton.setTexture(buttonTextureNotMarked);
    mainMenuButton.setTexture(buttonTextureMarked);
      }
    }
  }
  else if (inputmgr.isKeyPressed(ENTER))
  {
    if (keyMarker.getMarkerPos() == 1)
    {
      return GAMESCENE;
    }
    else if (keyMarker.getMarkerPos() == 2)
    {
      return MAINMENUSCENE;
    }
    else
    {
      return EXITGAME;
    }
  }
  return PAUSESCENE; //Do nothing
}
