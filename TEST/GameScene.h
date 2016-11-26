#pragma once
#include "Scene.h"
#include "MapManager.h"
#include "InputManager.h"
#include "Player.h"
#include "TimeLeft.h"
#include "HealthDisplay.h"
#include "Snail.h"
#include "Coin.h"
#include "Goal.h"
#include <chrono>
#include "Constants.h"
#include "GameOverScene.h"
#include "PauseScene.h"
#include "Key.h"
class DebugInfo;
class GameScene : public Scene {
  friend DebugInfo;
public:
  GameScene(InputManager& input, bool SingleOrMultiplayer);
  void renderScene(SFMLRender* render, float deltaTime); //Render logic
  SCENES updateScene(float deltaTime); //Update Logic
  std::chrono::high_resolution_clock::time_point start_time;
  void reloadMap();
private:
  void playerMovement(Player& player, float deltaTime); //Calculates player position based on input/gravity
  void cameraHandling();
  void dead(Player& player);
  bool gameOver = false;
  int gameOverOrPaused = 0; //sets to 2 if gameover 1 if paus
  bool notPaused = true;
  std::vector<Snail> enemies;
  std::vector<Coin> coins;
  std::vector<Key> keys;
  MapManager mapmgr{"map.txt"}; //Map module
  InputManager& inputmgr; //Provides access to inputs
  bool multiplayer;
  int remainingTime {200};
  GameOverScene *gameOverScene = new GameOverScene(inputmgr);
  PauseScene *pausescene = new PauseScene(inputmgr);

  //Textures
  SFMLTexture backgroundTexture{"background.png"};
  SFMLTexture playerOneTexture{"Player/p1_stand.png"};
  SFMLTexture playerOneTextureJump{"Player/p1_jump.png"};
  SFMLTexture playerTwoTexture{"Player/p2_stand.png"};
  SFMLTexture playerTwoTextureJump{"Player/p2_jump.png"};
  SFMLTexture snailWalk1{"Enemies/snailWalk1.png"};
  SFMLTexture snailWalk2{"Enemies/snailWalk2.png"};
  SFMLTexture coinTexture{"HUD/hud_coins.png"};
  SFMLTexture keyTexture{"Items/keyBlue.png"};
  SFMLTexture goalPost{"Items/flagRed.png"};
  SFMLTexture healthDisplayTexture{"HUD/hud_heartFull.png"};
  SFMLTexture playerOneWalkAnimation[11] = {
    SFMLTexture{"Player/p1_walk/PNG/p1_walk01.png"},
    SFMLTexture{"Player/p1_walk/PNG/p1_walk02.png"},
    SFMLTexture{"Player/p1_walk/PNG/p1_walk03.png"},
    SFMLTexture{"Player/p1_walk/PNG/p1_walk04.png"},
    SFMLTexture{"Player/p1_walk/PNG/p1_walk05.png"},
    SFMLTexture{"Player/p1_walk/PNG/p1_walk06.png"},
    SFMLTexture{"Player/p1_walk/PNG/p1_walk07.png"},
    SFMLTexture{"Player/p1_walk/PNG/p1_walk08.png"},
    SFMLTexture{"Player/p1_walk/PNG/p1_walk09.png"},
    SFMLTexture{"Player/p1_walk/PNG/p1_walk10.png"},
    SFMLTexture{"Player/p1_walk/PNG/p1_walk11.png"}};

  SFMLTexture playerTwoWalkAnimation[11] = {
    SFMLTexture{"Player/p2_walk/PNG/p2_walk01.png"},
    SFMLTexture{"Player/p2_walk/PNG/p2_walk02.png"},
    SFMLTexture{"Player/p2_walk/PNG/p2_walk03.png"},
    SFMLTexture{"Player/p2_walk/PNG/p2_walk04.png"},
    SFMLTexture{"Player/p2_walk/PNG/p2_walk05.png"},
    SFMLTexture{"Player/p2_walk/PNG/p2_walk06.png"},
    SFMLTexture{"Player/p2_walk/PNG/p2_walk07.png"},
    SFMLTexture{"Player/p2_walk/PNG/p2_walk08.png"},
    SFMLTexture{"Player/p2_walk/PNG/p2_walk09.png"},
    SFMLTexture{"Player/p2_walk/PNG/p2_walk10.png"},
    SFMLTexture{"Player/p2_walk/PNG/p2_walk11.png"}};
  //Sprites and UI
  SFMLSprite backgroundSprite{backgroundTexture, APPLICATION_WIDTH - 150, 0};
  TimeLeft timeLeftText{remainingTime};
  Goal goalSprite {goalPost, 26 * TILE_SIZE, 8 * TILE_SIZE};
  HealthDisplay healthDisplay{healthDisplayTexture};
  Player playerOne{playerOneTexture, playerOneTextureJump, playerOneWalkAnimation, 800, 400, 1};
  Player playerTwo{playerTwoTexture, playerTwoTextureJump, playerTwoWalkAnimation, 900, 400, 2};
  //Snail testSnail{snailWalk1, snailWalk2, 1330, 70*9, 6 * 70, false};
  int camera_x{};
};
