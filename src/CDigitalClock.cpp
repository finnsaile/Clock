#include "../headers/CDigitalClock.hpp"

using namespace sf;
using namespace std;

//takes references to variables from clock
CDigitalClock::CDigitalClock(const Vector2u& clockSize, const Vector2f& clockPosition, const float& clockRadius, const Color& clockColor) :
m_clock_size(clockSize),
m_clock_position(clockPosition),
m_clock_radius(clockRadius),
m_clock_color(clockColor)
{
    //load font for digital clock
    m_digital_clock_font.loadFromFile("resources/fonts/digital7_mono.ttf");
    //set font of clock string
    m_digital_clock_text.setFont(m_digital_clock_font);
    //update digital clock to initialize all values
    update();
}

//updates all attributes of digital clock
void CDigitalClock::update()
{
    //set character size depending on width and height of clock
    m_digital_clock_text.setCharacterSize((m_clock_size.y < m_clock_size.x ? m_clock_size.y : m_clock_size.x)/10);
    //set fill color of digital clock
    m_digital_clock_text.setFillColor(m_clock_color);
    //set initial string so postition and origin of digital clock will be correct
    m_digital_clock_text.setString("00:00:00");
    //calculate and set origin
    m_digital_clock_text.setOrigin(m_digital_clock_text.getLocalBounds().width/2, m_digital_clock_text.getLocalBounds().height/2);
    //calculate and set position
    m_digital_clock_text.setPosition(m_clock_position.x, m_clock_position.y - m_clock_radius - m_clock_radius * 0.25);
}

//updates time of digital clock
void CDigitalClock::tick()
{
    //get time passed since 1970 or smth
    m_passed_time = time(0);
    //convert to tm localtime
    m_time_now = localtime(&m_passed_time);

    //set string for digital clock using timestruct
    string digitalString = to_string(m_time_now->tm_hour) + ":" + to_string(m_time_now->tm_min) + ":" + to_string(m_time_now->tm_sec);
    //add 0 if hour has only one digit 
    if (m_time_now->tm_hour < 10)
        digitalString = "0" + digitalString;
    //add 0 if minute value has only one digit
    if (m_time_now->tm_min < 10)
        digitalString.insert(3, "0");
    //add 0 if second value has only one digit
    if (m_time_now->tm_sec < 10)
        digitalString.insert(6, "0");
    //set string for digital clock
    m_digital_clock_text.setString(digitalString);
}

//draw digital clock
void CDigitalClock::draw(RenderTarget& target, RenderStates states) const
{
    target.draw(m_digital_clock_text);
}

