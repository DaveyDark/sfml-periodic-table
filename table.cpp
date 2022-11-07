#include "headers/table.h"

bool contains(std::string s1,std::string s2){
    if(s1.find(s2) != std::string::npos)return true;
    return false;
}

periodicTable::periodicTable(float width,float height){
    std::ifstream fJson("periodic_table.json");
    std::stringstream buffer;
    buffer << fJson.rdbuf();
    periodicTable::elements = nlohmann::json::parse(buffer.str());

    periodicTable::elementFont.loadFromFile("assets/UbuntuMono-R.ttf");
    periodicTable::text.setFont(periodicTable::elementFont);
    periodicTable::text.setFillColor(sf::Color::Black);

    periodicTable::headingFont.loadFromFile("assets/Sauce Code Pro Nerd Font Complete.ttf");
    periodicTable::heading.setFont(periodicTable::headingFont);
    periodicTable::heading.setString("Periodic Table");
    periodicTable::heading.setCharacterSize(128.f);
    periodicTable::heading.setFillColor(sf::Color::White);
    periodicTable::heading.setPosition(width / 2 - (periodicTable::heading.getGlobalBounds().width/2), periodicTable::MARGIN_Y/4);
}

void periodicTable::render(sf::RenderWindow *win,sf::Vector2f mousePos,sf::Color bg){
    for(auto element : periodicTable::elements["elements"]){
        //make rectangle for element
        sf::RectangleShape rect(sf::Vector2f(periodicTable::SIZE,periodicTable::SIZE));
        rect.setPosition(periodicTable::MARGIN_X + (((int)element["xpos"]-1)*(periodicTable::SIZE + periodicTable::PADDING)),periodicTable::MARGIN_Y + (((int)element["ypos"]-1)*(periodicTable::SIZE + periodicTable::PADDING)));

        //color coordination
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
        rect.setOutlineColor(color);
        rect.setOutlineThickness(-2.f);
        rect.setFillColor(bg);
        /* rect.setFillColor(sf::Color(color.r,color.g,color.b,50)); */
        /* rect.setFillColor(color); */

        //write text
        periodicTable::text.setString((std::string)element["symbol"]);
        periodicTable::text.setCharacterSize(24);
        periodicTable::text.setPosition(rect.getPosition().x + (periodicTable::SIZE/2 - periodicTable::text.getGlobalBounds().width/2),rect.getPosition().y + (periodicTable::SIZE/2 - periodicTable::text.getGlobalBounds().height));
        /* periodicTable::text.setFillColor(sf::Color::Black); */
        periodicTable::text.setFillColor(color);

        //check hover
        if(periodicTable::isHovering(mousePos,rect.getPosition(),element)){
            /* rect.setOutlineColor(color); */
            /* rect.setOutlineThickness(-2.f); */
            /* rect.setFillColor(bg); */
            /* periodicTable::text.setFillColor(color); */
            rect.setOutlineThickness(0.f);
            rect.setFillColor(color);
            periodicTable::text.setFillColor(bg);
        }

        //drawing
        win->draw(rect);
        win->draw(periodicTable::heading);
        win->draw(periodicTable::text);
    }
}

void periodicTable::onClick(sf::Vector2f mousePos){
    for(auto element : periodicTable::elements["elements"]){
        sf::Vector2f pos = sf::Vector2f(periodicTable::MARGIN_X + (((int)element["xpos"]-1)*(periodicTable::SIZE + periodicTable::PADDING)),periodicTable::MARGIN_Y + (((int)element["ypos"]-1)*(periodicTable::SIZE + periodicTable::PADDING)));
        if(periodicTable::isHovering(mousePos,pos,element)){
            //do something
        }
    }
}

bool periodicTable::isHovering(sf::Vector2f mousePos,sf::Vector2f pos,nlohmann::json element){
        if(mousePos.x >= pos.x && mousePos.x <= pos.x+periodicTable::SIZE){
            if(mousePos.y >= pos.y && mousePos.y <= pos.y+periodicTable::SIZE){
                return true;
            }
        }
        return false;
}

