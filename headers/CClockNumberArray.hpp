#pragma once
#include <SFML/Graphics.hpp>
#include "CClockNumber.hpp"

//class used to store 12 clock numbers in array and initialise them
class CClockNumberArray : public sf::Drawable
{
    public: 
        //Constructor takes values needed for elements of number array
        CClockNumberArray(float radius, float thickness, sf::Vector2f position, sf::Vector2f origin);
        virtual ~CClockNumberArray();
    private:
        //pointer to number array
        CClockNumber* numberArray;
        //virtual draw function
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};