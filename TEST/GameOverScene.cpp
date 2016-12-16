#include "GameOverScene.h"
#include "SFMLRender.h"
GameOverScene::GameOverScene(InputManager& input) : Scene{GAMEOVERSCENE, input}{}

void GameOverScene::renderScene(SFMLRender* render, float deltaTime)
{
  //Reset camera position (Needed if we return from gamescene)
  render->setCameraPosition(APPLICATION_WIDTH / 2, APPLICATION_HEIGHT /2);

  // Draw the background
  render->drawSprite(backgroundSprite);

  // Draw the buttons
  render->drawSprite(mainMenuButton);
  render->drawSprite(exitButton);

  // Draw the marker
  render->drawSprite(keyMarker);
// Draw text
if (winOrLose == false)//renders Game over if the player lost
  {
    render->drawText(loserText);
  }
  else//if player win display score and highscore
  {
    //the score text is here, so that we have a updated score when its called
  SFMLText scoreText{"Your score : " + std::to_string(getScore()),
  (float)(APPLICATION_WIDTH/2 - 150) , 100};
  SFMLText highScoreText{"High Score : ",
  (float)(APPLICATION_WIDTH/2 - 600) , 100};
  SFMLText highScoreText1{"1 : " + std::to_string(highScoreVector.at(0)),
  (float)(APPLICATION_WIDTH/2 - 500) , 150};
  SFMLText highScoreText2{"2 : " + std::to_string(highScoreVector.at(1)),
  (float)(APPLICATION_WIDTH/2 - 500) , 200};
  SFMLText highScoreText3{"3 : " + std::to_string(highScoreVector.at(2)),
  (float)(APPLICATION_WIDTH/2 - 500) , 250};
  SFMLText highScoreText4{"4 : " + std::to_string(highScoreVector.at(3)),
  (float)(APPLICATION_WIDTH/2 - 500) , 300};
  SFMLText highScoreText5{"5 : " + std::to_string(highScoreVector.at(4)),
  (float)(APPLICATION_WIDTH/2 - 500) , 350};

  render->drawText(winText);
  render->drawText(scoreText);
  render->drawText(highScoreText);
  render->drawText(highScoreText1);
  render->drawText(highScoreText2);
  render->drawText(highScoreText3);
  render->drawText(highScoreText4);
  render->drawText(highScoreText5);
  }
  render->drawText(mainMenuText);
  render->drawText(exitText);
  //center text in buttons
  centerText(mainMenuText, mainMenuButton);
  centerText(exitText, exitButton);
}

void GameOverScene::getHighScore()
{
  int yourScore = getScore();//gets your score
  std::ifstream inHighScoreFile;
  inHighScoreFile.open("High_Score.txt");
  std::string line;
  int lineScore;//score of the line on file
  if(inHighScoreFile.is_open())
  {
    while(getline(inHighScoreFile,line))
    {
      lineScore = std::stoi(line);
      if (lineScore <= yourScore)
      {
        highScoreVector.push_back(yourScore);
        highScoreVector.push_back(lineScore);
       yourScore = 0;
      }
      else if (lineScore > yourScore)
      {
        highScoreVector.push_back(lineScore);
      }
    }
    inHighScoreFile.close();
  }else{
    std::cout << "Couldn't open High Score" << std::endl;
  }
  std::cout << "High score loaded " << std::endl;
  //opens a outstream and clears the file
std::ofstream outHighScoreFile("High_Score.txt", std::ios::out | std::ios::trunc);
if (outHighScoreFile.is_open())
{
  for (int i = 0; i < 5; i++)//only writes the top 5 scores to the file
  {
  outHighScoreFile << std::to_string(highScoreVector.at(i)) << std::endl;
  }
}else{std::cout << "Couldn't open file " << std::endl;}
  outHighScoreFile.close();
}

SCENES GameOverScene::updateScene(float deltaTime){
  using namespace std::chrono;
  high_resolution_clock::time_point now = high_resolution_clock::now();
  duration<double> time_span = duration_cast<duration<double>>( now - start_time);

  // Checking what key is pressed and compare it to the last time a key was pressed
  if ((inputmgr.isKeyPressed(UP) && time_span.count() > 0.5) && (keyMarker.getMarkerPos() == 2))
  {
      keyMarker.move(0,-190);
      start_time = high_resolution_clock::now();
      keyMarker.setMarkerPos(1);
      mainMenuButton.setTexture(buttonTextureMarked);
      exitButton.setTexture(buttonTextureNotMarked);
  }
  else if((inputmgr.isKeyPressed(DOWN) && time_span.count() > 0.5) && (keyMarker.getMarkerPos() == 1))
  {
      keyMarker.move(0,190);
      start_time = high_resolution_clock::now();
      keyMarker.setMarkerPos(2);
      mainMenuButton.setTexture(buttonTextureNotMarked);
      exitButton.setTexture(buttonTextureMarked);
  }
  else if (inputmgr.isKeyPressed(ENTER))
  {
    if (keyMarker.getMarkerPos() == 1)
    {
      return MAINMENUSCENE;
    }
    else
    {
      return EXITGAME;  //---Change to multiplayerscene when its done
    }
  }
  return GAMESCENE; //Do nothing
}
