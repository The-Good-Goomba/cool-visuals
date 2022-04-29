//
//  dithering.hpp
//  visuals
//
//  Created by Matthew  Eatough on 15/1/2022.
//  Copyright © 2022 The Good Goomba. All rights reserved.
//

#ifndef dithering_hpp
#define dithering_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include "trackSlider.hpp"
#include "checkBox.hpp"

extern float height;
extern float width;

class dithering
{
public:
    sf::RenderTexture background;
    sf::Sprite spt1;
    sf::Sprite spt2;
    sf::Texture tex1;
    sf::Texture tex2;
    sf::Image img2;
    sf::Image img1;
    trackSlider slider{1, 255, width/4, height/18 - 10, 520,12, 12,"Color range",36};
    checkBox greyScale;
    sf::Text gray;
    
    float factor;
    bool toUpdate;
    bool grey;
    int offX, offY;

    void startUp(float width, float height,float offSetX,float offSetY);

    void update();
    
    sf::Color checkCol(sf::Color col);
};

#endif /* dithering_hpp */
