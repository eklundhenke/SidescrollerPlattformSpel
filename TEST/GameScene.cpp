#include "GameScene.h"
#include "SFMLRender.h"
GameScene::GameScene(InputManager& input, bool multiplayer) : Scene{GAMESCENE}, inputmgr{input}, multiplayer{multiplayer}
{
  //Spawns enemies and coins
  enemies.push_back(Snail{snailWalk1, snailWalk2, 19 * TILE_SIZE, 9 * TILE_SIZE, 6 * 70, false});
  enemies.push_back(Snail{snailWalk1, snailWalk2, 75 * TILE_SIZE, 14 * TILE_SIZE, 10 * 70, true});
  enemies.push_back(Snail{snailWalk1, snailWalk2, 134 * TILE_SIZE, 12 * TILE_SIZE, 7 * 70, false});
  enemies.push_back(Snail{snailWalk1, snailWalk2, 161 * TILE_SIZE, 11 * TILE_SIZE, 7 * 70, false});
  enemies.push_back(Snail{snailWalk1, snailWalk2, 179 * TILE_SIZE, 10 * TILE_SIZE, 4 * 70, false});
  enemies.push_back(Snail{snailWalk1, snailWalk2, 189 * TILE_SIZE, 10 * TILE_SIZE, 6 * 70, false});
  enemies.push_back(Snail{snailWalk1, snailWalk2, 200 * TILE_SIZE, 10 * TILE_SIZE, 6 * 70, false});
  coins.push_back(Coin{coinTexture, 15 * TILE_SIZE, 8 * TILE_SIZE});
  coins.push_back(Coin{coinTexture, 30 * TILE_SIZE, 8 * TILE_SIZE});
  coins.push_back(Coin{coinTexture, 63 * TILE_SIZE, 3 * TILE_SIZE});
  coins.push_back(Coin{coinTexture, 86 * TILE_SIZE, 13 * TILE_SIZE});
  coins.push_back(Coin{coinTexture, 87 * TILE_SIZE, 13 * TILE_SIZE});
  coins.push_back(Coin{coinTexture, 129 * TILE_SIZE, 6 * TILE_SIZE});
  coins.push_back(Coin{coinTexture, 181 * TILE_SIZE, 6 * TILE_SIZE});
  keys.push_back(Key(keyTexture, 17 * TILE_SIZE, 4 * TILE_SIZE, mapmgr.getTilePtrAtPosition(15 * TILE_SIZE,7 * TILE_SIZE), mapmgr.getTilePtrAtPosition(14 * TILE_SIZE,7 * TILE_SIZE), mapmgr.getTilePtrAtPosition(16 * TILE_SIZE,7 * TILE_SIZE)));
  keys.push_back(Key(keyTexture, 137* TILE_SIZE, 1 * TILE_SIZE, mapmgr.getTilePtrAtPosition(128 * TILE_SIZE, 5 * TILE_SIZE), mapmgr.getTilePtrAtPosition(129 * TILE_SIZE, 5 * TILE_SIZE), mapmgr.getTilePtrAtPosition(130 * TILE_SIZE, 5 * TILE_SIZE)));
  keys.push_back(Key(keyTexture, 196* TILE_SIZE, 12 * TILE_SIZE, mapmgr.getTilePtrAtPosition(201 * TILE_SIZE, 8 * TILE_SIZE), mapmgr.getTilePtrAtPosition(201 * TILE_SIZE, 7 * TILE_SIZE), mapmgr.getTilePtrAtPosition(201 * TILE_SIZE, 6 * TILE_SIZE)));
  keys.push_back(Key(keyTexture, 196* TILE_SIZE, 12 * TILE_SIZE, mapmgr.getTilePtrAtPosition(201 * TILE_SIZE, 5 * TILE_SIZE), mapmgr.getTilePtrAtPosition(201 * TILE_SIZE, 4 * TILE_SIZE), mapmgr.getTilePtrAtPosition(201 * TILE_SIZE, 3 * TILE_SIZE)));

}

