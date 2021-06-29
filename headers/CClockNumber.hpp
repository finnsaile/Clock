#pragma once
#include <SFML/Graphics.hpp>

class CClockNumber : public sf::Drawable
{
    public:
        //default constructor
        CClockNumber();
        //update origin and position of both lines 
        void update();
        //set rotation of both lines
        void setRotation(float);
        //getter function returns rotation
        float getRotation();
        //setter function sets static origin variable
        static void setOrigin(sf::Vector2f);
        //getter function returns static origin
        static sf::Vector2f getOrigin();
        //setter function sets static position variable
        static void setPosition(sf::Vector2f);
                //getter function returns static position variable
        static sf::Vector2f getPosition();
        //set size of both line members
        void setSize(sf::Vector2f, sf::Vector2f);
    private:
        //static variable to save position of all elements
        static sf::Vector2f m_position;
        //static variable to save origin of all elements
        static sf::Vector2f m_origin;
        //variable to save rotation, differs for every elements
        float m_rotation;
        //two rectangles one to display, one to cover unwanted part
        sf::RectangleShape mainRect;
        sf::RectangleShape coverRect;
        //virtual draw function
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};