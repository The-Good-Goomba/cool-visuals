//
//  Dithering.hpp
//  visuals
//
//  Created by Matthew  Eatough on 15/1/2022.
//  Copyright © 2022 The Good Goomba. All rights reserved.
//

#ifndef boxes_hpp
#define boxes_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <string>

extern float height;
extern int boxTextSize;
extern sf::Color boxColor;
extern sf::Color boxOutCol;
extern sf::Color boxTextCol;

struct boxes
{
    sf::RectangleShape rectangle{sf::Vector2f(height/3,height/15)};
    std::string option = "null";
    sf::Text text;
    int textSize = boxTextSize;
    bool active = false;
    sf::Color color = boxColor;
    sf::Color outlineCol = boxOutCol;
    sf::Color textCol = boxTextCol;
};

#endif /* Boxes_hpp */
