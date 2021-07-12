#pragma once
#include <SFML/Graphics.hpp>
#include <ctime>
#include <string>
#include <iostream>
#include "CClockNumberArray.hpp"

class CClock : public sf::Drawable
{
    public:
        //constructors with lots of parameters
        CClock(sf::Vector2u size, sf::Vector2f position, sf::Color color = sf::Color::Green, bool digitalClock = false, bool smoothClock = false);
        ~CClock();
        //changes elements each tick according to current time
        void clockTick();
        //getter and setter functions
        bool getSmoothClockBool();
        bool getDigitalClockBool();
        sf::Vector2u getSize();
        sf::Color getColor();
        sf::Vector2f getPosition();

        void setSmoothClockBool(bool in);
        void setDigitalClockBool(bool in);
        void setSize(sf::Vector2u size);
        void setColor(sf::Color);
        void setPosition(sf::Vector2f position);
    private:

        //Array Object for 12 numbers
        CClockNumberArray *numberArray;
        
        //variables for calculating correct position, size and origin of elements
        bool clockOffsetBool;
        bool digitalClockBool;
        bool smoothClockBool;
        float clockRadius;
        float clockThickness;
        sf::Vector2u clockSize;
        sf::Vector2f clockPosition;

        //clock Color
        sf::Color clockColor;

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
        void initClock();
        void initDigitalClock();
        void initClockCircle();
        void initClockCenter();
        void initHourLine();
        void initMinuteLine();
        void initSecondLine();
};