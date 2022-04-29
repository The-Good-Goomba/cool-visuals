//
//  checkBox.hpp
//  visuals
//
//  Created by Matthew  Eatough on 19/1/2022.
//  Copyright © 2022 The Good Goomba. All rights reserved.
//

#ifndef checkBox_hpp
#define checkBox_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <array>

class checkBox
{
public:
    sf::RectangleShape outer;
    sf::VertexArray check{sf::VertexArray(sf::TriangleStrip,6)};
    std::array<float,6> pointX;
    std::array<float,6> pointY;
    std::array<float,4> M;
    
    float animationPhase;
    bool animating;
    bool checked;
    
    void startUp(float x, float y, float size);
    
    bool touchy(float mouseX, float mouseY);
    
    void animate(bool click);
    
};

#endif /* checkBox_hpp */
