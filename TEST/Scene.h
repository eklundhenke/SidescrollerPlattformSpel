#pragma once
#include "InputManager.h"
#include <iostream>
class SFMLRender;
enum SCENES {MAINMENUSCENE, GAMESCENE, GAMESCENEMULTI, GAMEOVERSCENE, EXITGAME, PAUSESCENE};
class Scene{
public:
  virtual SCENES updateScene(float deltaTime){ return MAINMENUSCENE;};
  virtual void renderScene(SFMLRender* render, float deltaTime){};
  SCENES getType(){return type;};
  virtual ~Scene(){};

  void changedFocus(bool hasFocus) { inputmgr.enableInputs(hasFocus); };

  virtual void keyPress(sf::Keyboard::Key) { std::cout << "PRESSED KEY" << std::endl; };
private:
  enum SCENES type{MAINMENUSCENE};

protected:
	Scene(SCENES scene, InputManager& input) : type{ scene }, inputmgr{input} {};
  InputManager& inputmgr; //Provides access to inputs
};
