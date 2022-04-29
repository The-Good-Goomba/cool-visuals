//
//  trackSlider.hpp
//  visuals
//
//  Created by Matthew  Eatough on 15/1/2022.
//  Copyright © 2022 The Good Goomba. All rights reserved.
//

#ifndef trackSlider_hpp
#define trackSlider_hpp

#include <stdio.h>
#include <string>
#include <SFML/Graphics.hpp>

class trackSlider
{
public:
    sf::RectangleShape rect;
    sf::CircleShape ends[2];
    sf::CircleShape bigCir;
    sf::Text message;
    sf::Font font;
    
    bool isPressed;
    
    float maxVal;
    float minVal;
    float curVal;
    
    trackSlider(float min,float max,float x,float y,float w, float h,float r,std::string msg,int fontSize);
    
    void move(int mouseX, int mouseY);
    
    bool touchCircle(int mouseX, int mouseY);
};

#endif /* trackSlider_hpp */
