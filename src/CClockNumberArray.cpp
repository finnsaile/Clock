#include "../headers/CClockNumberArray.hpp"

CClockNumberArray::CClockNumberArray(float radius, float thickness, sf::Vector2f position, sf::Vector2f origin) :
//allocate memory for 12 objects
numberArray(new CClockNumber[12])
{
    //set static origin member variable to passed parameter from constructor
    numberArray->setOrigin(origin);
    //set static position member variable to passed parameter from constructor
    numberArray->setPosition(position);
    //set static radius member variable to passed parameter from constructor
    numberArray->setRadius(radius);
    //loop through all elements of array
    for (int i = 0; i < 12; i++)
    {
        numberArray[i].setNumber(i, thickness * 10);
        //set size of element (first size for visible line, second size for invisible line)
        numberArray[i].setSize(sf::Vector2f(radius, thickness), sf::Vector2f(radius - radius/15, thickness));
        //set rotation according to n
        numberArray[i].setRotation(i * 30);
        //update origin and position of both lines in object
        numberArray[i].update();
    }
}

//virtual draw function loops through all objects and draws them
void CClockNumberArray::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (int i = 0; i < 12; i++)
    {
        target.draw(numberArray[i]);
    }
}