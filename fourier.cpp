//
//  fourier.cpp
//  visuals
//
//  Created by Matthew  Eatough on 25/1/2022.
//  Copyright © 2022 The Good Goomba. All rights reserved.
//

#include "Headers/fourier.hpp"
#include <iostream>



fourier::fourier(int h, int w,float offSetX,float offSetY)
{
    if(!background.create(w, h))
        return EXIT_FAILURE;
    
    offY = offSetY;
    offX = offSetX;
    
    regular = true;

    y.clear();
    x.clear();
    for (int i = 0; i < 100; i++){
        y.push_back(100*sin(i*2*M_PI/100.0));
        x.push_back(100*cos(i*2*M_PI/100.0));
    }
    
    fourierY = dft(y);
    fourierX = dft(x);
    
    menu.app = {"Series","Square","Experiment","7"};
    
    menu.startUp(w*0.55, (h + offY)/18, h, w);
    
    
}

std::vector<fourier::waves> fourier::slowSort(std::vector<waves> four)
{
    for(int i= 0;i<four.size();i++)
    {
        float record = -1;
        int recIn = four.size()-1;
        for (int j = i;j<four.size();j++)
        {
            if (four[j].amp>record){
                record = four[j].amp;
                recIn = j;
            }
        }
        if (recIn == i)
            continue;
        waves temp = four[i];
        four[i] = four[recIn];
        four[recIn] = temp;
        
    }
    
    return four;
    
}

void fourier::set(int num)
{
    switch (num) {
        case 0:
            break;
            
        case 1:{
            y.clear();
            x.clear();
            wave.clear();
            path.clear();
            fourierX.clear();
            fourierY.clear();
            for (int i = 0; i < 100; i++){
                if (i<50)
                    y.push_back(100);
                else
                    y.push_back(-100);
            }
            
            fourierY = dft(y);
            fourierX = dft(x);
            
            fourierY = slowSort(fourierY);
            
            time = 0;
            break;
        }
            
        case 2: {
            y.clear();
            x.clear();
            wave.clear();
            path.clear();
            fourierX.clear();
            fourierY.clear();
            for (int i = 0; i < 100; i++){
                float angle = ((i/100.0)*2*M_PI);
                y.push_back(100*sin(angle));
                x.push_back(100*cos(angle));
            }
            
            fourierY = dft(y);
            fourierX = dft(x);
            time = 0;
            
            fourierY = slowSort(fourierY);
            
            break;
        }
        
        case 3: {
            y.clear();
            x.clear();
            wave.clear();
            path.clear();
            fourierX.clear();
            fourierY.clear();
            
            std::vector<std::array<int,3>> pos = {{36,0},{26,17},{12,17},{2,0},{36,0},{38,1},{48,17},{30,49},
                {10,49},{38,1}};
            
//            std::vector<std::array<int,3>> pos = {};
            
            std::cout << x.size() << " " << y.size() << "\n";
            
            float midpoint[] = {0,0};
            
            for (int i = 0;i<pos.size();i++)
            {
                midpoint[0] += pos[i][0];
                midpoint[1] += pos[i][1];
            }
            
            midpoint[0] = midpoint[0] / pos.size();
            midpoint[1] = midpoint[1] / pos.size();
            
            const float tempScale = 6;
            for(int i = 0; i < pos.size()-1;i++)
            {
                float a = (pos[i][0] - midpoint[0])*tempScale;
                float b = (pos[i+1][0] - midpoint[0])*tempScale;
                
                float p = (pos[i][1] - midpoint[1])*tempScale;
                float q = (pos[i+1][1] - midpoint[1])*tempScale;
                
                int dist = sqrt(pow(pos[i][0]-pos[i+1][0],2)+pow(pos[i][1]-pos[i+1][1],2))*tempScale/2;
                
                for (int j = 0; j < dist; j++){
                    float xMan = a + (b-a)*j/dist;
                    float yMan = p + (q-p)*j/dist;
                    x.push_back(xMan);
                    y.push_back(yMan);
                    
                }
            }
            
            
            fourierY = dft(y);
            fourierX = dft(x);
            
            
            time = 0;
            
            fourierY = slowSort(fourierY);
            fourierX = slowSort(fourierX);
            
            break;
        }
    
        default:
            break;
    }
}


std::vector<fourier::waves> fourier::dft(std::vector<float> a)
{
    std::vector<fourier::waves> X(a.size());
    const float N = a.size();
    for (int k=0;k<N;k++)
    {
        float re = 0;
        float im = 0;
        for (int n=0;n<N;n++)
        {
            float phi = (M_PI*2*k*n)/N;
            re += a[n] * cos(phi);
            im -= a[n] * sin(phi);
        }
        re = re/N;
        im = im/N;
        
        float freq = k;
        float amp = sqrt(re*re+im*im);
        float phase = atan2(im, re);
        
        X[k] = fourier::waves {
            re,     // Real component
            im,     // imaginary component
            amp,    // Amplitude or radius
            freq,   // Spinny speed
            phase   // Start pos
        };
        
        
    }
    
    return X;
}