void GameScene::renderScene(SFMLRender* render, float deltaTime)
{
  if(playerOne.getPosition().x >= camera_x && (!playerOne.getPlayerStuck() && !playerTwo.getPlayerStuck()))
  {
    //Set camera to point to player 1 or two depending on whom are in front
    render->setCameraPosition(playerOne.getGlobalBounds().left, 600);
  }
  if(playerTwo.getPosition().x >= camera_x && (!playerOne.getPlayerStuck() && !playerTwo.getPlayerStuck()))
  {
    //Set camera to point to player 1 or two depending on whom are in front
    render->setCameraPosition(playerTwo.getGlobalBounds().left, 600);
  }
  float screenScale = (float)((float)render->getWindowSize().x / (float)APPLICATION_WIDTH);
  //Background should not move when camera moves
  backgroundSprite.setPosition(render->screenPixelsToMapCord(0, 0));
  //Text should not move when camera moves
  timeLeftText.setPosition(render->screenPixelsToMapCord(render->getWindowSize().x - 300 * screenScale, 0));

  //Draw background
  render->drawSprite(backgroundSprite);
  //Draw map
  mapmgr.renderMap(render);
  //Drawing all snails
  for(Snail& s : enemies)
  {
    render->drawSprite(s);
  }
  //Drawing all coins
  for(Coin& c : coins)
  {
    if(!c.removeCoin())
    {
      render->drawSprite(c);
    }
  }
  for(Key& k : keys)
  {
    if (k.isUsed()) continue;
    render->drawSprite(k);
  }
  //Draw player 1
  render->drawPlayer(playerOne);
  //If multiplayer is chosen -- Draw player 2
  if(multiplayer)
  {
    render->drawPlayer(playerTwo);
  }
  //Draw "Time left" text
  render->drawText(timeLeftText);
  //Display hearts based on player hp
  for (int i = 0; i<playerOne.getHP(); i++)
  {
    //HP should not move when camera moves
    healthDisplay.setPosition(render->screenPixelsToMapCord(55 * i * screenScale + 5 * screenScale, 10 * screenScale));
    //Draw heart
    render->drawSprite(healthDisplay);
  }
  render->drawSprite(goalSprite);//render the goal
  if (gameOver == true && gameOverOrPaused == 2) //if game over render gameoverscene
  {
    gameOverScene->renderScene(render, deltaTime);
  }
  if (notPaused == false && gameOverOrPaused == 1) //if ESCAPE is pressed render PauseScene
  {
    pausescene->renderScene(render,deltaTime);
  }

}
SCENES GameScene::updateScene(float deltaTime)
{
if(notPaused)
{
  //1 = touching player 1 2= touching player2 3= both
  int status_snail = 0;
  int status_coin = 0;
  for(Snail& s : enemies)
  {
    status_snail = s.logic(deltaTime, playerOne, playerTwo);
    //NOTERA ATT SPELARE TVÅ ÄR SPAWNAD MEN OSYNLIG OM MAN KÖR SINGLEPLAYER SÅ HAN KAN TRIGGA DETTA ÄVEN I SINGLEPLAYER
    //Lösning1 Spawna inte spelare2 i SINGLEPLAYER
    //Lösning2 lägg in en check här för multiplayer(fulkod?)
    using namespace std::chrono;
    if(status_snail == 3)
    {
      //Both touching snail, what should we do?
    }
    else if(status_snail == 1)
    {
      //Player1 touching snail -- reducing health and
      //start a clock, when the clock reaches 3 secconds respawn him.
      playerOne.getHP() -= 1;
      start_time = high_resolution_clock::now();
      playerOne.getDead() = true;
    }
    else if(status_snail == 2)
    {
      //Player 2 touching snail
      playerOne.getHP() -= 1;
      start_time = high_resolution_clock::now();
      playerTwo.getDead() = true;
    }

  }
  for(Coin& c : coins)
  {
    status_coin = c.logic(playerOne, playerTwo);
    if(status_coin == 1 || status_coin == 2 || status_coin == 3)
    {
      // REMOVE COIN FROM VECTOR AND ADD TIME TO PLAYER
      if(!c.removeCoin())
      {
        timeLeftText.get_remTime() += 5;
      }
      c.removeCoin() = true;
    }
  }

  for (Key& k : keys){
    k.logic(playerOne, playerTwo);
  }

  timeLeftText.decreaseTime();
  timeLeftText.setString("Time Left : " + std::to_string(timeLeftText.get_remTime()));
  playerMovement(playerOne, deltaTime);
  if(multiplayer)
  {
    //Calculate player position base on input/Gravity
    playerMovement(playerTwo, deltaTime);
  }
  //Exit to mainmenu if ESCAPE is pressed
  if(inputmgr.isKeyPressed(ESCAPE))
  {
    notPaused = false;
    gameOverOrPaused = 1;
  }
  if (goalSprite.logic(playerOne, playerTwo))
  {
    goalSprite.setGoal(true);
    gameOver = true;
    notPaused = false;
    gameOverOrPaused = 2;
  }
  // If the player has no HP -- Go to gameoverscene
  if(playerOne.getHP() == -1 || timeLeftText.get_remTime() == 0)
  {
    gameOver = true;
    notPaused = false;
    gameOverOrPaused = 2;
  }
  //if none of these is true -- stay in gamescene
  return GAMESCENE;
}
if(gameOverOrPaused == 1) {
  SCENES status = pausescene->updateScene(deltaTime);
  if (status == GAMESCENE){
    gameOverOrPaused = 0;
    notPaused = true;
  }
  return status;
}
else if (gameOverOrPaused == 2) return gameOverScene->updateScene(deltaTime);
return GAMESCENE;
}


