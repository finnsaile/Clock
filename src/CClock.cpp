#include "../headers/CClock.hpp"

//constructor takes reference to window
CClock::CClock(sf::RenderWindow &window)
{
    //initialise clock
    initClock(window);
    //call clock tick once
    clockTick();
}

//method to initialise all clock elements
void CClock::initClock(sf::RenderWindow &window)
{ 
    //safe window size in member variable
    winSize = window.getSize();
    //calculatee clock radius and thickness
    clockRadius = winSize.y * 0.4;
    clockThickness = winSize.y / 100;
    //calculate position of clock center
    position.x = winSize.x/2;
    position.y = winSize.y/2 + winSize.x/20;
    
    //call all initialisation methods
    initDigitalClock();
    initClockCircle();
    initClockCenter();
    initHourLine();
    initMinuteLine();
    initSecondLine();
}

//initialises digital clock
void CClock::initDigitalClock()
{
    //load font
    digitalClockFont.loadFromFile("resources/fonts/digital7_mono.ttf");
    //set font of clock string
    digitalClock.setFont(digitalClockFont);
    //set char size
    digitalClock.setCharacterSize(winSize.y/10);
    //set color
    digitalClock.setFillColor(sf::Color::Green);
    //set dummy string to calculate first origin and position
    digitalClock.setString("00:00:00");
    //calculate and set origin
    digitalClock.setOrigin(digitalClock.getLocalBounds().width/2, digitalClock.getLocalBounds().height/2);
    //calculate and set position
    digitalClock.setPosition(position.x, winSize.y/20);
}

//initialises clock circle
void CClock::initClockCircle()
{
    //high circle point count for smooth appearance
    clockCircle.setPointCount(100);
    //set precalculated radius
    clockCircle.setRadius(clockRadius);
    //set precalculated origin
    clockCircle.setOrigin(clockRadius, clockRadius);
    //set precalculated position
    clockCircle.setPosition(position);
    //set fill color to black
    clockCircle.setFillColor(sf::Color::Black);
    //set precalculated outlinethickness
    clockCircle.setOutlineThickness(clockThickness);
    //set outline color
    clockCircle.setOutlineColor(sf::Color::Green);
}

//initialises clockcenter
void CClock::initClockCenter()
{
    //high circle point count for smooth appearance
    clockCenter.setPointCount(100);
    //set precalculated radius
    clockCenter.setRadius(clockThickness);
    //set precalculated origin
    clockCenter.setOrigin(clockThickness, clockThickness);
    //set precalculated position
    clockCenter.setPosition(position);
    //set fill color to green
    clockCenter.setFillColor(sf::Color::Green);
}

//initialises hour line
void CClock::initHourLine()
{
    //set length according to radius
    hourLine.setSize(sf::Vector2f(clockRadius - clockRadius/2, clockThickness));
    //set orign correctly
    hourLine.setOrigin(0, clockThickness/2);
    //set precalculated position
    hourLine.setPosition(position);
    //set fill color to green
    hourLine.setFillColor(sf::Color::Green);
    //set initial rotation
    hourLine.setRotation(-90);
}
//initialises minute line
void CClock::initMinuteLine()
{
    //set length according to radius
    minuteLine.setSize(sf::Vector2f(clockRadius - clockRadius/5, clockThickness));
    //set orign correctly
    minuteLine.setOrigin(0, clockThickness/ 2);
    //set precalculated position
    minuteLine.setPosition(position);
    //set fill color to green
    minuteLine.setFillColor(sf::Color::Green);
}
//initialises second line
void CClock::initSecondLine()
{
    //set length according to radius
    secondLine.setSize(sf::Vector2f(clockRadius - clockRadius/10, clockThickness));
    //set orign correctly
    secondLine.setOrigin(0, clockThickness/ 2);
    //set precalculated position
    secondLine.setPosition(position);
    //set fill color to green
    secondLine.setFillColor(sf::Color::Green);
    //set initial rotation
    secondLine.setRotation(90);
}

//adjust each element according to current time
void CClock::clockTick()
{
    //get time passed 1970 or smth
    passedTime = std::time(0);
    //convert to tm localtime
    timeNow = std::localtime(&passedTime);
    //compose digital string of all values
    std::string digitalString = std::to_string(timeNow->tm_hour) + ":" + std::to_string(timeNow->tm_min) + ":" + std::to_string(timeNow->tm_sec);
    //add 0 if hour has only one digit 
    if (timeNow->tm_hour < 10)
        digitalString = "0" + digitalString;
    //add 0 if minute value has only one digit
    if (timeNow->tm_min < 10)
        digitalString.insert(3, "0");
    //add 0 if second value has only one digit
    if (timeNow->tm_sec < 10)
        digitalString.insert(6, "0");
    //set string for digital clock
    digitalClock.setString(digitalString);
 
    //set rotation for hour line (360 degree circle / 12 hours = 15; - 90 because rectangles are vertikal)
    hourLine.setRotation((timeNow->tm_hour * 30) - 90);
    //rotation for minute line (360/60 = 6)
    minuteLine.setRotation((timeNow->tm_min * 6) - 90);
    //rotation for second line (360/60 = 6)
    secondLine.setRotation((timeNow->tm_sec * 6) - 90);
}

//draw all objects in correct order
void CClock::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(digitalClock);
    target.draw(clockCircle);
    target.draw(clockCenter);
    target.draw(hourLine);
    target.draw(minuteLine);
    target.draw(secondLine);
}