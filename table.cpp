#include "headers/table.h"
#include "headers/popup.h"

bool contains(std::string s1,std::string s2){
    if(s1.find(s2) != std::string::npos)return true;
    return false;
}

periodicTable::periodicTable(float width,float height){
    std::ifstream fJson("periodic_table.json");
    std::stringstream buffer;
    buffer << fJson.rdbuf();
    this->elements = nlohmann::json::parse(buffer.str());

    this->elementFont.loadFromFile("assets/UbuntuMono-R.ttf");
    this->text.setFont(this->elementFont);
    this->text.setFillColor(sf::Color::Black);

    this->headingFont.loadFromFile("assets/Sauce Code Pro Nerd Font Complete.ttf");
    this->heading.setFont(this->headingFont);
    this->heading.setString("Periodic Table");
    this->heading.setCharacterSize(128.f);
    this->heading.setFillColor(sf::Color::White);
    this->heading.setPosition(width / 2 - (this->heading.getGlobalBounds().width/2), this->MARGIN_Y/4);

    this->popup = nullptr;
    this->bg = sf::Color::Black;
}

sf::Color periodicTable::getColor(nlohmann::json element){
        sf::Color color;
        if(contains(element["category"] , "diatomic nonmetal"))color = sf::Color(0, 181, 237);
        else if(contains(element["category"],"alkali metal"))color = sf::Color(217, 101, 96);
        else if(contains(element["category"] , "actinide"))color = sf::Color(235, 89, 156);
        else if(contains(element["category"] , "alkaline earth metal"))color = sf::Color(253, 192, 0);
        else if(contains(element["category"] , "lanthanide"))color = sf::Color(232, 62, 143);
        else if(contains(element["category"] , "metalloid"))color = sf::Color(63, 170, 51);
        else if(contains(element["category"] , "noble gas"))color = sf::Color(195, 128, 181);
        else if(contains(element["category"] , "polyatomic nonmetal"))color = sf::Color(0,181,237);
        else if(contains(element["category"] , "post-transition metal"))color = sf::Color(168, 200, 12);
        else if(contains(element["category"] , "transition metal"))color = sf::Color(255, 239, 33);

        return color;
}

void periodicTable::updateEvents(sf::RenderWindow *win){
        if(this->popup == nullptr)win->close();
        else {
            delete this->popup;
            this->popup = nullptr;
        }
}

void periodicTable::render(sf::RenderWindow *win,sf::Vector2f mousePos,sf::Color bg){
    for(auto element : this->elements["elements"]){
        //make rectangle for element
        sf::RectangleShape rect(sf::Vector2f(this->SIZE,this->SIZE));
        rect.setPosition(this->MARGIN_X + (((int)element["xpos"]-1)*(this->SIZE + this->PADDING)),this->MARGIN_Y + (((int)element["ypos"]-1)*(this->SIZE + this->PADDING)));

        //color coordination
        this->bg = bg;
        sf::Color color = this->getColor(element); 
        rect.setOutlineColor(color);
        rect.setOutlineThickness(-2.f);
        rect.setFillColor(bg);
        /* rect.setFillColor(sf::Color(color.r,color.g,color.b,50)); */
        /* rect.setFillColor(color); */

        //write text
        this->text.setString((std::string)element["symbol"]);
        this->text.setCharacterSize(24);
        this->text.setPosition(rect.getPosition().x + (this->SIZE/2 - this->text.getGlobalBounds().width/2),rect.getPosition().y + (this->SIZE/2 - this->text.getGlobalBounds().height));
        /* this->text.setFillColor(sf::Color::Black); */
        this->text.setFillColor(color);

        //check hover
        if(this->isHovering(mousePos,rect.getPosition(),element)){
            /* rect.setOutlineColor(color); */
            /* rect.setOutlineThickness(-2.f); */
            /* rect.setFillColor(bg); */
            /* this->text.setFillColor(color); */
            rect.setOutlineThickness(0.f);
            rect.setFillColor(color);
            this->text.setFillColor(bg);
        }

        //drawing
        win->draw(rect);
        win->draw(this->heading);
        win->draw(this->text);
        if(this->popup != nullptr){
            this->popup->render();
            if(this->popup->update(win) != nullptr)this->updateEvents(win);
        }
    }
}

void periodicTable::onClick(sf::Vector2f mousePos){
    for(nlohmann::json element : this->elements["elements"]){
        sf::Vector2f pos = sf::Vector2f(this->MARGIN_X + (((int)element["xpos"]-1)*(this->SIZE + this->PADDING)),this->MARGIN_Y + (((int)element["ypos"]-1)*(this->SIZE + this->PADDING)));
        if(this->isHovering(mousePos,pos,element)){
            if(this->popup == nullptr)this->popup = new Popup(element,this->bg,this->getColor(element));
            else this->popup->refresh(element,this->getColor(element));
        }
    }
}

bool periodicTable::isHovering(sf::Vector2f mousePos,sf::Vector2f pos,nlohmann::json element){
        if(mousePos.x >= pos.x && mousePos.x <= pos.x+this->SIZE){
            if(mousePos.y >= pos.y && mousePos.y <= pos.y+this->SIZE){
                return true;
            }
        }
        return false;
}

