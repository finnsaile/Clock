#include "../headers/CClockNumber.hpp"
#include <iostream>
//initialise static position variable
sf::Vector2f CClockNumber::m_position = sf::Vector2f(0,0);
//initialise static origin variable
sf::Vector2f CClockNumber::m_origin = sf::Vector2f(0,0);
//initialise static radius variable
float CClockNumber::m_radius = 0;

//default constructor
CClockNumber::CClockNumber() :
m_number(0)
{
    //load font for numbers
    m_numberFont.loadFromFile("resources/fonts/digital7.ttf");
}

//set size of both line members
void CClockNumber::setSize(sf::Vector2f sizeMain)
{
    //set correct size and color for both lines
    mainRect.setSize(sizeMain);
    mainRect.setFillColor(sf::Color::Green);
}

//update origin and position of both lines 
void CClockNumber::update()
{
    //update origin of both lines
    mainRect.setOrigin(m_origin);

    //update position of both lines
    mainRect.setPosition(m_position);
    
    //move each line to the correct position on the circle using pythagoream theorem and the respective angle
    //for the first quarter of the clock
    //m_radius - m_radius/15: origin of line is towards center of clock - therefore each line must be moved towards center by its length
    //m_rotation: + 90 degrees because sfml angles start at 90 degrees (0 rotation = _, -90 rotation = |)
    // %90 because for the formula only the angle in the respective quarter is used
    // * PI / 180 to convert to degree
    if(m_rotation >= -90 && m_rotation < 0)
        //move in positive x position and y in negative position  
        mainRect.move((m_radius - m_radius/15) * sin((((m_rotation + 90) % 90) * PI) / 180), -(m_radius - m_radius/15) * cos((((m_rotation + 90) % 90)  * PI) / 180));

    else if (m_rotation >= 0 && m_rotation < 90)
        //swap x and y (cos and sin) because the calculations are always respective to the current quarter
        //move x and y in positive direction
        mainRect.move((m_radius - m_radius/15) * cos((((m_rotation + 90) % 90)  * PI) / 180), (m_radius - m_radius/15) * sin((((m_rotation + 90) % 90) * PI) / 180));

    else if (m_rotation >= 90 && m_rotation < 180)
        mainRect.move(-(m_radius - m_radius/15) * sin((((m_rotation + 90) % 90) * PI) / 180), (m_radius - m_radius/15) * cos((((m_rotation + 90)% 90)  * PI) / 180));
        //same as first one but move x in negative and y in positive direction (because it's mirrored)
    else    
        //same as second one but move both x and y in negative direction (because it's mirrored)
        mainRect.move(-(m_radius - m_radius/15) * cos((((m_rotation + 90)% 90)  * PI) / 180),-(m_radius - m_radius/15) * sin((((m_rotation + 90) % 90) * PI) / 180));

    //update position and origin of number
    m_numberText.setOrigin(m_numberText.getLocalBounds().width / 1.75, m_numberText.getLocalBounds().height);
    m_numberText.setPosition(m_position);
    
    //move number text according to number (formating)
    switch(m_number)
    {
        case 3:
            m_numberText.move(m_radius - 45, 0);
            break;
        case 6:
            m_numberText.move(-1.5, m_radius - 55);
            break;
        case 9:
            m_numberText.move(- m_radius + 45, 0);
            break;
        case 12:
            m_numberText.move(0, - m_radius + 55);
            break;
        default:
            break;         
    }
}

//set rotation of both lines
void CClockNumber::setRotation(int in)
{
    //set rotation member variable
    m_rotation = in - 90;
    //set rotation of both lines
    mainRect.setRotation(m_rotation);
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

//setter function sets static radius variable
void CClockNumber::setRadius(float in)
{
    m_radius = in;
}

//getter function returns static radius variable
float CClockNumber::getRadius()
{
    return m_radius;
}

//set number and font size of number string. Also initialise other number string values
void CClockNumber::setNumber(unsigned int in, float fontSize)
{
    //turn 0 into 12
    if(in != 0)
        m_number = in;
    else    
        m_number = 12;
    
    //set number string variables
    m_numberText.setFont(m_numberFont);
    m_numberText.setCharacterSize(fontSize);
    m_numberText.setString(std::to_string(m_number));
    m_numberText.setFillColor(sf::Color::Green);
}

//virtual draw function draws both lines and number
void CClockNumber::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mainRect);
    //only draw number if its 3/6/9/12
    if(m_number % 3 == 0)
        target.draw(m_numberText);
}