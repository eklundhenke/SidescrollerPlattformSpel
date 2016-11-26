#pragma once
#include "SFML/Graphics.hpp"
#include "SFMLTexture.h"
class SFMLSprite : public sf::Sprite{
public:
  SFMLSprite(SFMLTexture& texture, float x, float y);
private:

};
