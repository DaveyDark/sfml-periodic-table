#include "headers/popup.h"
#include <SFML/Graphics/RenderWindow.hpp>

Popup::Popup(nlohmann::json element,sf::Color bg,sf::Color color){
    this->element = element;
    this->bg = sf::Color(color.r/4,color.g/4,color.b/4);
    this->color = color;

    this->WINDOW_WIDTH = 480;
    this->WINDOW_HEIGHT = 1000;

    this->headingFont.loadFromFile("assets/Sauce Code Pro Nerd Font Complete.ttf");
    this->font.loadFromFile("assets/Sauce Code Pro Nerd Font Complete.ttf");
    this->text.setFont(Popup::font);
    this->heading.setString((std::string)element["name"]);
    this->heading.setFont(Popup::headingFont);
    this->heading.setCharacterSize(48.f);
    this->heading.setFillColor(sf::Color::White);

    this->win = new sf::RenderWindow(sf::VideoMode(Popup::WINDOW_WIDTH,Popup::WINDOW_HEIGHT),"Periodic Table",sf::Style::Close);

    this->heading.setPosition(this->WINDOW_WIDTH/2 - (this->heading.getGlobalBounds().width/2),50.f);
}

void Popup::refresh(nlohmann::json element, sf::Color color){
    this->element = element;
    this->color = color;
    this->bg = sf::Color(color.r/4,color.g/4,color.b/4);
    this->heading.setString((std::string)element["name"]);
    this->heading.setFillColor(sf::Color::White);
    this->heading.setPosition(this->WINDOW_WIDTH/2 - (this->heading.getGlobalBounds().width/2),50.f);
}

void Popup::render(){
    if(this->win == nullptr)return;
    this->win->clear(this->bg);

    this->text.setString((std::string)this->element["symbol"]);
    sf::RectangleShape rect = sf::RectangleShape(sf::Vector2f(150.f,150.f));
    rect.setPosition(this->WINDOW_WIDTH/2 - (rect.getSize().x/2),125.f);
    rect.setFillColor(this->color);
    this->text.setCharacterSize(96.f);
    this->text.setPosition(rect.getPosition().x + (rect.getSize().x/2) - (this->text.getGlobalBounds().width/2),rect.getPosition().y + (rect.getSize().y/2) - (this->text.getGlobalBounds().height));
    this->text.setFillColor(this->bg);
    this->win->draw(rect);
    this->win->draw(this->text);

    rect.setFillColor(sf::Color(30,30,30,100));
    rect.setSize(sf::Vector2f(this->WINDOW_WIDTH - 60.f,600.f));
    rect.setPosition(30.f,350.f);
    this->win->draw(rect);

    this->win->draw(this->heading);

    this->win->display();
}

