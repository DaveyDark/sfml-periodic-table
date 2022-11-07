#ifndef POPUP_H
#define POPUP_H

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <nlohmann/json.hpp>

class Popup{
    private:
        sf::Font font;
        sf::Font headingFont;
        sf::Text heading;
        sf::Text text;
        nlohmann::json element;
        sf::Color bg;
        sf::Color color;
        sf::RenderWindow *win;

        float WINDOW_WIDTH,WINDOW_HEIGHT;
    public:
        Popup(nlohmann::json element,sf::Color bg,sf::Color color);
        ~Popup();

        void render();
        void refresh(nlohmann::json element, sf::Color color);
};

#endif

