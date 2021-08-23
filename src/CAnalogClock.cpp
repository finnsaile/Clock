#include "../headers/CAnalogClock.hpp"

using namespace sf;
using namespace std;

//constructor takes references and safes them in own member variables
CAnalogClock::CAnalogClock(const Vector2f& clockPosition, const float& clockRadius, const Color& clockColor, const float& clockThickness, const bool& smoothClockBool) :
m_smooth_clock_bool(smoothClockBool),
m_clock_thickness(clockThickness),
m_clock_position(clockPosition),
m_clock_radius(clockRadius),
m_clock_color(clockColor)
{
    //initialize all elements
    update();
}

//initialises clock circle
void CAnalogClock::initClockCircle()
{
    //high circle point count for smooth appearance
    m_clock_circle.setPointCount(120);
    //set precalculated radius
    m_clock_circle.setRadius(m_clock_radius);
    //set precalculated origin
    m_clock_circle.setOrigin(m_clock_radius, m_clock_radius);
    //set precalculated position
    m_clock_circle.setPosition(m_clock_position);
    //set fill color to black
    m_clock_circle.setFillColor(Color::Transparent);
    //set precalculated outlinethickness
    m_clock_circle.setOutlineThickness(m_clock_thickness);
    //set outline color
    m_clock_circle.setOutlineColor(m_clock_color);
}

//initialises clockcenter
void CAnalogClock::initClockCenter()
{
    //high circle point count for smooth appearance
    m_clock_center.setPointCount(100);
    //set precalculated radius
    m_clock_center.setRadius(m_clock_thickness);
    //set precalculated origin
    m_clock_center.setOrigin(m_clock_thickness, m_clock_thickness);
    //set precalculated position
    m_clock_center.setPosition(m_clock_position);
    //set fill color to green
    m_clock_center.setFillColor(m_clock_color);
}

//initialises hour line
void CAnalogClock::initHourLine()
{
    //set length according to radius
    m_hour_line.setSize(Vector2f(m_clock_radius - m_clock_radius/2, m_clock_thickness));
    //set orign correctly
    m_hour_line.setOrigin(0, m_clock_thickness/2);
    //set precalculated position
    m_hour_line.setPosition(m_clock_position);
    //set fill color to green
    m_hour_line.setFillColor(m_clock_color);
    //set initial rotation
    m_hour_line.setRotation(-90);
}
//initialises minute line
void CAnalogClock::initMinuteLine()
{
    //set length according to radius
    m_minute_line.setSize(Vector2f(m_clock_radius - m_clock_radius/5,m_clock_thickness));
    //set orign correctly
    m_minute_line.setOrigin(0, m_clock_thickness/ 2);
    //set precalculated position
    m_minute_line.setPosition(m_clock_position);
    //set fill color to green
    m_minute_line.setFillColor(m_clock_color);
}

//initialises second line
void CAnalogClock::initSecondLine()
{
    //set length according to radius
    m_second_line.setSize(Vector2f(m_clock_radius - m_clock_radius/10, m_clock_thickness));
    //set orign correctly
    m_second_line.setOrigin(0, m_clock_thickness/ 2);
    //set precalculated position
    m_second_line.setPosition(m_clock_position);
    //set fill color to green
    m_second_line.setFillColor(m_clock_color);
    //set initial rotation
    m_second_line.setRotation(90);
}

//adjust each element according to current time
void CAnalogClock::tick()
{
    //get time passed 1970 or smth
    m_passed_time = time(0);
    //convert to tm localtime
    m_time_now = localtime(&m_passed_time);
 
    //set rotation for hour line (360 degree circle / 12 hours = 15; - 90 because rectangles are vertikal)
    m_hour_line.setRotation(((m_time_now->tm_hour * 30) - 90) + static_cast<float>(m_smooth_clock_bool) * 30 * m_time_now->tm_min/60);
    //rotation for minute line (360/60 = 6)
    m_minute_line.setRotation(((m_time_now->tm_min * 6) - 90) + static_cast<float>(m_smooth_clock_bool) * 6 * m_time_now->tm_sec/60);
    //rotation for second line (360/60 = 6)
    m_second_line.setRotation((m_time_now->tm_sec * 6) - 90);
}

//draw all objects in correct order
void CAnalogClock::draw(RenderTarget& target, RenderStates states) const
{ 
    target.draw(m_clock_circle);
    target.draw(m_clock_center);
    target.draw(m_hour_line);
    target.draw(m_minute_line);
    target.draw(m_second_line);    
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