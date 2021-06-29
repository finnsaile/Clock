#pragma once

#include <SFML/Graphics.hpp>
#include <ctime>
#include <string>
#include <iostream>

class CClock : public sf::Drawable
{
    public:
        //constructor takes window used to get window size
        CClock(sf::RenderWindow &window);
        //changes elements each tick according to current time
        void clockTick();
        //used to initialise all elements
        void initClock(sf::RenderWindow&);
        bool getSmoothClockBool();
        void setSmoothClockBool(bool);
    private:

        //variables for calculating correct position, size and origin of elements
        bool smoothClockBool;
        float clockRadius;
        float clockThickness;
        sf::Vector2u winSize;
        sf::Vector2f position;

        //variable for calculating time
        std::time_t passedTime;
        std::tm* timeNow;

        //font and string for digital clock
        sf::Font digitalClockFont;
        sf::Text digitalClock;

        //center and circle for analog clock
        sf::CircleShape clockCircle;
        sf::CircleShape clockCenter;

        //lines for analog clock
        sf::RectangleShape hourLine;
        sf::RectangleShape minuteLine;
        sf::RectangleShape secondLine;

        //virtual draw function from sf::Drawable
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        
        //functions for initialisation of elemets
        void initDigitalClock();
        void initClockCircle();
        void initClockCenter();
        void initHourLine();
        void initMinuteLine();
        void initSecondLine();
};