//Checks if the camera should be moving or not.
void GameScene::cameraHandling()
{
  if(camera_x - playerOne.getPosition().x - playerOne.xVelocity > APPLICATION_WIDTH/2)
  {
    if(playerOne.xVelocity < 0)
    {
      playerOne.xVelocity = 0;
    }
    playerOne.getPlayerStuck() = true;
    playerOne.getStuckRight() = playerOne.getPosition().x;
  }
  else if(camera_x - playerOne.getPosition().x - playerOne.xVelocity < APPLICATION_WIDTH/2)
  {
    if(playerOne.getPosition().x > camera_x)
    {
      playerOne.getPlayerStuck() = false;
    }
  }
  if(multiplayer)
  {
    if(camera_x - playerTwo.getPosition().x - playerTwo.xVelocity > APPLICATION_WIDTH/2)
    {
      if(playerTwo.xVelocity < 0)
      {
        playerTwo.xVelocity = 0;
      }
      playerTwo.getPlayerStuck() = true;
      playerTwo.getStuckRight() = playerTwo.getPosition().x;
    }
    else if(camera_x - playerTwo.getPosition().x - playerTwo.xVelocity < APPLICATION_WIDTH/2)
    {
      if(playerTwo.getPosition().x > camera_x)
      {
        playerTwo.getPlayerStuck() = false;
      }
    }
    if(playerOne.getStuckRight()+APPLICATION_WIDTH - 80 <
    playerTwo.getPosition().x && playerOne.getPlayerStuck())
    {
      if(playerTwo.xVelocity > 0)
      {
        playerTwo.xVelocity = 0;
      }
    }
    if(playerTwo.getStuckRight()+APPLICATION_WIDTH - 80 <
    playerOne.getPosition().x && playerTwo.getPlayerStuck())
    {
      if(playerOne.xVelocity > 0)
      {
        playerOne.xVelocity = 0;
      }
    }
  }
}

