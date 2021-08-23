#include <SFML/Graphics.hpp>
#include <iostream>
#include "../headers/CClock.hpp"

using namespace sf;
using namespace std;

void colorCycle(CClock& clock);

Color colorArray[] = 
{  
    Color::Green,
    Color::Blue,
    Color::Red,
    Color::Magenta,
    Color::Cyan,
    Color::Yellow
};

int main()
{
    //antialiasing 
    Image icon;
    icon.loadFromFile("resources/icons/clock_icon.png");
    ContextSettings settings;
    settings.antialiasingLevel = 8;
    //get screen height
    unsigned int heigth = VideoMode::getDesktopMode().height;
    unsigned int width = VideoMode::getDesktopMode().width;
    FloatRect visibleArea(0, 0, width, heigth);
    //create non scalable window
    RenderWindow window(VideoMode(heigth / 2, heigth / 2), "Clock", Style::Titlebar | Style::Close | Style::Resize, settings);
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    //enable V-Sync
    window.setFramerateLimit(10);
    //disable repeat key press on hold
    window.setKeyRepeatEnabled(true);
    //Create clock
    CClock clockObject(window.getSize(), Vector2f(window.getSize().x/2, window.getSize().y/2), Color::Red, true, true);

    Event event;
    //window loop
    while (window.isOpen())
    {
        //event loop
        while(window.pollEvent(event))
        {
            switch(event.type)
            {
                //close window if close button is pressed
                case Event::Closed:
                    window.close();
                    break;
                case Event::Resized:
                    visibleArea = FloatRect(0, 0, event.size.width, event.size.height);
                    window.setView(View(visibleArea));
                    clockObject.setSize(window.getSize()); 
                    clockObject.setPosition(Vector2f(window.getSize().x/2, window.getSize().y/2));
                    break;
                //switch case for key press
                case Event::KeyPressed:
                    switch(event.key.code)
                    {
                        //close window if ESC is pressed
                        case Keyboard::Escape:
                            window.close(); 
                            break;
                        //change smooth mode if R is pressed
                        case Keyboard::R:
                            clockObject.setSmoothClockBool(!clockObject.getSmoothClockBool());
                            break;
                        //change smooth mode if R is pressed
                        case Keyboard::E:
                            clockObject.setDigitalClockBool(!clockObject.getDigitalClockBool());
                            break;
                        
                        case Keyboard::C:    
                            colorCycle(clockObject);                        
                            break;

                        default:
                            break;
                    }
                default:
                    break;
            }     
        }
        //call window tick from window object
        clockObject.clockTick();
        //clear window
        window.clear(Color::Transparent);
        //draw clock
        window.draw(clockObject);
        //display everything
        window.display();
    } 
    return 0;  
}

//function to change color
void colorCycle(CClock& clock)
{
    //use static counter to keep index through different function calls
    static int counter = 0;
    //set color to current counter index
    clock.setColor(colorArray[counter]);
    //increase the counter by one as long as it is not larger than the amount of colors in the array
    counter = (++counter) % (sizeof(colorArray)/sizeof(colorArray[0]));
}
