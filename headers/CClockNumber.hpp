#pragma once
#include <SFML/Graphics.hpp>
#include <string>

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
        //setter function sets static radius variable
        static void setRadius(float);
        //getter function returns static radius variable
        static float getRadius();
        //set size of both line members
        void setSize(sf::Vector2f, sf::Vector2f);
        //setter for m_number
        void setNumber(unsigned int, float);
        //getter for m_number
        unsigned int getNumber();
    private:
        //variables for number and number string
        unsigned int m_number;
        sf::Text m_numberText;
        sf::Font m_numberFont;
        //static variable to save position of all elements
        static sf::Vector2f m_position;
        //static variable to save origin of all elements
        static sf::Vector2f m_origin;
        //static vartiable for radius
        static float m_radius;
        //variable to save rotation, differs for every elements
        float m_rotation;
        //two rectangles one to display, one to cover unwanted part
        sf::RectangleShape mainRect;
        sf::RectangleShape coverRect;
        //virtual draw function
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};