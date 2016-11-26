#include "SFML/System/Clock.hpp"
class Time{
//THIS CLASS IS USED TO CALCULATE TIME BETWEEN FRAMES
public:
  Time(){};
  sf::Time getTimeAndRestart(){
    return clock.restart();
  };

private:
  sf::Clock clock;
};
