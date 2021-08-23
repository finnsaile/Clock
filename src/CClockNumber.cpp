#include "../headers/CClockNumber.hpp"

#define PI 3.14159265

using namespace sf;
using namespace std;

//initialise static position variable
Vector2f CClockNumber::m_position = Vector2f(0,0);
//initialise static origin variable
Vector2f CClockNumber::m_origin = Vector2f(0,0);
//initialise static radius variable
float CClockNumber::m_radius = 0;

//default constructor
CClockNumber::CClockNumber() :
m_number(0)
{
    //load font for numbers
    m_number_font.loadFromFile("resources/fonts/digital7.ttf");  
}

//set size of both line members
void CClockNumber::setSize(Vector2f sizeMain)
{
    //set correct size and color for both lines
    m_line.setSize(sizeMain);
    m_line.setFillColor(m_number_color);
}

//update origin and position of both lines 
void CClockNumber::update()
{
    //update origin of both lines
    m_line.setOrigin(m_origin);

    //update position of both lines
    m_line.setPosition(m_position);
    
    //move each line to the correct position on the circle using pythagoream theorem and the respective angle
    //for the first quarter of the clock
    //m_radius - m_radius/15: origin of line is towards center of clock - therefore each line must be moved towards center by its length
    //m_rotation: + 90 degrees because sfml angles start at 90 degrees (0 rotation = _, -90 rotation = |)
    // %90 because for the formula only the angle in the respective quarter is used
    // * PI / 180 to convert to degree
    if(m_rotation >= -90 && m_rotation < 0)
        //move in positive x position and y in negative position  
        m_line.move((m_radius - m_radius/15) * sin((((m_rotation + 90) % 90) * PI) / 180), -(m_radius - m_radius/15) * cos((((m_rotation + 90) % 90)  * PI) / 180));

    else if (m_rotation >= 0 && m_rotation < 90)
        //swap x and y (cos and sin) because the calculations are always respective to the current quarter
        //move x and y in positive direction
        m_line.move((m_radius - m_radius/15) * cos((((m_rotation + 90) % 90)  * PI) / 180), (m_radius - m_radius/15) * sin((((m_rotation + 90) % 90) * PI) / 180));

    else if (m_rotation >= 90 && m_rotation < 180)
        m_line.move(-(m_radius - m_radius/15) * sin((((m_rotation + 90) % 90) * PI) / 180), (m_radius - m_radius/15) * cos((((m_rotation + 90)% 90)  * PI) / 180));
        //same as first one but move x in negative and y in positive direction (because it's mirrored)
    else    
        //same as second one but move both x and y in negative direction (because it's mirrored)
        m_line.move(-(m_radius - m_radius/15) * cos((((m_rotation + 90)% 90)  * PI) / 180),-(m_radius - m_radius/15) * sin((((m_rotation + 90) % 90) * PI) / 180));

    //update position and origin of number
    m_number_text.setOrigin(m_number_text.getLocalBounds().width / 1.75, m_number_text.getLocalBounds().height);
    m_number_text.setPosition(m_position);
    
    //move number text according to number and radius of clock (formating)
    switch(m_number)
    {
        case 3:
            m_number_text.move(m_radius - m_radius / 6.4, 0);
            break;
        case 6:
            m_number_text.move(0, m_radius - m_radius / 5.2);
            break;
        case 9:
            m_number_text.move(- m_radius + m_radius / 6.4, 0);
            break;
        case 12:
            m_number_text.move(m_radius / 230, - m_radius + m_radius / 5.2);
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
    m_line.setRotation(m_rotation);
}

//getter function returns rotation
float CClockNumber::getRotation()
{
    return m_rotation;
}

//setter function sets static origin variable
void CClockNumber::setOrigin(Vector2f in)
{
    m_origin = in;
}

//getter function returns static origin
Vector2f CClockNumber::getOrigin()
{
    return m_origin;
}

//setter function sets static position variable
void CClockNumber::setPosition(Vector2f in)
{
    m_position = in;
}

//getter function returns static position variable
Vector2f CClockNumber::getPosition()
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
    m_number_text.setFont(m_number_font);
    m_number_text.setCharacterSize(fontSize);
    m_number_text.setString(to_string(m_number));
    m_number_text.setFillColor(m_number_color);
}

//set color membervariable for color of numbers and lines
void CClockNumber::setColor(Color color)
{
    this->m_number_color = color;
}

//virtual draw function draws both lines and number
void CClockNumber::draw(RenderTarget& target, RenderStates states) const
{
    target.draw(m_line);
    //only draw number if its 3/6/9/12
    if(m_number % 3 == 0)
        target.draw(m_number_text);
}