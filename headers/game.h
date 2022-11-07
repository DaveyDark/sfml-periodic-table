#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include "table.h"

class Game{
    private:
        sf::RenderWindow *window;
        sf::RenderWindow *popup;
        sf::VideoMode videoMode;
        sf::Event ev;
        sf::Vector2f mousePos;
        int WINDOW_WIDTH, WINDOW_HEIGHT;
        sf::Color BACKGROUND_COLOR;

        void initWindow();
        void initVariables();
    public:
        Game();
        virtual ~Game();

        const bool isRunning()const;
        periodicTable *table;


        void update();
        void updateMousePos();
        void pollEvents();
        void render();

};

#endif

