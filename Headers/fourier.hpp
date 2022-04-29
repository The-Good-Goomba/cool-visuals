//
//  fourier.hpp
//  visuals
//
//  Created by Matthew  Eatough on 25/1/2022.
//  Copyright © 2022 The Good Goomba. All rights reserved.
//

#ifndef fourier_hpp
#define fourier_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <deque>
#include <vector>
#include <algorithm>
#include "trackSlider.hpp"
#include "dropMenu.hpp"

class fourier
{
public:
    
    struct waves
    {
        float re;
        float im;
        float amp;
        float freq;
        float phase;
        
    };
    
    bool regular;
    float time;
    float offX;
    float offY;
    std::deque<float> wave;
    std::deque<sf::Vector2f> path;
    std::vector<float> y;
    std::vector<float> x;
    std::vector<waves> fourierY;
    std::vector<waves> fourierX;
    sf::RenderTexture background;
    trackSlider slider{1, 10, 1920/4, 1080/18 - 10, 520,12, 12,"amount",36};
    dropMenu menu;
    
    fourier(int height, int width,float offSetX, float offSetY);
    
    void set(int num);
    
    std::vector<waves> dft(std::vector<float> a);
    
    std::vector<waves> slowSort(std::vector<waves> four);
    
    void update();
    
    sf::Vector2f epicycle(float a,float b,float rotation,std::vector<waves> four);
};

#endif /* fourier_hpp */
