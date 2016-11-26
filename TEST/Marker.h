#pragma once
#include "Entity.h"
class Marker : public Entity{

private:
	int markerPos;
public:
  Marker(SFMLTexture& texture, int pos, float x, float y) : Entity{texture}{
    setPosition(x, y);
    markerPos = pos;

  };
int getMarkerPos(){ return markerPos;};
void setMarkerPos(int position){markerPos = position;};

};