sf::Vector2f fourier::epicycle(float a,float b,float rotation,std::vector<fourier::waves> four)
{
    float prevx;
    float prevy;
    for (float i=0; i<four.size();i++){
        prevx = a;
        prevy = b;
        
        float freq = four[i].freq;
        float radius = four[i].amp;
        float phase = four[i].phase;
        a += radius * cos(freq * time + phase + rotation);
        b += radius * sin(freq * time + phase + rotation);
        
    
        sf::CircleShape circle{radius,50};
        circle.setOutlineColor(sf::Color(255,255,255,100));
        circle.setOutlineThickness(2);
        circle.setFillColor(sf::Color::Transparent);
        circle.setOrigin(radius, radius);
        circle.setPosition(prevx, prevy);
        background.draw(circle);
    
        sf::VertexArray radi(sf::LineStrip,2);
        radi[0].position = sf::Vector2f(prevx, prevy);
        radi[1].position = sf::Vector2f(a, b);
        radi[0].color = sf::Color::White;
        radi[1].color = sf::Color::White;
        background.draw(radi);
         
    }
    
    return sf::Vector2f(a,b);
    
}

void fourier::update()
{
    background.clear();
    
    switch (menu.activeApp) {
        case 0:{
            const float xPos = background.getSize().x/6;
            const float yPos = background.getSize().y/2;
            
            
            float x = background.getSize().x/6;
            float y = background.getSize().y/2;
            
            int iterations = round(pow(slider.curVal,2));
            
            for (float i=0; i<iterations;i++){
                float prevx = x;
                float prevy = y;
                float n = i*2 +1;
                float radius = 100 * (4/(n * M_PI));
                x += radius * cos(n*time);
                y += radius * sin(n*time);
                
            
                sf::CircleShape circle{radius,50};
                circle.setOutlineColor(sf::Color(255,255,255,100));
                circle.setOutlineThickness(2);
                circle.setFillColor(sf::Color::Transparent);
                circle.setOrigin(radius, radius);
                circle.setPosition(prevx, prevy);
                background.draw(circle);
                
                //sf::CircleShape point{5,6};
                //point.setOrigin(5, 5);
                //point.setPosition(x + xPos, y + yPos);
                //point.setFillColor(sf::Color::White);
                //background.draw(point);
                 
                sf::VertexArray radi(sf::LineStrip,2);
                radi[0].position = sf::Vector2f(prevx, prevy);
                radi[1].position = sf::Vector2f(x, y);
                radi[0].color = sf::Color::White;
                radi[1].color = sf::Color::White;
                background.draw(radi);
            }
            
            wave.push_front(y);
            
            sf::VertexArray connect(sf::LineStrip,2);
            connect[0].position = sf::Vector2f(x, y);
            connect[1].position = sf::Vector2f(xPos + 200,wave[0]);
            connect[0].color = sf::Color::White;
            connect[1].color = sf::Color::White;
            background.draw(connect);
                
            sf::VertexArray line(sf::LineStrip,wave.size());
            for (int i=0;i<wave.size();i++)
            {
                line[i].position = sf::Vector2f(i + xPos  + 200,wave[i]);
                line[i].color = sf::Color::White;
            }
            background.draw(line);
            
            
            
            background.display();
            time += 0.05;
            
            if (wave.size()>300)
                wave.pop_back();
            break;
        }
            
        case 1:{
            const float xPos = background.getSize().x/6;
            const float yPos = background.getSize().y/2;
            
            
            float x = background.getSize().x/6;
            float y = background.getSize().y/2;
            
            
            y = epicycle(background.getSize().x/6, background.getSize().y/2, M_PI*0.5,fourierY).y;
            
            wave.push_front(y);
             
            sf::VertexArray connect(sf::LineStrip,2);
            connect[0].position = sf::Vector2f(x, y);
            connect[1].position = sf::Vector2f(xPos + 200,wave[0]);
            connect[0].color = sf::Color::White;
            connect[1].color = sf::Color::White;
            background.draw(connect);
                
            sf::VertexArray line(sf::LineStrip,wave.size());
            for (int i=0;i<wave.size();i++)
            {
                line[i].position = sf::Vector2f(i + xPos  + 200,wave[i]);
                line[i].color = sf::Color::White;
            }
            background.draw(line);
            
            
            
            
            background.display();
            
            const float dt = (M_PI*2.0)/fourierY.size() ;
            time += dt;
            
            if(time > (M_PI*2.0))
                time = 0;
            
            if (wave.size()>300)
                wave.pop_back();
            break;
        }
            
        case 2: {
            const float xPos = background.getSize().x*5/6;
            const float yPos = background.getSize().y/2;
            
            sf::Vector2f vx = epicycle(background.getSize().x*5/6, background.getSize().y/4, 0,fourierX);
            sf::Vector2f vy = epicycle(background.getSize().x/6, background.getSize().y/2, M_PI_2,fourierY);
            sf::Vector2f v = sf::Vector2f(vx.x,vy.y);
            
            path.push_front(v);
             
            
            sf::VertexArray connect(sf::LineStrip,2);
            connect[0].position = sf::Vector2f(vx.x, vx.y);
            connect[1].position = sf::Vector2f(path[0].x,path[0].y);
            connect[0].color = sf::Color::White;
            connect[1].color = sf::Color::White;
            background.draw(connect);
            
            connect[0].position = sf::Vector2f(vy.x, vy.y);
            background.draw(connect);
            
            sf::VertexArray line(sf::LineStrip,path.size());
            for (int i=0;i<path.size();i++)
            {
                line[i].position = path[i];
                line[i].color = sf::Color::White;
            }
            background.draw(line);
            
            
            
            background.display();
            
            const float dt = (M_PI*2.0)/fourierY.size();
            time += dt;
            
            if(time > (M_PI*2.0)){
                time = 0;
                path.clear();
            }
            break;
        }
            
        case 3: {
            const float xPos = background.getSize().x*5/6;
            const float yPos = background.getSize().y/2;
            
            sf::Vector2f vx = epicycle(background.getSize().x*2/3, background.getSize().y/4, 0,fourierX);
            sf::Vector2f vy = epicycle(background.getSize().x/6, background.getSize().y/2, M_PI_2,fourierY);
            sf::Vector2f v = sf::Vector2f(vx.x,vy.y);
            
            path.push_front(v);
             
            
            sf::VertexArray connect(sf::LineStrip,2);
            connect[0].position = sf::Vector2f(vx.x, vx.y);
            connect[1].position = sf::Vector2f(path[0].x,path[0].y);
            connect[0].color = sf::Color::Red;
            connect[1].color = sf::Color::Red;
            background.draw(connect);
            
            connect[0].position = sf::Vector2f(vy.x, vy.y);
            background.draw(connect);
            
            sf::VertexArray line(sf::LineStrip,path.size());
            for (int i=0;i<path.size();i++)
            {
                line[i].position = path[i];
                line[i].color = sf::Color::Red;
            }
            background.draw(line);
            
            
            
            background.display();
            
            const float dt = (M_PI*2.0)/fourierY.size();
            time += dt;
            
            if(time > (M_PI*2.0)){
                time = 0;
                path.clear();
            }
            
            
            std::string fileName = "/Users/mattheweatough/Desktop/sfml/"+ std::to_string(time) +".jpg";
            const sf::Texture &texture = background.getTexture();
            texture.copyToImage().saveToFile(fileName);
            
            break;
        }
    
        default:
            break;
    }
    
}

