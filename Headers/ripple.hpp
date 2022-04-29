//
//  ripple.hpp
//  visuals
//
//  Created by Matthew  Eatough on 19/1/2022.
//  Copyright © 2022 The Good Goomba. All rights reserved.
//

#ifndef ripple_hpp
#define ripple_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>


// (width*(height*8/9)*4)



class ripple
{
public:
    float damping;
    std::vector<std::vector<float>> buffer1;
    std::vector<std::vector<float>> buffer2;
    std::vector<sf::VertexArray> pixels;
    int width;
    int height;
    int offSetX;
    int offSetY;
    
    
    bool updating;
    
    void setup(int width, int height,int x,int y);
    
    void update();
    
    void drop(int mouseX,int mouseY);
    
    void swapBuf();
    
    void click();
};


#endif /* ripple_hpp */
