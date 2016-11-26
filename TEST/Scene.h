#pragma once
class SFMLRender;
enum SCENES {MAINMENUSCENE, GAMESCENE, GAMESCENEMULTI, GAMEOVERSCENE, EXITGAME, PAUSESCENE};
class Scene{
public:
  virtual SCENES updateScene(float deltaTime){ return MAINMENUSCENE;};
  virtual void renderScene(SFMLRender* render, float deltaTime){};
  SCENES getType(){return type;};
  virtual ~Scene(){};
private:
  enum SCENES type{MAINMENUSCENE};

protected:
  Scene(SCENES scene) : type{scene}{};
};
