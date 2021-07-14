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
    unsigned int width = sf::VideoMode::getDesktopMode().width;
    sf::FloatRect visibleArea(0, 0, width, heigth);
    //create non scalable window
    sf::RenderWindow window(sf::VideoMode(heigth / 2, heigth / 2), "Clock", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize, settings);
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    //enable V-Sync
    window.setFramerateLimit(10);
    //disable repeat key press on hold
    window.setKeyRepeatEnabled(false);

    //Create clock
    CClock clockObject(window.getSize(), sf::Vector2f(window.getSize().x/2, window.getSize().y/2), sf::Color::Green, true, false);

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
                case sf::Event::Resized:
                    visibleArea = sf::FloatRect(0, 0, event.size.width, event.size.height);
                    window.setView(sf::View(visibleArea));
                    clockObject.setSize(window.getSize()); 
                    clockObject.setPosition(sf::Vector2f(window.getSize().x/2, window.getSize().y/2));
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
                        
                        case sf::Keyboard::C:                            
                            if(clockObject.getColor() == sf::Color::Green) 
                                clockObject.setColor(sf::Color::Blue);
                            else if(clockObject.getColor() == sf::Color::Blue)   
                                clockObject.setColor(sf::Color::Red); 
                            else if(clockObject.getColor() == sf::Color::Red)   
                                clockObject.setColor(sf::Color::Magenta); 
                            else if(clockObject.getColor() == sf::Color::Magenta)   
                            
                                clockObject.setColor(sf::Color::Cyan); 
                            else if(clockObject.getColor() == sf::Color::Cyan)   
                                clockObject.setColor(sf::Color::Yellow); 
                            else if(clockObject.getColor() == sf::Color::Yellow)   
                                clockObject.setColor(sf::Color::Green); 

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
        window.clear(sf::Color::Transparent);
        //draw clock
        window.draw(clockObject);
        //display everything
        window.display();
    } 
    return 0;  
}

