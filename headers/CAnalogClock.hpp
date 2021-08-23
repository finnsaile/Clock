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
        const bool& m_smooth_clock_bool;
        const float& m_clock_thickness;
        const sf::Vector2f& m_clock_position;
        const float& m_clock_radius;
        const sf::Color& m_clock_color;

        //variable for calculating time
        std::time_t m_passed_time;
        std::tm* m_time_now;

        //center and circle for analog clock
        sf::CircleShape m_clock_circle;
        sf::CircleShape m_clock_center;

        //lines for analog clock
        sf::RectangleShape m_hour_line;
        sf::RectangleShape m_minute_line;
        sf::RectangleShape m_second_line;

        //functions to initialize all elements of analog clock
        void initClockCircle();
        void initClockCenter();
        void initHourLine();
        void initMinuteLine();
        void initSecondLine();

        //draw function to draw all elements
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};