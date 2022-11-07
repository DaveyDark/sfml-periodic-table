#ifndef TABLE_H
#define TABLE_H

#include "popup.h"
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>

class periodicTable{
    private:
        float SIZE = 64.f,PADDING=6.f,MARGIN_X=12.f,MARGIN_Y=212.f;
        sf::Font elementFont;
        sf::Font headingFont;
        sf::Text text;
        sf::Text heading;
        sf::Color bg;
        Popup *popup;

        bool isHovering(sf::Vector2f mousePos,sf::Vector2f pos,nlohmann::json element);
        sf::Color getColor(nlohmann::json element);
    public:
        periodicTable(float width,float height);
        ~periodicTable();

        void render(sf::RenderWindow *win,sf::Vector2f mousePos,sf::Color bg);
        void update(sf::Vector2f mousePos);
        void onClick(sf::Vector2f mousePos);

        nlohmann::json elements;
};

#endif
