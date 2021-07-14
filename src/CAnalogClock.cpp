#include "../headers/CAnalogClock.hpp"

//constructor takes references and safes them in own member variables
CAnalogClock::CAnalogClock(const sf::Vector2f& clockPosition, const float& clockRadius, const sf::Color& clockColor, const float& clockThickness, const bool& smoothClockBool) :
m_smoothClockBool(smoothClockBool),
m_clockThickness(clockThickness),
m_clockPosition(clockPosition),
m_clockRadius(clockRadius),
m_clockColor(clockColor)
{
    //initialize all elements
    initClockCircle();
    initClockCenter();
    initHourLine();
    initMinuteLine();
    initSecondLine();
}

//initialises clock circle
void CAnalogClock::initClockCircle()
{
    //high circle point count for smooth appearance
    clockCircle.setPointCount(100);
    //set precalculated radius
    clockCircle.setRadius(m_clockRadius);
    //set precalculated origin
    clockCircle.setOrigin(m_clockRadius, m_clockRadius);
    //set precalculated position
    clockCircle.setPosition(m_clockPosition);
    //set fill color to black
    clockCircle.setFillColor(sf::Color::Transparent);
    //set precalculated outlinethickness
    clockCircle.setOutlineThickness(m_clockThickness);
    //set outline color
    clockCircle.setOutlineColor(m_clockColor);
}

//initialises clockcenter
void CAnalogClock::initClockCenter()
{
    //high circle point count for smooth appearance
    clockCenter.setPointCount(100);
    //set precalculated radius
    clockCenter.setRadius(m_clockThickness);
    //set precalculated origin
    clockCenter.setOrigin(m_clockThickness, m_clockThickness);
    //set precalculated position
    clockCenter.setPosition(m_clockPosition);
    //set fill color to green
    clockCenter.setFillColor(m_clockColor);
}

//initialises hour line
void CAnalogClock::initHourLine()
{
    //set length according to radius
    hourLine.setSize(sf::Vector2f(m_clockRadius - m_clockRadius/2, m_clockThickness));
    //set orign correctly
    hourLine.setOrigin(0, m_clockThickness/2);
    //set precalculated position
    hourLine.setPosition(m_clockPosition);
    //set fill color to green
    hourLine.setFillColor(m_clockColor);
    //set initial rotation
    hourLine.setRotation(-90);
}
//initialises minute line
void CAnalogClock::initMinuteLine()
{
    //set length according to radius
    minuteLine.setSize(sf::Vector2f(m_clockRadius - m_clockRadius/5,m_clockThickness));
    //set orign correctly
    minuteLine.setOrigin(0, m_clockThickness/ 2);
    //set precalculated position
    minuteLine.setPosition(m_clockPosition);
    //set fill color to green
    minuteLine.setFillColor(m_clockColor);
}

//initialises second line
void CAnalogClock::initSecondLine()
{
    //set length according to radius
    secondLine.setSize(sf::Vector2f(m_clockRadius - m_clockRadius/10, m_clockThickness));
    //set orign correctly
    secondLine.setOrigin(0, m_clockThickness/ 2);
    //set precalculated position
    secondLine.setPosition(m_clockPosition);
    //set fill color to green
    secondLine.setFillColor(m_clockColor);
    //set initial rotation
    secondLine.setRotation(90);
}

//adjust each element according to current time
void CAnalogClock::tick()
{
    //get time passed 1970 or smth
    m_passedTime = std::time(0);
    //convert to tm localtime
    m_timeNow = std::localtime(&m_passedTime);
 
    //set rotation for hour line (360 degree circle / 12 hours = 15; - 90 because rectangles are vertikal)
    hourLine.setRotation(((m_timeNow->tm_hour * 30) - 90) + static_cast<float>(m_smoothClockBool) * 30 * m_timeNow->tm_min/60);
    //rotation for minute line (360/60 = 6)
    minuteLine.setRotation(((m_timeNow->tm_min * 6) - 90) + static_cast<float>(m_smoothClockBool) * 6 * m_timeNow->tm_sec/60);
    //rotation for second line (360/60 = 6)
    secondLine.setRotation((m_timeNow->tm_sec * 6) - 90);
}

//draw all objects in correct order
void CAnalogClock::draw(sf::RenderTarget& target, sf::RenderStates states) const
{ 
    target.draw(clockCircle);
    target.draw(clockCenter);
    target.draw(hourLine);
    target.draw(minuteLine);
    target.draw(secondLine);    
}

//update all elements
void CAnalogClock::update()
{
    initClockCircle();
    initClockCenter();
    initHourLine();
    initMinuteLine();
    initSecondLine();
}