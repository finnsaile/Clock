#include "../headers/CClockNumberArray.hpp"

//constructor with references to values from clock
CClockNumberArray::CClockNumberArray(const float& radius, const float& thickness, const sf::Vector2f& position, const sf::Color& color) :
m_radius(radius),
m_thickness(thickness),
m_position(position),
m_color(color),
//allocate memory for 12 objects
numberArray(new CClockNumber[12])
{
    this->update();
}

//deletes all entries in numberArray
CClockNumberArray::~CClockNumberArray()
{
    delete[] numberArray;
}

//updates all entries of numberArray
void CClockNumberArray::update()
{
    //set static origin member variable to passed reference parameter from constructor
    numberArray->setOrigin(sf::Vector2f(0, (m_thickness)/ 2));
    //set static position member variable to passed reference parameter from constructor
    numberArray->setPosition(m_position);
    //set static radius member variable to passed reference parameter from constructor
    numberArray->setRadius(m_radius);
    //loop through all elements of array
    for (int i = 0; i < 12; i++)
    {
        //set color
        numberArray[i].setColor(m_color);
        //set number and font size
        numberArray[i].setNumber(i, m_thickness * 10);
        //set size of element (first size for visible line, second size for invisible line)
        numberArray[i].setSize(sf::Vector2f(m_radius/15, m_thickness));
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