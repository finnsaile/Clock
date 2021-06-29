#include <SFML/Graphics.hpp>
#include <iostream>
#include "../headers/CClock.hpp"

int main()
{
    //antialiasing 
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    //get screen height
    unsigned int heigth = sf::VideoMode::getDesktopMode().height;
    //create non scalable window
    sf::RenderWindow window(sf::VideoMode(heigth / 2, heigth / 2), "Clock", sf::Style::Titlebar | sf::Style::Close, settings);
    //enable V-Sync
    window.setFramerateLimit(10);

    //Create clock
    CClock clockObject(window);
    //Create event
    sf::Event event;
    //window loop
    while (window.isOpen())
    {
        //event loop
        while(window.pollEvent(event))
        {
            switch(event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    switch(event.key.code)
                    {
                        case sf::Keyboard::Escape:  
                            window.close(); 
                            break;
                        
                        case sf::Keyboard::R:
                        
                            if(clockObject.getSmoothClockBool() == false)
                                clockObject.setSmoothClockBool(true);
                            else   
                                clockObject.setSmoothClockBool(false); 
                            break;

                        default:
                            break;
                    }
                default:
                    break;
            }     
        }
        //call window tick from window object
        clockObject.clockTick();
        //clear window
        window.clear(sf::Color::Black);
        //draw clock
        window.draw(clockObject);
        //display everything
        window.display();
    }   
}