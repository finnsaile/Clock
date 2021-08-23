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
        const sf::Vector2u& m_clock_size;
        const sf::Vector2f& m_clock_position;
        const float& m_clock_radius;
        const sf::Color& m_clock_color;

        //time variables to get current time
        std::time_t m_passed_time;
        tm* m_time_now;

        //font and string for digital clock
        sf::Font m_digital_clock_font;
        sf::Text m_digital_clock_text;

        //draw function to draw clock
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};