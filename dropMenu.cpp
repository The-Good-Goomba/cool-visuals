//
//  Dithering.cpp
//  visuals
//
//  Created by Matthew  Eatough on 15/1/2022.
//  Copyright © 2022 The Good Goomba. All rights reserved.
//

#include <iostream>
#include "Headers/dropMenu.hpp"
#include "Headers/boxes.hpp"
#include "ResourcePath.hpp"

extern sf::Color boxColor;
extern int boxTextSize;
extern sf::Color boxTextCol;

void dropMenu::drawThings()
{
    background.clear(sf::Color::Transparent);
    
    background.draw(box);
    background.draw(arrowBox);
    background.draw(arrow);
    background.draw(activeText);
    
    for (auto& box:apps){
        background.draw(box.rectangle);
        background.draw(box.text);
    }
    
    background.display();
    
    things.setTexture(background.getTexture());
}

void dropMenu::startUp(float x,float y,float h,float w)
{
    // Declare variables
    color = sf::Color(57, 59, 58);
    box = sf::RectangleShape(sf::Vector2f(height/3,height/15));
    outlineCol = sf::Color(53,53,54);
    
    posX = x;
    posY = y;
    
    if(!background.create(w, h))
        return EXIT_FAILURE;
    
    activeApp = 0;
    activeText.setString(app[activeApp]);
    
    arrowBox = sf::RectangleShape(sf::Vector2f(height/15,height/15));
    arrowCol = sf::Color(255,255,255);
    arrowBGCol = sf::Color(0,0,0);
    arrowThicc = 4;
    arrowSize = 10;
    arrow = sf::VertexArray(sf::TriangleStrip, 6);
    
    animation = false;
    animationStage = 0;
    direction = true;
    
    // Drop menu box
    box.setOrigin(0, box.getGlobalBounds().height/2);
    box.setPosition(x, y);
    box.setFillColor(color);
    box.setOutlineColor(outlineCol);
    box.setOutlineThickness(2);
    
    // Text in drop menu box
    activeText.setFont(font);
    activeText.setCharacterSize(boxTextSize);
    sf::Color actTxtCol = boxTextCol;
    actTxtCol.a = 255;
    activeText.setFillColor(actTxtCol);
    activeText.setOrigin(0, activeText.getGlobalBounds().top*0.6);
    activeText.setPosition(box.getPosition().x+5, box.getPosition().y);
    
    // Arrow box
    arrowBox.setOrigin(arrowBox.getGlobalBounds().width, arrowBox.getGlobalBounds().height/2);
    arrowBox.setPosition(box.getPosition().x+box.getGlobalBounds().width, box.getPosition().y);
    arrowBox.setFillColor(arrowBGCol);
    arrowBox.setOutlineColor(outlineCol);
    arrowBox.setOutlineThickness(2);
    
    // Arrow itself
    arrow[0].position = sf::Vector2f(arrowBox.getPosition().x-arrowBox.getGlobalBounds().width/4.0,
                                           arrowBox.getPosition().y - arrowThicc - arrowSize);
    arrow[1].position = sf::Vector2f(arrowBox.getPosition().x-arrowBox.getGlobalBounds().width/4.0,
                                           arrowBox.getPosition().y+arrowThicc - arrowSize);
    
    arrow[2].position = sf::Vector2f(arrowBox.getPosition().x-arrowBox.getGlobalBounds().width/2.0,
                                           arrowBox.getPosition().y-arrowThicc + arrowSize);
    arrow[3].position = sf::Vector2f(arrowBox.getPosition().x-arrowBox.getGlobalBounds().width/2.0,
                                           arrowBox.getPosition().y+arrowThicc + arrowSize);
    
    arrow[4].position = sf::Vector2f(arrowBox.getPosition().x-arrowBox.getGlobalBounds().width*3/4.0,
                                           arrowBox.getPosition().y-arrowThicc - arrowSize);
    arrow[5].position = sf::Vector2f(arrowBox.getPosition().x-arrowBox.getGlobalBounds().width*3/4.0,
                                           arrowBox.getPosition().y+arrowThicc - arrowSize);
    // Setting all the colors of the arrow
    for(int i = 0;i<arrow.getVertexCount();i++){
        arrow[i].color = arrowCol;
    }
    
    arrowOrigin = arrow;
    
    // Setting the different apps
    for (int i = 0; i<this->app.size();i++){
        struct boxes sus;
        sus.option = app[i];
        sus.text.setString(app[i]);
        sus.text.setFont(font);
        sus.text.setCharacterSize(sus.textSize);
        sus.text.setFillColor(sus.textCol);
        sus.text.setOrigin(0, sus.text.getGlobalBounds().top*0.6);
        sus.rectangle.setOrigin(0, sus.rectangle.getGlobalBounds().height*0.5);
        sus.rectangle.setFillColor(sus.color);
        sus.rectangle.setOutlineColor(sus.outlineCol);
        sus.rectangle.setOutlineThickness(2);
        sus.rectangle.setPosition(box.getPosition().x, box.getPosition().y+box.getGlobalBounds().height*(i+1));
        sus.text.setPosition(sus.rectangle.getPosition().x+5, sus.rectangle.getPosition().y);
        apps.push_back(sus);
    }

    if(!font.loadFromFile(resourcePath()+"Resources/sansation.ttf"))
        return EXIT_FAILURE;
   
    drawThings();
}
    
