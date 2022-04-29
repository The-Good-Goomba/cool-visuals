//
//  Dithering.hpp
//  visuals
//
//  Created by Matthew  Eatough on 15/1/2022.
//  Copyright © 2022 The Good Goomba. All rights reserved.
//

#ifndef dropMenu_hpp
#define dropMenu_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <array>
#include <string>
#include <vector>
#include "boxes.hpp"


class dropMenu
{
public:
    sf::Color color;
    sf::RectangleShape box;
    sf::Color outlineCol;
    std::vector<std::string> app;
    std::vector<boxes> apps;
    sf::Font font;
    
    int activeApp;
    sf::Text activeText;
    
    sf::RectangleShape arrowBox;
    sf::Color arrowCol;
    sf::Color arrowBGCol;
    float arrowThicc;
    float arrowSize;
    sf::VertexArray arrow;
    sf::RenderTexture background;
    sf::Sprite things;
    
    float posX;
    float posY;
    
    bool animation;
    float animationStage;
    bool direction;
    
    sf::VertexArray arrowOrigin;
    
    void startUp(float x,float y,float h,float w);
    
    void drawThings();
    
    void clickArrow(bool click);
    
    void clickBox(int i);
    
    bool touchArrow(int mouseX, int mouseY);
    
    bool touchBox(int mouseX, int mouseY, int i);
};

#endif /* dropManu_hpp */
