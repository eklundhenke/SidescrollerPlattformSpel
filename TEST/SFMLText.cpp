#include "SFMLText.h"

SFMLText::SFMLText(std::string text, float x, float y, unsigned fontSize) : sf::Text(text, font, fontSize){
  // Load it from a file
  setColor(sf::Color::Black);
  setPosition (x, y);
  font.loadFromFile("kenvector_future.ttf");
  //font.loadFromFile("times_new_roman.ttf");
}
