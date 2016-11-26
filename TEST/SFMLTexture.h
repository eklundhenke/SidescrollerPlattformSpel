#pragma once
#include "SFML/Graphics.hpp"
#include "iostream"
class SFMLTexture : public sf::Texture{
private:

  //Loads the texure from a file
  void load(std::string path) {
    if (loadFromFile(path)){
      setRepeated(false);
      std::cout << "loaded texture " + path << std::endl;
    }
  }

public:

  //Constructor
  SFMLTexture(std::string filePath){
    load(filePath);
  }
};
