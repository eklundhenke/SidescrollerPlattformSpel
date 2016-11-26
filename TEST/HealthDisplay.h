#pragma once
#include "SFMLSprite.h"
class HealthDisplay : public SFMLSprite{

public:
  HealthDisplay(SFMLTexture& texture) : SFMLSprite{texture, 0,0}{};
private:

};
