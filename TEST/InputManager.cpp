#include "InputManager.h"
#include "iostream"
bool InputManager::isKeyPressed(KEYS key){
	if (!inputsEnabled) return false;
  switch(key){
    case UP:
    return sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
    break;
    case DOWN:
    return sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
    break;
    case LEFT:
    return sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
    break;
    case RIGHT:
    return sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
    break;
    case ENTER:
    return sf::Keyboard::isKeyPressed(sf::Keyboard::Return); //Enter
    break;
    case ESCAPE:
    return sf::Keyboard::isKeyPressed(sf::Keyboard::Escape);
    break;
    case W:
    return sf::Keyboard::isKeyPressed(sf::Keyboard::W);
    break;
    case A:
    return sf::Keyboard::isKeyPressed(sf::Keyboard::A);
    break;
    case S:
    return sf::Keyboard::isKeyPressed(sf::Keyboard::S);
    break;
    case D:
    return sf::Keyboard::isKeyPressed(sf::Keyboard::D);
    break;
    case F5:
    return sf::Keyboard::isKeyPressed(sf::Keyboard::F5);
    break;
    case G:
    return sf::Keyboard::isKeyPressed(sf::Keyboard::G);
    break;
    default:
      std::cout << "Error key not mapped in InputManager" << std::endl;
    return false;
  }
}
