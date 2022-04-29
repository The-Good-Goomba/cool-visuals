//
//  dithering.cpp
//  visuals
//
//  Created by Matthew  Eatough on 15/1/2022.
//  Copyright © 2022 The Good Goomba. All rights reserved.
//

#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"
#include "Headers/dithering.hpp"
#include "Headers/checkBox.hpp"
#include <cmath>
#include <iostream>


void dithering::startUp(float width, float height,float offSetX,float offSetY)
{
    if(!background.create(width, height))
        return EXIT_FAILURE;
    
    offX = offSetX;
    offY = offSetY;
    
    greyScale.startUp(width*0.6, height/18,60);
    
    gray.setString("Greyscale?");
    gray.setCharacterSize(36);
    gray.setFont(slider.font);
    gray.setPosition(greyScale.outer.getPosition().x+greyScale.outer.getGlobalBounds().width+20,
                     height/18 - gray.getGlobalBounds().height*0.7);
    
    if(!img1.loadFromFile(resourcePath()+"Resources/doge.jpeg"))
        return EXIT_FAILURE;
    img2.create(img1.getSize().x, img1.getSize().y);
    img2.copy(img1, 0, 0);
    tex1.loadFromImage(img1);
    tex1.setSmooth(true);
    tex2.loadFromImage(img2);
    tex2.setSmooth(true);
    spt1.setTexture(tex1);
    spt2.setTexture(tex2);
    
    float ratio = width/(height*8/9);

    spt2.setTextureRect(sf::IntRect(img1.getSize().y*0.4,0,img1.getSize().y*ratio*0.5,img1.getSize().y));
    spt1.setTextureRect(sf::IntRect(img1.getSize().y*0.4,0,img1.getSize().y*ratio*0.5,img1.getSize().y));
    
    toUpdate = true;
    
    factor = 255;
    
    spt2.setScale(height/spt2.getGlobalBounds().height, height/spt2.getGlobalBounds().height);
    spt2.setPosition(width/2.0, 0);
    spt1.setScale(height/spt1.getGlobalBounds().height, height/spt1.getGlobalBounds().height);
    spt1.setPosition(0, 0);
    
    grey = false;
    // slider = trackSlider(1, 255, width/2, height/18, 255, 6, 6);
}

sf::Color dithering::checkCol(sf::Color col)
{
    int r;
    int g;
    int b;
    
    r = (col.r>255) ? 255:col.r;
    g = (col.g>255) ? 255:col.g;
    b = (col.b>255) ? 255:col.b;
    
    r = (col.r<0) ? 0:col.r;
    g = (col.g<0) ? 0:col.g;
    b = (col.b<0) ? 0:col.b;
    
    return sf::Color(r,g,b,col.a);
}

void dithering::update()
{
    float ranger = (std::round(slider.curVal)/255.0) * log2(255);
    
    
    factor = std::round(255/std::round(pow(2,ranger)));

    img2.copy(img1, 0, 0,sf::IntRect(0,0,img1.getSize().x,img1.getSize().y),false);
    
    grey = greyScale.checked;
    
    if(grey)
    {
        for (int y = 0; y<img2.getSize().y; y++)
        {
            for (int x = 0; x<img2.getSize().x; x++)
            {
                sf::Color old = img2.getPixel(x, y);
                float avg = (old.r+old.g+old.b)/3;
                img2.setPixel(x, y, checkCol(sf::Color(avg,avg,avg)));
            }
        }
    }
    
    for (int y = 0; y<img2.getSize().y-1; y++)
    {
        for (int x = 1; x<img2.getSize().x-1; x++)
        {
            sf::Color oldColor = img2.getPixel(x, y);
            
            float r = oldColor.r;
            float g = oldColor.g;
            float b = oldColor.b;
    
            float newR = std::round(r/factor)*factor;
            float newG = std::round(g/factor)*factor;
            float newB = std::round(b/factor)*factor;
            
            img2.setPixel(x, y, checkCol(sf::Color(newR,newG,newB)));
            
          
            float errR = (r - newR);
            float errG = (g - newG);
            float errB = (b - newB);
            
            sf::Color curPix = img2.getPixel(x+1, y);
            
            img2.setPixel(x+1, y  , checkCol(sf::Color(curPix.r + (errR*7/16.0),curPix.g + (errG*7/16.0), curPix.b + (errB*7/16.0))));
            curPix = img2.getPixel(x-1, y+1);
            img2.setPixel(x-1, y+1, checkCol(sf::Color(curPix.r + (errR*3/16.0),curPix.g + (errG*3/16.0),curPix.b + (errB*3/16.0))));
            curPix = img2.getPixel(x, y+1);
            img2.setPixel(x  , y+1, checkCol(sf::Color(curPix.r + (errR*5/16.0),curPix.g + (errG*5/16.0),curPix.b + (errB*5/16.0))));
            curPix = img2.getPixel(x+1, y+1);
            img2.setPixel(x+1, y+1, checkCol(sf::Color(curPix.r + (errR*1/16.0),curPix.g + (errG*1/16.0),curPix.b + (errB*1/16.0))));
            
           
        }
    }
    // tex2.update(img2.getPixelsPtr());
    tex2.loadFromImage(img2);
    spt2.setTexture(tex2);

    
    background.clear();
    background.draw(spt1);
    background.draw(spt2);
    background.display();
    
}

