#pragma once
#include "SFMLRender.h"
#include "InputManager.h"
#include "MainMenuScene.h"
#include "GameScene.h"
#include "GameOverScene.h"
#include "Time.h"
#include "DebugInfo.h"
class GameWindow{
private:
  SFMLRender render; //Render module
  InputManager inputmgr; //Input module
  Time timeMgr; //Calculates time between frames
  Scene* current_scene{nullptr}; //Points to current scene
  DebugInfo debug{};
public:
  GameWindow(){
    //Program started...
    current_scene = new MainMenuScene(inputmgr); //Show MainMenu

    while(render.windowIsOpen()){ //Loop untill program window is closed
      bool exitRequested = render.processEvents(current_scene); //Process inputs
      float deltaTime = timeMgr.getTimeAndRestart().asSeconds(); //Calculate deltaTime
      SCENES result = current_scene->updateScene(deltaTime); //run current scene logic
      if(result == GAMESCENE && inputmgr.isKeyPressed(F5)){
        GameScene* gP = (GameScene*)current_scene;
        gP->reloadMap();
      }
      if(result == GAMESCENE && current_scene->getType() != GAMESCENE){ //Switch currentscene to GameScene
        delete current_scene; //No memory leak
        current_scene = new GameScene(inputmgr, false); //Show GameScene
        debug.setGameScenePtr((GameScene*)current_scene);
      }
      else if(result == GAMESCENEMULTI && current_scene->getType() != GAMESCENEMULTI)
      {
        delete current_scene;
        current_scene = new GameScene(inputmgr, true);
        debug.setGameScenePtr((GameScene*)current_scene);
      }
      else if(result == MAINMENUSCENE && current_scene->getType() != MAINMENUSCENE){ //Swtich to MainMenuscene
        delete current_scene; //No memory leak
        current_scene = new MainMenuScene(inputmgr); //Show mainmenu
        debug.setGameScenePtr(nullptr);
      }
      /*else if(result == GAMEOVERSCENE && current_scene->getType() != GAMEOVERSCENE){ //Swtich to MainMenuscene
        delete current_scene; //No memory leak
        current_scene = new GameOverScene(inputmgr); //Show mainmenu
      }
      */
      else if((result == EXITGAME || exitRequested) && result != GAMESCENE) { //User has requested to exit program
        std::cout << "User closed the game " << result << std::endl;
        render.closeWindow(); //Close window
        continue;
      }
      //Draw a new frame
      render.clearFrame(); //Clear old frame
      render.drawFrame(current_scene, deltaTime); //Draw the new frame
      render.drawDebugInfo(debug);
      render.displayFrame(); //Show the new frame
    }

    if(current_scene != nullptr){ //No memory leak
        delete current_scene;
    }
  };

};
