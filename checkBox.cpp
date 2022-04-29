//
//  checkBox.cpp
//  visuals
//
//  Created by Matthew  Eatough on 19/1/2022.
//  Copyright © 2022 The Good Goomba. All rights reserved.
//

#include "Headers/checkBox.hpp"

void checkBox::startUp(float x, float y, float size)
{
    outer = sf::RectangleShape(sf::Vector2f(size,size));
    outer.setOrigin(0,size/2);
    outer.setPosition(x, y);
    outer.setFillColor(sf::Color::Black);
    outer.setOutlineColor(sf::Color(200,200,200));
    outer.setOutlineThickness(2);
    
    pointX = {6,0,20,20,47,50};
    pointY = {14,20,27,40,0,10};
    
    for(int i=0; i<pointY.size();i++){
        pointX[i] = ((pointX[i] + 15)*size*0.01) + x;
        pointY[i] = ((pointY[i] -10)*size*0.01) + y;
    }

    M[0] = (pointY[0]-pointY[2])/(pointX[0]-pointX[2]);
    M[1] = (pointY[1]-pointY[3])/(pointX[1]-pointX[3]);
    M[2] = (pointY[2]-pointY[4])/(pointX[2]-pointX[4]);
    M[3] = (pointY[3]-pointY[5])/(pointX[3]-pointX[5]);
    
    animating = false;
    checked = false;
    animationPhase = 0;
    
}

bool checkBox::touchy(float mouseX, float mouseY)
{
    sf::FloatRect rectangel{
        outer.getPosition().x,
        outer.getPosition().y-outer.getGlobalBounds().height/2,
        outer.getGlobalBounds().width,
        outer.getGlobalBounds().height
    };
    
    if(rectangel.contains(mouseX, mouseY))
        return true;
    else
        return false;
}

void checkBox::animate(bool click)
{
    
    if (click){
        if (checked)
            checked = false;
        else
            checked = true;
        animating = true;
    } else
    {
        
        if (checked)
        {
            animationPhase += 0.1;
            if (animationPhase>=1){
                animationPhase = 1;
                animating = false;
            }
        } else
        {
            animationPhase -= 0.1;
            if (animationPhase<=0){
                animationPhase = 0;
                animating = false;
                check.clear();
                return;
            }
        }
        check.clear();

        
        if (animationPhase<0.5)
        {
            for (int i=0; i<2;i++){
                check.append(sf::Vertex());
                check[i].position = sf::Vector2f(pointX[i],pointY[i]);
            }
            
            check.append(sf::Vertex());
            check.append(sf::Vertex());
            check[2] = sf::Vector2f((pointX[0])+((pointX[2]-pointX[0])/4)*10*animationPhase,
                                    pointY[0]+((pointX[2]-pointX[0])/4)*10*animationPhase*M[0]);
            
            check[3] = sf::Vector2f((pointX[1])+((pointX[3]-pointX[1])/4)*10*animationPhase,
                                    pointY[1]+((pointX[3]-pointX[1])/4)*10*animationPhase*M[1]);
        } else
        {
            for (int i=0; i<4;i++){
                check.append(sf::Vertex());
                check[i].position = sf::Vector2f(pointX[i],pointY[i]);
                check[i].color = sf::Color::White;
            }
            check.append(sf::Vertex());
            check[4] = sf::Vector2f((pointX[2])+((pointX[4]-pointX[2])/6)*10*animationPhase,
                                    pointY[2]+((pointX[4]-pointX[2])/6)*10*animationPhase*M[2]);
            check.append(sf::Vertex());
            check[5] = sf::Vector2f((pointX[3])+((pointX[5]-pointX[3])/6)*10*animationPhase,
                                    pointY[3]+((pointX[5]-pointX[3])/6)*10*animationPhase*M[3]);

        }
        for (int i=0; i<check.getVertexCount();i++)
        {
            check[i].color = sf::Color::White;
        }
        
    
    }
     
}

// for (int i=0; i<2;i++){
//     check[0].position = sf::Vector2f(pointX[i],pointY[i]);
//     check[i].color = sf::Color::White;
// }
