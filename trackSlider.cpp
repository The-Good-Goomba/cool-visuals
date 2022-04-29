//
//  trackSlider.cpp
//  visuals
//
//  Created by Matthew  Eatough on 15/1/2022.
//  Copyright © 2022 The Good Goomba. All rights reserved.
//

#include "Headers/trackSlider.hpp"
#include "ResourcePath.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

trackSlider::trackSlider(float min,float max,float x,float y,float w, float h,float r,std::string msg,int fon)
{
    if (!font.loadFromFile(resourcePath()+"Resources/sansation.ttf"))
        return EXIT_FAILURE;
    
    isPressed = false;
    
    minVal = min;
    maxVal = max;
    
    rect = sf::RectangleShape(sf::Vector2f(w,h));
    rect.setOrigin(0, h*0.5);
    rect.setPosition(x, y);
    
    for (int i = 0; i<2;i++){
    ends[i].setRadius(h/2);
    ends[i].setOrigin(h/2, h/2);
    ends[i].setFillColor(sf::Color::Black);
    }
    ends[0].setPosition(x, y);
    ends[1].setPosition(x+w, y);
    
    rect.setFillColor(sf::Color::Black);
    
    bigCir.setRadius(r);
    bigCir.setOrigin(r, r);
    bigCir.setPosition(x+w/2, y);
    bigCir.setOutlineThickness(1);
    
    bigCir.setFillColor(sf::Color(86,87,87));
    bigCir.setOutlineColor(sf::Color(41,42,42));
    
    curVal = (maxVal-minVal)*0.5 + minVal;
    
    message.setString(msg);
    message.setCharacterSize(fon);
    message.setFont(font);
    message.setOrigin(message.getGlobalBounds().width/2, 0);
    message.setPosition(rect.getPosition().x+(rect.getGlobalBounds().width/2.0), rect.getPosition().y+20);
    
}

bool trackSlider::touchCircle(int mouseX, int mouseY)
{
    if (((mouseX-bigCir.getPosition().x)*
        (mouseX-bigCir.getPosition().x) +
        (mouseY-bigCir.getPosition().y)*
        (mouseY-bigCir.getPosition().y) )< bigCir.getRadius()*bigCir.getRadius()*2)
        return true;
    else
        return false;
}

void trackSlider::move(int mouseX, int mouseY)
{
    //if (((mouseX-bigCir.getPosition().x)*
    //    (mouseX-bigCir.getPosition().x) +
    //    (mouseY-bigCir.getPosition().y)*
    //    (mouseY-bigCir.getPosition().y) )< bigCir.getRadius()*bigCir.getRadius()*2)
    //{
        bigCir.setPosition(mouseX,bigCir.getPosition().y);
        
        if (bigCir.getPosition().x < rect.getPosition().x)
            bigCir.setPosition(rect.getPosition());
        
        if (bigCir.getPosition().x > rect.getPosition().x + rect.getGlobalBounds().width)
            bigCir.setPosition(rect.getPosition().x +rect.getGlobalBounds().width, bigCir.getPosition().y);
    //}
    
    curVal = ((bigCir.getPosition().x - rect.getPosition().x)/rect.getGlobalBounds().width)*(maxVal - minVal) + minVal;
}

/*
 if (((sf::Mouse::getPosition(window).x-dith.slider.bigCir.getPosition().x)*
     (sf::Mouse::getPosition(window).x-dith.slider.bigCir.getPosition().x) +
     (sf::Mouse::getPosition(window).y-dith.slider.bigCir.getPosition().y)*
     (sf::Mouse::getPosition(window).y-dith.slider.bigCir.getPosition().y) )< dith.slider.bigCir.getRadius()*dith.slider.bigCir.getRadius())
 {
     dith.slider.bigCir.setPosition(sf::Mouse::getPosition(window).x,
                                    dith.slider.bigCir.getPosition().y);
     
     if (dith.slider.bigCir.getPosition().x < dith.slider.rect.getPosition().x)
         dith.slider.bigCir.setPosition(dith.slider.rect.getPosition());
     
     if (dith.slider.bigCir.getPosition().x > dith.slider.rect.getPosition().x + dith.slider.rect.getGlobalBounds().width)
         dith.slider.bigCir.setPosition(dith.slider.rect.getPosition().x +dith.slider.rect.getGlobalBounds().width, dith.slider.bigCir.getPosition().y);
 }
 */
