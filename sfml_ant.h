#pragma once
#include <SFML-3.0.0\include\SFML\Graphics.hpp>
#include "ant.h"
#include "anthill.h"
class SFMLAnt {
private:
    sf::CircleShape shape;
    Ant* ant;
    sf::Font font;
    sf::Text roleText;
    
public:
    SFMLAnt(Ant* ant, float x, float y);
    void update();
    void draw(sf::RenderWindow& window);
    Ant* getAnt() const { return ant; }
    void setPosition(float x, float y);
    sf::Vector2f getPosition() const;
};

class SFMLAnthill {
private:
    sf::CircleShape shape;
    Anthill* anthill;
    std::vector<SFMLAnt> sfmlAnts;
    
public:
    SFMLAnthill(Anthill* anthill, float x, float y);
    void update();
    void draw(sf::RenderWindow& window);
    void addAnt(SFMLAnt& ant);
    std::vector<SFMLAnt>& getSFMLAnts() { return sfmlAnts; }
};