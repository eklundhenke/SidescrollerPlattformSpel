#pragma once
#include "SFML/Window.hpp"


enum KEYS{UP = 0, DOWN, LEFT, RIGHT, W, A, S, D, ENTER, ESCAPE, F5, G}; //Supported keys
class InputManager{
public:
  InputManager(){};
  bool isKeyPressed(KEYS key); //Returns true if key pressed

};
