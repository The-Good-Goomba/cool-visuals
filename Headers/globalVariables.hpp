//
//  Dithering.hpp
//  visuals
//
//  Created by Matthew  Eatough on 15/1/2022.
//  Copyright © 2022 The Good Goomba. All rights reserved.
//

#ifndef globalVariables_hpp
#define globalVariables_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>

float height;
float width;

// Setting up the navigation bar
sf::RectangleShape navBar;
sf::Color navBGColor;
sf::Color navOutline;

// Window
sf::Color backgroundColor;

// Clock
sf::Clock glock;
int milliseconds;

// Box variables and sizes
int boxTextSize;
sf::Color boxColor;
sf::Color boxOutCol;
sf::Color boxTextCol;




#endif /* globalVariables_hpp */
