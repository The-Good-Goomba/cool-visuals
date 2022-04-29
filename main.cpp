
//
// Disclaimer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resources, use the helper
// function `resourcePath()` from ResourcePath.hpp
//

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <vector>
#include <array>
#include <string>
// Here is a small helper for you! Have a look.
#include "ResourcePath.hpp"
#include "Headers/dropMenu.hpp"
#include "Headers/boxes.hpp"
#include "Headers/dithering.hpp"
#include "Headers/ripple.hpp"
#include "Headers/fourier.hpp"

float height = 1080;
float width = 1920;

// Setting up the navigation bar
sf::RectangleShape navBar = sf::RectangleShape(sf::Vector2f(width,height/9));
sf::Color navBGColor = sf::Color(29, 31, 31);
sf::Color navOutline = sf::Color(53,53,54);

// Window
sf::Color backgroundColor = sf::Color(41,40,48);

// Clock
sf::Clock glock;

// Box variables and sizes
int boxTextSize = 48;
int clockyBoi = 0;

sf::Color boxColor{57, 59, 58, 0};
sf::Color boxOutCol{53,53,54,0};
sf::Color boxTextCol{255,255,255,0};

dropMenu selector;
dithering dith;
ripple rip;
fourier fou(height*8/9,width,0,height/9);

