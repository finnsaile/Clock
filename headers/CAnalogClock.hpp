#pragma once
#include <SFML/Graphics.hpp>
#include <ctime>
#include <string>
#include <iostream>

//class to store all elements of the analog clock
class CAnalogClock : public sf::Drawable
{
    public:
        //constructor takes references to variables from clock object
        CAnalogClock(const sf::Vector2f& clockPosition, const float& clockRadius, const sf::Color& clockColor, const float& clockThickness, const bool& smoothClockBool);
        //tick function to update time
        void tick();
        //update fuction to update elements after values get changed
        void update();
    private: 
        //references to clock variables
        const bool& m_smoothClockBool;
        const float& m_clockThickness;
        const sf::Vector2f& m_clockPosition;
        const float& m_clockRadius;
        const sf::Color& m_clockColor;

        //variable for calculating time
        std::time_t m_passedTime;
        std::tm* m_timeNow;

        //center and circle for analog clock
        sf::CircleShape clockCircle;
        sf::CircleShape clockCenter;

        //lines for analog clock
        sf::RectangleShape hourLine;
        sf::RectangleShape minuteLine;
        sf::RectangleShape secondLine;

        //functions to initialize all elements of analog clock
        void initClockCircle();
        void initClockCenter();
        void initHourLine();
        void initMinuteLine();
        void initSecondLine();

        //draw function to draw all elements
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};