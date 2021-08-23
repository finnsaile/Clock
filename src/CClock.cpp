#include "../headers/CClock.hpp"

using namespace sf;

//constructor with all needed parameters
CClock::CClock(Vector2u size, Vector2f position, Color color, bool digitalClockB, bool smoothClockB) :
m_number_array(nullptr),
m_clock_offset_bool(false),
m_digital_clock_bool(digitalClockB),
m_smooth_clock_bool(smoothClockB),
m_clock_size(size),
m_clock_position(position),
m_clock_color(color)
{
    //if digital clock is activated and clock hasn't been moved already move clock position and set offsetBool to true
    if(!m_clock_offset_bool && m_digital_clock_bool)
    {
        m_clock_offset_bool = true;        
        m_clock_position.y += (calcSize()/20);
    }

    //calculatee clock radius and thickness
    m_clock_radius = calcSize() * 0.4;
    m_clock_thickness = calcSize() / 100;

    //create all 3 objects with the correct values
    m_number_array = new CClockNumberArray(m_clock_radius, m_clock_thickness, m_clock_position, m_clock_color);
    m_digital_clock = new CDigitalClock(m_clock_size, m_clock_position, m_clock_radius, m_clock_color);
    m_analog_clock = new CAnalogClock(m_clock_position, m_clock_radius, m_clock_color, m_clock_thickness, m_smooth_clock_bool);
}

//delete all 3 objects
CClock::~CClock()
{
    delete m_number_array;
    delete m_digital_clock;
    delete m_analog_clock;
}

//update all 3 objects
void CClock::update()
{
    //calculate new radius and thickness
    m_clock_radius = calcSize() * 0.4;
    m_clock_thickness = calcSize() / 100;

    //update all objects
    m_digital_clock->update();
    m_analog_clock->update();
    m_number_array->update();
}

//call tick function for both clocks
void CClock::clockTick()
{
    m_digital_clock->tick();
    m_analog_clock->tick();
}

//getter function for smooth bool which decides if minute and hour arm move smooth or not
bool CClock::getSmoothClockBool()
{
    return m_smooth_clock_bool;
}

//setter function for smooth bool
void CClock::setSmoothClockBool(bool in)
{
    m_smooth_clock_bool = in;
}

//getter function for digital bool which decides if minute and hour arm move smooth or not
bool CClock::getDigitalClockBool()
{
    return m_digital_clock_bool;
}

//setter function for digital bool
void CClock::setDigitalClockBool(bool in)
{
    m_digital_clock_bool = in;

    //if digital clock is being turned off, move clock up and set offset bool to false
    if(!m_digital_clock_bool) 
    {
        m_clock_offset_bool = false;
        m_clock_position.y -= (calcSize()/20);
    }
    //if digital bool is being turned on, and there is no offset move clock down
    else if(!m_clock_offset_bool && m_digital_clock_bool)
    {
        m_clock_offset_bool = true;        
        m_clock_position.y += (calcSize()/20);
    }

    //update all elements
    update();
}

//getter function for clock size
Vector2u CClock::getSize()
{
    return m_clock_size;
}

//setter function for clock size
void CClock::setSize(Vector2u size)
{
    m_clock_size = size;
    //update all elements
    update();
}

//getter function for clock color
Color CClock::getColor()
{
    return m_clock_color;
}

//setter function for clock color
void CClock::setColor(Color color)
{
    m_clock_color = color;
    //update all elements
    update();
}

//getter function for clock position
Vector2f CClock::getPosition()
{
    return m_clock_position;
}

//setter function for clock position
void CClock::setPosition(Vector2f position)
{
    //change clock position
    m_clock_position = position;
    //if digital clock is turned on, offset needs to be recalculated
    if(m_digital_clock_bool)
    {
        m_clock_offset_bool = true;        
        m_clock_position.y += (calcSize()/20);
    }
    //update all elements
    update();
}

//calc size returns either width or heigh of clock depending on which on is smaller
unsigned int CClock::calcSize()
{
    return (m_clock_size.y < m_clock_size.x ? m_clock_size.y : m_clock_size.x);
}

//draw all objects in correct order
void CClock::draw(RenderTarget& target, RenderStates states) const
{ 
    //only draw digital clock when digialClockBool is true
    if(m_digital_clock_bool)
        target.draw(*m_digital_clock);
    target.draw(*m_number_array);
    target.draw(*m_analog_clock);
}