//If the player is dead, wait for 3 secconds, then respawn him above the last
//place he was touching the ground
void GameScene::dead(Player& player)
{
  using namespace std::chrono;
  high_resolution_clock::time_point now = high_resolution_clock::now();
  duration<double> time_span = duration_cast<duration<double>>( now - start_time);
  if(time_span.count() > 3)
  {
    player.getDead() = false;
    if(camera_x - player.getTmp_x() > APPLICATION_WIDTH/2)
    {
      player.getTmp_x() = camera_x - APPLICATION_WIDTH/2 + 100;
    }
    player.setPosition(player.getTmp_x(), player.getTmp_y() - 500);
  }
  else
  {
    player.setPosition(player.getTmp_x(), player.getTmp_y() - 10000);
  }
}

void GameScene::playerMovement(Player& player, float deltaTime)
{
  //Check if we are falling
  if(player.isFalling)
  {
    if(player.getPosition().y > APPLICATION_HEIGHT)
    {
      using namespace std::chrono;
      start_time = high_resolution_clock::now();
      player.getHP() -= 1;
      player.yVelocity = 0;
      player.xVelocity = 0;
      player.getDead() = true;
      camera_x = player.getPosition().x;
      if(player.getOneorTwo() == 2)
      {
        playerOne.getHP() -= 1;
      }
    }
    player.falling(deltaTime);
  }
  else
  {
    //Check if we should jump again
    if(inputmgr.isKeyPressed(UP) || inputmgr.isKeyPressed(W))
    {
      if(inputmgr.isKeyPressed(W) && player.getOneorTwo() == 2)
      {
        player.jump();
      }
      if(inputmgr.isKeyPressed(UP) && player.getOneorTwo() == 1)
      {
        player.jump();
      }
    }
    player.getTmp_x() = player.getPosition().x - 10;
    player.getTmp_y() = player.getPosition().y - 10;
  }

  //We are not falling, check if we should move in x axis
  if((inputmgr.isKeyPressed(RIGHT) && !inputmgr.isKeyPressed(LEFT))||
  (inputmgr.isKeyPressed(D) && !inputmgr.isKeyPressed(A)))
  {
    if(inputmgr.isKeyPressed(D) && player.getOneorTwo() == 2)
    {
      player.moveRight(deltaTime);
    }
    if(inputmgr.isKeyPressed(RIGHT) && player.getOneorTwo() == 1)
    {
      player.moveRight(deltaTime);
    }
  }
  if((inputmgr.isKeyPressed(LEFT) && !inputmgr.isKeyPressed(RIGHT))||
  (inputmgr.isKeyPressed(A) && !inputmgr.isKeyPressed(D)))
  {
    if(inputmgr.isKeyPressed(A) && player.getOneorTwo() == 2)
    {
      player.moveLeft(deltaTime);
    }
    if(inputmgr.isKeyPressed(LEFT) && player.getOneorTwo() == 1)
    {
      player.moveLeft(deltaTime);
    }
  }
  if(!inputmgr.isKeyPressed(RIGHT) && !inputmgr.isKeyPressed(LEFT) && player.getOneorTwo() == 1)
  {
    player.retardX(deltaTime);
  }
  if(!inputmgr.isKeyPressed(A) && !inputmgr.isKeyPressed(D) && player.getOneorTwo() == 2)
  {
    player.retardX(deltaTime);
  }
  if(player.getPosition().x > camera_x)
  {
    if(!playerOne.getPlayerStuck() && !playerTwo.getPlayerStuck())
    {
      if(playerOne.getPosition().x > playerTwo.getPosition().x)
      {
        camera_x = playerOne.getPosition().x;
      }
      else
      {
        camera_x = playerTwo.getPosition().x;
      }
    }
  }
  if(playerOne.getDead())
  {
    dead(playerOne);
  }
  if(playerTwo.getDead())
  {
    dead(playerTwo);
  }

  //Limit the max-speed of the player.
  player.limitSpeed();
  cameraHandling();
  //Avoid changing xVelocity or yVelocity before calling move() or this won't work correctly
  mapmgr.checkMapCollision(player, deltaTime);
  player.updateTexture(deltaTime);
}

void GameScene::reloadMap(){
  mapmgr.loadMapFromFile("map.txt");
}
