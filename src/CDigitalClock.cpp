#include "../headers/CDigitalClock.hpp"

//takes references to variables from clock
CDigitalClock::CDigitalClock(const sf::Vector2u& clockSize, const sf::Vector2f& clockPosition, const float& clockRadius, const sf::Color& clockColor) :
m_clockSize(clockSize),
m_clockPosition(clockPosition),
m_clockRadius(clockRadius),
m_clockColor(clockColor)
{
    //load font for digital clock
    m_digitalClockFont.loadFromFile("resources/fonts/digital7_mono.ttf");
    //set font of clock string
    m_digitalClockText.setFont(m_digitalClockFont);
    //update digital clock to initialize all values
    update();
}

//updates all attributes of digital clock
void CDigitalClock::update()
{
    //set character size depending on width and height of clock
    m_digitalClockText.setCharacterSize((m_clockSize.y < m_clockSize.x ? m_clockSize.y : m_clockSize.x)/10);
    //set fill color of digital clock
    m_digitalClockText.setFillColor(m_clockColor);
    //set initial string so postition and origin of digital clock will be correct
    m_digitalClockText.setString("00:00:00");
    //calculate and set origin
    m_digitalClockText.setOrigin(m_digitalClockText.getLocalBounds().width/2, m_digitalClockText.getLocalBounds().height/2);
    //calculate and set position
    m_digitalClockText.setPosition(m_clockPosition.x, m_clockPosition.y - m_clockRadius - m_clockRadius * 0.25);
}

//updates time of digital clock
void CDigitalClock::tick()
{
    //get time passed since 1970 or smth
    m_passedTime = std::time(0);
    //convert to tm localtime
    m_timeNow = std::localtime(&m_passedTime);

    //set string for digital clock using timestruct
    std::string digitalString = std::to_string(m_timeNow->tm_hour) + ":" + std::to_string(m_timeNow->tm_min) + ":" + std::to_string(m_timeNow->tm_sec);
    //add 0 if hour has only one digit 
    if (m_timeNow->tm_hour < 10)
        digitalString = "0" + digitalString;
    //add 0 if minute value has only one digit
    if (m_timeNow->tm_min < 10)
        digitalString.insert(3, "0");
    //add 0 if second value has only one digit
    if (m_timeNow->tm_sec < 10)
        digitalString.insert(6, "0");
    //set string for digital clock
    m_digitalClockText.setString(digitalString);
}

//draw digital clock
void CDigitalClock::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_digitalClockText);
}

