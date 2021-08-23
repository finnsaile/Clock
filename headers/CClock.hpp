#pragma once
#include <SFML/Graphics.hpp>
#include <ctime>
#include <string>
#include <iostream>
#include "CClockNumberArray.hpp"
#include "CDigitalClock.hpp"
#include "CAnalogClock.hpp"

class CClock : public sf::Drawable
{
    public:
        //constructors with lots of parameters
        CClock(sf::Vector2u size, sf::Vector2f position, sf::Color color = sf::Color::Green, bool digitalClock = false, bool smoothClock = false);
        ~CClock();
        //changes elements each tick according to current time
        void clockTick();
        void update();
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
        CClockNumberArray *m_number_array;
        //both clock objects
        CDigitalClock* m_digital_clock;
        CAnalogClock* m_analog_clock;
        
        //variables for calculating correct position, size and origin of elements
        bool m_clock_offset_bool;
        bool m_digital_clock_bool;
        bool m_smooth_clock_bool;
        float m_clock_radius;
        float m_clock_thickness;
        sf::Vector2u m_clock_size;
        sf::Vector2f m_clock_position;
        sf::Color m_clock_color;

        //returns either width or heigh of of clock size depending on which is smaller
        unsigned int calcSize();

        //virtual draw function from sf::Drawable
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};