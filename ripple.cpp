//
//  ripple.cpp
//  visuals
//
//  Created by Matthew  Eatough on 19/1/2022.
//  Copyright © 2022 The Good Goomba. All rights reserved.
//

#include "Headers/ripple.hpp"
#include <array>
#include <iostream>

void ripple::setup(int w, int h,int offX,int offY)
{
    width = w;
    height = h;
    
    offSetX = offX;
    offSetY = offY;
    
    std::vector<float> temp(height,0);
    
    buffer1.clear();
    buffer2.clear();
    for(int i=0;i<width;i++)
    {
        buffer1.push_back(temp);
        buffer2.push_back(temp);
    }
    
    
    buffer2[width/2][height/2] = 255;
    
    for(int x=1;x<width-1;x++)
    {
        for(int y=1;y<height-1;y++)
        {
            sf::Vertex vertex1;
            vertex1.position = sf::Vector2f(x+offSetX, y+offSetY);
            vertex1.color = sf::Color(buffer2[x][y],buffer2[x][y],buffer2[x][y]);//grayscale
            sf::VertexArray pixel;
            pixel.append(vertex1);
            pixels.push_back(pixel);
        }
    }
    

    
    
    updating = false;
    
    damping = 0.999;
}

void ripple::drop(int mouseX,int mouseY)
{
    mouseY -= offSetY;
    mouseX -= offSetX;
    
    if (mouseY > 0 && mouseX>0 && mouseY<height && mouseX < width)
    {
        buffer1.at(mouseX).at(mouseY) = 255;
    }
}

void ripple::update()
{
    updating = false;
    for(int x=1;x<width-1;x++)
    {
        for(int y=1;y<height-1;y++)
        {
            
            buffer2[x][y] = (buffer1[x-1][y  ] +
                             buffer1[x+1][y  ] +
                             buffer1[x  ][y+1] +
                             buffer1[x  ][y-1])/2 - buffer2[x][y];
            buffer2[x][y] = buffer2[x][y] * damping;
            
            if (buffer2[x][y] < 1)
                buffer2[x][y] = 0;
            
            if (buffer1[x][y] > 0)
                updating = true;

            if (buffer2[x][y] > 255)
                buffer2[x][y] = 255;
        }
    }
    
    pixels.clear();
    
    for(int x=1;x<width-1;x++)
    {
        for(int y=1;y<height-1;y++)
        {
            sf::Vertex vertex1;
            vertex1.position = sf::Vector2f(x+offSetX, y+offSetY);
            vertex1.color = sf::Color(buffer2[x][y], buffer2[x][y], buffer2[x][y]);//grayscale
            sf::VertexArray pixel;
            pixel.append(vertex1);
            pixels.push_back(pixel);
        }
    }
    
    swapBuf();

}

void ripple::swapBuf()
{
    buffer2.swap(buffer1);
}
