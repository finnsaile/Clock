#include <SFML/Graphics.hpp>
#include <iostream>
#include "../headers/CClock.hpp"

int main()
{
    //get screen height
    unsigned int heigth = sf::VideoMode::getDesktopMode().height;
    //create non scalable window
    sf::RenderWindow window(sf::VideoMode(heigth / 2, heigth / 2), "Clock", sf::Style::Titlebar | sf::Style::Close);
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