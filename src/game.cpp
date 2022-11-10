#include "headers/game.h"

Game::Game(){
    this->initVariables();
    this->initWindow();
}

Game::~Game(){
    delete this->window;
}

void Game::initVariables(){
    this->WINDOW_HEIGHT = 1000;
    this->WINDOW_WIDTH = 1280;
    this->window = nullptr;
    this->table = new periodicTable(this->WINDOW_WIDTH,this->WINDOW_HEIGHT);
    this->BACKGROUND_COLOR = sf::Color(30,30,30);
}

void Game::initWindow(){
    this->videoMode.height = this->WINDOW_HEIGHT;
    this->videoMode.width = this->WINDOW_WIDTH;
    this->window = new sf::RenderWindow(this->videoMode,"chem-project",sf::Style::Close);
}

const bool Game::isRunning() const{
    return this->window->isOpen();
}

void Game::update(){
    this->updateMousePos();
    this->pollEvents();
}

void Game::updateMousePos(){

    this->mousePos = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
}

void Game::pollEvents(){
    while(this->window->pollEvent(this->ev)){
        if(this->ev.type == sf::Event::Closed) this->window->close();
        else if(this->ev.type == sf::Event::MouseButtonPressed) this->table->onClick(this->mousePos);
        else if(this->ev.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))this->table->updateEvents(this->window);
    }
}

void Game::render(){
    this->window->clear(this->BACKGROUND_COLOR);

    this->table->render(this->window,this->mousePos,this->BACKGROUND_COLOR);
    
    this->window->display();
}

