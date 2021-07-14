#include "../headers/CClock.hpp"

//constructor with all needed parameters
CClock::CClock(sf::Vector2u size, sf::Vector2f position, sf::Color color, bool digitalClockB, bool smoothClockB) :
numberArray(nullptr),
clockOffsetBool(false),
digitalClockBool(digitalClockB),
smoothClockBool(smoothClockB),
clockSize(size),
clockPosition(position),
clockColor(color)
{
    //if digital clock is activated and clock hasn't been moved already move clock position and set offsetBool to true
    if(!clockOffsetBool && digitalClockBool)
    {
        clockOffsetBool = true;        
        clockPosition.y += (calcSize()/20);
    }

    //calculatee clock radius and thickness
    clockRadius = calcSize() * 0.4;
    clockThickness = calcSize() / 100;

    //create all 3 objects with the correct values
    numberArray = new CClockNumberArray(clockRadius, clockThickness, clockPosition, clockColor);
    digitalClock = new CDigitalClock(clockSize, clockPosition, clockRadius, clockColor);
    analogClock = new CAnalogClock(clockPosition, clockRadius, clockColor, clockThickness, smoothClockBool);
}

//delete all 3 objects
CClock::~CClock()
{
    delete numberArray;
    delete digitalClock;
    delete analogClock;
}

//update all 3 objects
void CClock::update()
{
    //calculate new radius and thickness
    clockRadius = calcSize() * 0.4;
    clockThickness = calcSize() / 100;

    //update all objects
    digitalClock->update();
    analogClock->update();
    numberArray->update();
}

//call tick function for both clocks
void CClock::clockTick()
{
    digitalClock->tick();
    analogClock->tick();
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

    //if digital clock is being turned off, move clock up and set offset bool to false
    if(!digitalClockBool) 
    {
        clockOffsetBool = false;
        clockPosition.y -= (calcSize()/20);
    }
    //if digital bool is being turned on, and there is no offset move clock down
    else if(!clockOffsetBool && digitalClockBool)
    {
        clockOffsetBool = true;        
        clockPosition.y += (calcSize()/20);
    }

    //update all elements
    update();
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
    //update all elements
    update();
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
    //update all elements
    update();
}

//getter function for clock position
sf::Vector2f CClock::getPosition()
{
    return clockPosition;
}

//setter function for clock position
void CClock::setPosition(sf::Vector2f position)
{
    //change clock position
    clockPosition = position;
    //if digital clock is turned on, offset needs to be recalculated
    if(digitalClockBool)
    {
        clockOffsetBool = true;        
        clockPosition.y += (calcSize()/20);
    }
    //update all elements
    update();
}

//calc size returns either width or heigh of clock depending on which on is smaller
unsigned int CClock::calcSize()
{
    return (clockSize.y < clockSize.x ? clockSize.y : clockSize.x);
}

//draw all objects in correct order
void CClock::draw(sf::RenderTarget& target, sf::RenderStates states) const
{ 
    //only draw digital clock when digialClockBool is true
    if(digitalClockBool)
        target.draw(*digitalClock);
    target.draw(*numberArray);
    target.draw(*analogClock);
}