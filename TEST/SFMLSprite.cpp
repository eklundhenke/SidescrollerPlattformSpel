#include "SFMLSprite.h"
#include "SFMLTexture.h"
SFMLSprite::SFMLSprite(SFMLTexture& texture, float x, float y) : sf::Sprite{texture, sf::IntRect(0, 0, texture.getSize().x, texture.getSize().y)}{
  setPosition(x,y);
}