void dropMenu::clickArrow(bool click)
{
    if(click){
        // Down is true while up is false
        direction = !direction;
        
        if(animation == false){
            animation = true;
        }
    } else {
    
        // 0 means that it is down and 1 means its up
        if (direction){
            animationStage -= 0.1;
            if (animationStage <= 0){
                animationStage = 0;
                animation = false;
            }
        } else {
            animationStage += 0.1;
            if (animationStage >= 1){
                animationStage = 1;
                animation = false;
            }
        }
        
        for(int i; i<arrow.getVertexCount();i++){
            if (i != 2 && i != 3)
                arrow[i].position = sf::Vector2f(arrowOrigin[i].position.x,arrowOrigin[i].position.y+arrowSize*2*animationStage);
            else
                arrow[i].position = sf::Vector2f(arrowOrigin[i].position.x,arrowOrigin[i].position.y-arrowSize*2*animationStage);
        }
        
        for (auto& i:apps){
            i.color.a = animationStage*255;
            i.outlineCol.a = animationStage*255;
            i.textCol.a = animationStage*100;
            i.rectangle.setFillColor(i.color);
            i.rectangle.setOutlineColor(i.outlineCol);
            i.text.setFillColor(i.textCol);
        }
        
    }
    
    background.clear(sf::Color::Transparent);
    
    background.draw(box);
    background.draw(arrowBox);
    background.draw(arrow);
    background.draw(activeText);
    
    for (auto& box:apps){
        background.draw(box.rectangle);
        background.draw(box.text);
    }
    
    background.display();

}

void dropMenu::clickBox(int i)
{
    for (int o = 0; o<apps.size();o++){
        apps[o].active = false;
    }
    apps[i].active = true;
    activeApp = i;
    
    activeText.setString(app[i]);
    
    drawThings();
}

bool dropMenu::touchArrow(int mouseX, int mouseY)
{
    if(mouseX < arrowBox.getPosition().x &&
        mouseX > arrowBox.getPosition().x - arrowBox.getGlobalBounds().width &&
        mouseY < arrowBox.getPosition().y + arrowBox.getGlobalBounds().height/2.0 &&
        mouseY > arrowBox.getPosition().y - arrowBox.getGlobalBounds().height/2.0)
        return true;
    else
        return false;
}

bool dropMenu::touchBox(int mouseX, int mouseY, int i)
{
    sf::IntRect box( apps[i].rectangle.getPosition().x,apps[i].rectangle.getPosition().y-apps[i].rectangle.getGlobalBounds().height/2.0,
        apps[i].rectangle.getGlobalBounds().width,apps[i].rectangle.getGlobalBounds().height);
    if(box.contains(mouseX, mouseY))
        return true;
    else
        return false;
}
