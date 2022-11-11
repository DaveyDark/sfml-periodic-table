#include "headers/popup.h"
#include <SFML/Graphics/RenderWindow.hpp>

Popup::Popup(nlohmann::json element,sf::Color bg,sf::Color color){
    this->element = element;
    this->bg = sf::Color(color.r/4,color.g/4,color.b/4);
    this->color = color;

    this->WINDOW_WIDTH = 480;
    this->WINDOW_HEIGHT = 1000;

    this->headingFont.loadFromFile("src/assets/Sauce Code Pro Nerd Font Complete.ttf");
    this->font.loadFromFile("src/assets/Roboto-Light.ttf");
    this->text.setFont(this->font);
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
    rect.setPosition(this->WINDOW_WIDTH/2 - (rect.getSize().x/2),175.f);
    rect.setFillColor(this->color);
    this->text.setCharacterSize(96.f);
    this->text.setFont(this->headingFont);
    this->text.setFillColor(this->bg);
    this->text.setPosition(rect.getPosition().x + (rect.getSize().x/2) - (this->text.getGlobalBounds().width/2),rect.getPosition().y + (rect.getSize().y/2) - (this->text.getGlobalBounds().height));
    this->win->draw(rect);
    this->win->draw(this->text);

    rect.setFillColor(sf::Color(30,30,30,120));
    rect.setSize(sf::Vector2f(this->WINDOW_WIDTH - 60.f,475.f));
    rect.setPosition(30.f,450.f);
    this->win->draw(rect);

    this->text.setCharacterSize(22.f);
    this->text.setFillColor(sf::Color::White);
    this->text.setFont(this->font);

    this->str.str("");
    this->str << "Atomic Number : " << this->element["number"];
    this->text.setPosition(45.f,465.f);
    this->text.setString(this->str.str());
    this->win->draw(this->text);

    this->str.str("");
    this->str << "Mass : " << this->element["atomic_mass"];
    this->text.setPosition(45.f,515.f);
    this->text.setString(this->str.str());
    this->win->draw(this->text);

    this->str.str("");
    this->str << "Category : " << (std::string)this->element["category"];
    this->text.setPosition(45.f,565.f);
    this->text.setString(this->str.str());
    this->win->draw(this->text);

    this->str.str("");
    this->str << "Configuration : " << (std::string)this->element["electron_configuration_semantic"];
    this->text.setPosition(45.f,615.f);
    this->text.setString(this->str.str());
    this->win->draw(this->text);

    this->str.str("");
    this->str << "Appearance : " << this->element["appearance"];
    this->text.setPosition(45.f,665.f);
    this->text.setString(this->str.str());
    this->win->draw(this->text);

    this->str.str("");
    this->str << "Phase : " << (std::string)this->element["phase"];
    this->text.setPosition(45.f,715.f);
    this->text.setString(this->str.str());
    this->win->draw(this->text);

    this->str.str("");
    this->str << "Melting Point : " << this->element["melt"] << " K";
    this->text.setPosition(45.f,765.f);
    this->text.setString(this->str.str());
    this->win->draw(this->text);

    this->str.str("");
    this->str << "Boiling Point : " << this->element["boil"] << " K";
    this->text.setPosition(45.f,815.f);
    this->text.setString(this->str.str());
    this->win->draw(this->text);

    this->str.str("");
    this->str << "Density : " << this->element["density"] << " g/cm3";
    this->text.setPosition(45.f,865.f);
    this->text.setString(this->str.str());
    this->win->draw(this->text);

    this->win->draw(this->heading);

    this->win->display();
}

sf::RenderWindow* Popup::update(sf::RenderWindow *mainWin){
    while(this->win->pollEvent(this->ev)){
        if(this->ev.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))return mainWin;
        if(this->ev.type == sf::Event::Closed)return mainWin;
    }
    return nullptr;
}

Popup::~Popup(){
    delete this->win;
}



