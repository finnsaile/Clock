#include "../headers/CClockNumber.hpp"

//initialise static position variable
sf::Vector2f CClockNumber::m_position = sf::Vector2f(0,0);
//initialise origin position variable
sf::Vector2f CClockNumber::m_origin = sf::Vector2f(0,0);

//default constructor
CClockNumber::CClockNumber()
{}

//set size of both line members
void CClockNumber::setSize(sf::Vector2f sizeMain, sf::Vector2f sizeCover)
{
    //set correct size and color for both lines
    mainRect.setSize(sizeMain);
    coverRect.setSize(sizeCover);
    mainRect.setFillColor(sf::Color::Green);
    coverRect.setFillColor(sf::Color::Black);
}

//update origin and position of both lines 
void CClockNumber::update()
{
    //update origin of both lines
    mainRect.setOrigin(m_origin);
    coverRect.setOrigin(m_origin);

    //update position of both lines
    mainRect.setPosition(m_position);
    coverRect.setPosition(m_position);
}

//set rotation of both lines
void CClockNumber::setRotation(float in)
{
    //set rotation member variable
    m_rotation = in - 90;
    //set rotation of both lines
    mainRect.setRotation(m_rotation);
    coverRect.setRotation(m_rotation);
}

//getter function returns rotation
float CClockNumber::getRotation()
{
    return m_rotation;
}

//setter function sets static origin variable
void CClockNumber::setOrigin(sf::Vector2f in)
{
    m_origin = in;
}

//getter function returns static origin
sf::Vector2f CClockNumber::getOrigin()
{
    return m_origin;
}

//setter function sets static position variable
void CClockNumber::setPosition(sf::Vector2f in)
{
    m_position = in;
}

//getter function returns static position variable
sf::Vector2f CClockNumber::getPosition()
{
    return m_position;
}

//virtual draw function draws both lines
void CClockNumber::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mainRect);
    target.draw(coverRect);
}