#pragma once
#include <SFML/Graphics.hpp>
#include "CClockNumber.hpp"

//class used to store 12 clock numbers in array and initialise them
class CClockNumberArray : public sf::Drawable
{
    public: 
        //Constructor takes values needed for elements of number array
        CClockNumberArray(const float& radius, const float& thickness, const sf::Vector2f& position, const sf::Color& color);
        virtual ~CClockNumberArray();
        void update();
    private:
        //references to variables from clock object
        const float& m_radius;
        const float& m_thickness;
        const sf::Vector2f& m_position;
        const sf::Color& m_color;

        //pointer to number array
        CClockNumber* m_number_array;
        //virtual draw function
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};