#pragma once
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Text.hpp"

class SFMLText : public sf::Text {
public:
  SFMLText(std::string text, float x, float y, unsigned fontSize = 30); //displayed text, x,y cords and font size(optional)

private:
  sf::Font font; //Font object
};
