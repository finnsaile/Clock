#include "../headers/CClock.hpp"

/******************************************************************************************
 * ***************************       CONSTRUCTORS       ***********************************
 * ***************************************************************************************/


//constructor with position
CClock::CClock(sf::Vector2u size, sf::Vector2f position, sf::Color color, bool digitalClock, bool smoothClock) :
numberArray(nullptr),
clockOffsetBool(digitalClock),
digitalClockBool(digitalClock),
smoothClockBool(smoothClock),
clockSize(size),
clockPosition(position),
clockColor(color)
{
    //if digital clock is activated move clock down
    if(digitalClockBool)
        clockPosition.y += (clockSize.x/20);
    //initialize clock
    initClock();
}

/******************************************************************************************
 * ****************************************************************************************
 * ***************************************************************************************/

CClock::~CClock()
{
    delete numberArray;
}

void CClock::initClock()
{
    //calculatee clock radius and thickness
    clockRadius = clockSize.y * 0.4;
    clockThickness = clockSize.y / 100;
    

    //if digital clock is activated and clock hasn't benn moved already move clock and set offsetBool to true
    if(!clockOffsetBool && digitalClockBool)
    {
        clockOffsetBool = true;        
        clockPosition.y += (clockSize.x/20);
    }

    
    //number Array gets constructed
    if (numberArray != nullptr)
        delete numberArray;
    numberArray = new CClockNumberArray(clockRadius, clockThickness, sf::Vector2f(clockPosition.x, clockPosition.y), sf::Vector2f(0, (clockThickness)/ 2), clockColor);
    
    //call all initialisation methods
    initDigitalClock();
    initClockCircle();
    initClockCenter();
    initHourLine();
    initMinuteLine();
    initSecondLine();
    
    //call clock tick once
    clockTick();
}

//initialises digital clock
void CClock::initDigitalClock()
{
    //load font
    digitalClockFont.loadFromFile("resources/fonts/digital7_mono.ttf");
    //set font of clock string
    digitalClock.setFont(digitalClockFont);
    //set char size
    digitalClock.setCharacterSize(clockSize.y/10);
    //set color
    digitalClock.setFillColor(clockColor);
    //set dummy string to calculate first origin and position
    digitalClock.setString("00:00:00");
    //calculate and set origin
    digitalClock.setOrigin(digitalClock.getLocalBounds().width/2, digitalClock.getLocalBounds().height/2);
    //calculate and set position
    digitalClock.setPosition(clockPosition.x, clockSize.y/20);
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
    clockCircle.setPosition(clockPosition);
    //set fill color to black
    clockCircle.setFillColor(sf::Color::Transparent);
    //set precalculated outlinethickness
    clockCircle.setOutlineThickness(clockThickness);
    //set outline color
    clockCircle.setOutlineColor(clockColor);
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
    clockCenter.setPosition(clockPosition);
    //set fill color to green
    clockCenter.setFillColor(clockColor);
}

//initialises hour line
void CClock::initHourLine()
{
    //set length according to radius
    hourLine.setSize(sf::Vector2f(clockRadius - clockRadius/2, clockThickness));
    //set orign correctly
    hourLine.setOrigin(0, clockThickness/2);
    //set precalculated position
    hourLine.setPosition(clockPosition);
    //set fill color to green
    hourLine.setFillColor(clockColor);
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
    minuteLine.setPosition(clockPosition);
    //set fill color to green
    minuteLine.setFillColor(clockColor);
}
//initialises second line
void CClock::initSecondLine()
{
    //set length according to radius
    secondLine.setSize(sf::Vector2f(clockRadius - clockRadius/10, clockThickness));
    //set orign correctly
    secondLine.setOrigin(0, clockThickness/ 2);
    //set precalculated position
    secondLine.setPosition(clockPosition);
    //set fill color to green
    secondLine.setFillColor(clockColor);
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
    hourLine.setRotation(((timeNow->tm_hour * 30) - 90) + static_cast<float>(smoothClockBool) * 30 * timeNow->tm_min/60);
    //rotation for minute line (360/60 = 6)
    minuteLine.setRotation(((timeNow->tm_min * 6) - 90) + static_cast<float>(smoothClockBool) * 6 * timeNow->tm_sec/60);
    //rotation for second line (360/60 = 6)
    secondLine.setRotation((timeNow->tm_sec * 6) - 90);
}

//getter function for smooth bool which decides if minute and hour arm move smooth or not
bool CClock::getSmoothClockBool()
{
    return smoothClockBool;
}

//setter function for smooth bool
void CClock::setSmoothClockBool(bool in)
{
    smoothClockBool = in;
}

//getter function for digital bool which decides if minute and hour arm move smooth or not
bool CClock::getDigitalClockBool()
{
    return digitalClockBool;
}

//setter function for digital bool
void CClock::setDigitalClockBool(bool in)
{
    digitalClockBool = in;
    //if digital clock is being turned of, move clock up and set offset bool to false
    if(!digitalClockBool) 
    {
        clockOffsetBool = false;
        clockPosition.y -= (clockSize.x/20);
    }

    initClock();
}

//getter function for clock size
sf::Vector2u CClock::getSize()
{
    return clockSize;
}

//setter function for clock size
void CClock::setSize(sf::Vector2u size)
{
    clockSize = size;
    initClock();
}

//getter function for clock color
sf::Color CClock::getColor()
{
    return clockColor;
}

//setter function for clock color
void CClock::setColor(sf::Color color)
{
    clockColor = color;
    initClock();
}

//getter function for clock position
sf::Vector2f CClock::getPosition()
{
    return clockPosition;
}

//setter function for clock position
void CClock::setPosition(sf::Vector2f position)
{
    clockPosition = position;
    initClock();
}

//draw all objects in correct order
void CClock::draw(sf::RenderTarget& target, sf::RenderStates states) const
{ 
    //only draw digital clock when digialClockBool is true
    if(digitalClockBool)
        target.draw(digitalClock);
    target.draw(clockCircle);
    target.draw(*numberArray);
    target.draw(clockCenter);
    target.draw(hourLine);
    target.draw(minuteLine);
    target.draw(secondLine);    
}