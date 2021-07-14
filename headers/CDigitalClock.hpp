#pragma once
#include <SFML/Graphics.hpp>
#include <ctime>
#include <string>
#include <iostream>

//class to store all elements of digital clock
class CDigitalClock : public sf::Drawable
{
    public:
        //constructor takes references to variables from clock
        CDigitalClock(const sf::Vector2u& clockSize, const sf::Vector2f& clockPosition, const float& clockRadius, const sf::Color& clockColor);
        //tick function to update time
        void tick();
        //update function to update digital clock after change of variables
        void update();
        
    private:
        //references to store all variables from clock  
        const sf::Vector2u& m_clockSize;
        const sf::Vector2f& m_clockPosition;
        const float& m_clockRadius;
        const sf::Color& m_clockColor;

        //time variables to get current time
        std::time_t m_passedTime;
        tm* m_timeNow;

        //font and string for digital clock
        sf::Font m_digitalClockFont;
        sf::Text m_digitalClockText;

        //draw function to draw clock
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};