/*
 void fourier::update()
 {
     background.clear();
     
     float xPos = background.getSize().x/6;
     float yPos = background.getSize().y/2;
     
     
     float x = 0;
     float y = 0;
     
     int iterations = round(pow(slider.curVal,2));
     
     for (float i=0; i<iterations;i++){
         float prevx = x;
         float prevy = y;
         float n = i*2 +1;
         float radius = 100 * (4/(n * M_PI));
         x += radius * cos(n*time);
         y += radius * sin(n*time);
         
     
         sf::CircleShape circle{radius,50};
         circle.setOutlineColor(sf::Color(255,255,255,100));
         circle.setOutlineThickness(2);
         circle.setFillColor(sf::Color::Transparent);
         circle.setOrigin(radius, radius);
         circle.setPosition(prevx + xPos, prevy+yPos);
         background.draw(circle);
         
         //sf::CircleShape point{5,6};
         //point.setOrigin(5, 5);
         //point.setPosition(x + xPos, y + yPos);
         //point.setFillColor(sf::Color::White);
         //background.draw(point);
          
         sf::VertexArray radi(sf::LineStrip,2);
         radi[0].position = sf::Vector2f(prevx + xPos, prevy + yPos);
         radi[1].position = sf::Vector2f(x + xPos, y + yPos);
         radi[0].color = sf::Color::White;
         radi[1].color = sf::Color::White;
         background.draw(radi);
     }
     
     wave.push_front(y);
     
     sf::VertexArray connect(sf::LineStrip,2);
     connect[0].position = sf::Vector2f(x + xPos, y + yPos);
     connect[1].position = sf::Vector2f(xPos + 200,wave[0]+yPos);
     connect[0].color = sf::Color::White;
     connect[1].color = sf::Color::White;
     background.draw(connect);
         
     sf::VertexArray line(sf::LineStrip,wave.size());
     for (int i=0;i<wave.size();i++)
     {
         line[i].position = sf::Vector2f(i + xPos  + 200,wave[i] + yPos);
         line[i].color = sf::Color::White;
     }
     background.draw(line);
     
     
     
     background.display();
     time += 0.05;
     
     if (wave.size()>300)
         wave.pop_back();
 }
 */