int main(int, char const**)
{
    // Navigation bar setup
    navBar.setFillColor(navBGColor);
    navBar.setPosition(0, 0);
    navBar.setOutlineColor(navOutline);
    navBar.setOutlineThickness(2);
    
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(width, height), "SFML window");
    
    selector.app = {"Ripple","Dithering","Fourier"};
    selector.startUp(height/36,height/18,width,height);
    dith.startUp(width,height*8/9,0,height/9);
    rip.setup(200, 200, 0, height/9);
    glock.restart();
    // Start the game loop
    while (window.isOpen())
    {
        sf::Time elapsed = glock.getElapsedTime();
        sf::sleep(sf::milliseconds(20-elapsed.asMilliseconds()));
        elapsed = glock.restart();
        
        
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type){
                case sf::Event::Closed:
                    window.close();
                    break;
                    
                case sf::Event::KeyPressed:
                    switch (event.key.code) {
                        case sf::Keyboard::Escape:
                            window.close();
                            break;
                            
                        default:
                            break;
                    }
                    break;
                    
                case sf::Event::MouseButtonPressed:
                
                    if (selector.touchArrow(event.mouseButton.x, event.mouseButton.y))
                        selector.clickArrow(true);
                    
                    if(!selector.direction)
                    {
                    for (int i = 0;i<selector.apps.size();i++)
                    {
                        if(selector.touchBox(event.mouseButton.x, event.mouseButton.y, i))
                            selector.clickBox(i);
                    }
                    }
                    
                    if (selector.activeApp == 1)
                    {
                        if (dith.slider.touchCircle(event.mouseButton.x, event.mouseButton.y))
                            dith.slider.isPressed = true;
                        if (dith.greyScale.touchy(event.mouseButton.x, event.mouseButton.y)){
                            dith.greyScale.animate(true);
                            dith.toUpdate = true;
                        }
                    }
                    if (selector.activeApp == 2)
                    {
                        if (fou.slider.touchCircle(event.mouseButton.x, event.mouseButton.y))
                            fou.slider.isPressed = true;
                        
                        if (fou.menu.touchArrow(event.mouseButton.x, event.mouseButton.y))
                            fou.menu.clickArrow(true);
                        
                        if(!fou.menu.direction)
                        {
                            for (int i = 0;i<fou.menu.apps.size();i++)
                            {
                                if(fou.menu.touchBox(event.mouseButton.x, event.mouseButton.y, i)){
                                    fou.menu.clickBox(i);
                                    fou.set(i);
                                }
                            }
                        }
                        
                    }
                    
                    break;
                    
                    
                case sf::Event::MouseMoved:
                    if (!selector.direction)
                    {
                        for (int i = 0;i<selector.apps.size();i++)
                        {
                            
                            if(selector.touchBox(event.mouseMove.x, event.mouseMove.y, i))
                            {
                                selector.apps[i].textCol.a = 255;
                                selector.apps[i].text.setFillColor(selector.apps[i].textCol);
                                selector.drawThings();
                            } else{
                                selector.apps[i].textCol.a = 100;
                                selector.apps[i].text.setFillColor(selector.apps[i].textCol);
                                selector.drawThings();
                            }
                                
                        }
                    }
                    
                    if (selector.activeApp == 2 && !fou.menu.direction)
                    {
                        for (int i = 0;i<fou.menu.apps.size();i++)
                        {
                            
                            if(fou.menu.touchBox(event.mouseMove.x, event.mouseMove.y, i))
                            {
                                fou.menu.apps[i].textCol.a = 255;
                                fou.menu.apps[i].text.setFillColor(fou.menu.apps[i].textCol);
                                fou.menu.drawThings();
                            } else{
                                fou.menu.apps[i].textCol.a = 100;
                                fou.menu.apps[i].text.setFillColor(fou.menu.apps[i].textCol);
                                fou.menu.drawThings();
                            }
                                
                        }
                    }
                    
                    break;
                
                default:
                    break;
            }
        
        }
        
        // Put the code here please
    
        if (selector.animation)
            selector.clickArrow(false);
        
        
        switch (selector.activeApp){
            case 0:
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                    rip.drop(sf::Mouse::getPosition(window).x,
                             sf::Mouse::getPosition(window).y);
                    rip.updating = true;
                }
                
                if (rip.updating)
                    rip.update();
                
                break;
            case 1: {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                    if (dith.slider.isPressed == true)
                        dith.slider.move(sf::Mouse::getPosition(window).x,
                                         sf::Mouse::getPosition(window).y);
                } else{
                    if(dith.slider.isPressed)
                        dith.toUpdate = true;
                    dith.slider.isPressed = false;
                    
                }
                
                if (dith.greyScale.animating)
                    dith.greyScale.animate(false);
                
                
                if (dith.toUpdate)
                {
                    dith.update();
                    dith.toUpdate = false;
                }
                
                break;
            }
                
            case 2:
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                    if (fou.slider.isPressed == true)
                        fou.slider.move(sf::Mouse::getPosition(window).x,
                                         sf::Mouse::getPosition(window).y);
                } else{
                    fou.slider.isPressed = false;
                }
                
                if (fou.menu.animation)
                    fou.menu.clickArrow(false);
                
                fou.update();
                
                break;
                
            default:
                break;
        }
        
        
        // Clear screen
        window.clear(backgroundColor);
        
        // Draw stuff here
        
        // Main window stuff
        switch (selector.activeApp){
            case 0:
                
                for(auto& i:rip.pixels){
                    window.draw(i);
                }
                 
                
                break;
            case 1:{
                sf::Sprite img(dith.background.getTexture());
                img.setPosition(dith.offX, dith.offY);
                window.draw(img);
                break;
            }
                
            case 2: {
                sf::Sprite img(fou.background.getTexture());
                img.setPosition(fou.offX, fou.offY);
                window.draw(img);
                break;
            }
                
            default:
                break;
        }
        
        // Draw the navigation bar
        
        window.draw(navBar);
        window.draw(selector.things);
        
        // For things that go in the navigation bar
        switch (selector.activeApp){
            case 0:
                break;
            case 1:
                window.draw(dith.slider.rect);
                window.draw(dith.slider.ends[0]);
                window.draw(dith.slider.ends[1]);
                window.draw(dith.slider.bigCir);
                window.draw(dith.slider.message);
                window.draw(dith.greyScale.outer);
                window.draw(dith.gray);
                window.draw(dith.greyScale.check);
                break;
                
            case 2:
                window.draw(fou.slider.rect);
                window.draw(fou.slider.ends[0]);
                window.draw(fou.slider.ends[1]);
                window.draw(fou.slider.bigCir);
                window.draw(fou.slider.message);
                
                window.draw(fou.menu.things);
                break;
                
            default:
                break;
        }
      
        
        // Update the window
        window.display();
        
        clockyBoi++;
    }

    return EXIT_SUCCESS;
}
