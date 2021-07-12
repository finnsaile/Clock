#include <SFML/Graphics.hpp>
#include <iostream>
#include "../headers/CClock.hpp"

int main()
{
    //antialiasing 
    sf::Image icon;
    icon.loadFromFile("resources/icons/clock_icon.png");
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    //get screen height
    unsigned int heigth = sf::VideoMode::getDesktopMode().height;
    //create non scalable window
    sf::RenderWindow window(sf::VideoMode(heigth / 2, heigth / 2), "Clock", sf::Style::Titlebar | sf::Style::Close, settings);
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    //enable V-Sync
    window.setFramerateLimit(10);
    //disable repeat key press on hold
    window.setKeyRepeatEnabled(false);

    //Create clock
    CClock clockObject(window.getSize(), sf::Vector2f(window.getSize().x/2, window.getSize().y/2), sf::Color::Red);
    CClock clockObject1(window.getSize(), sf::Vector2f(0, 0));
    CClock clockObject2(window.getSize(), sf::Vector2f(window.getSize().x, window.getSize().y));
    CClock clockObject3(window.getSize(), sf::Vector2f(0, window.getSize().y));
    CClock clockObject4(window.getSize(), sf::Vector2f(window.getSize().x, 0));
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
                //close window if close button is pressed
                case sf::Event::Closed:
                    window.close();
                    break;
                //switch case for key press
                case sf::Event::KeyPressed:
                    switch(event.key.code)
                    {
                        //close window if ESC is pressed
                        case sf::Keyboard::Escape:  
                            window.close(); 
                            break;
                        //change smooth mode if R is pressed
                        case sf::Keyboard::R:
                        
                            if(clockObject.getSmoothClockBool() == false) 
                                clockObject.setSmoothClockBool(true);
                            else   
                                clockObject.setSmoothClockBool(false); 
                            break;
                        //change smooth mode if R is pressed
                        case sf::Keyboard::E:
                            
                            if(clockObject.getDigitalClockBool() == false) 
                                clockObject.setDigitalClockBool(true);
                            else   
                                clockObject.setDigitalClockBool(false); 
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
        clockObject1.clockTick();
        clockObject2.clockTick();
        clockObject3.clockTick();
        clockObject4.clockTick();
        //clear window
        window.clear(sf::Color::Transparent);
        //draw clock
        window.draw(clockObject);
        window.draw(clockObject1);
        window.draw(clockObject2);
        window.draw(clockObject3);
        window.draw(clockObject4);
        //display everything
        window.display();
    }   
}