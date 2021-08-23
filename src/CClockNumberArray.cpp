#include "../headers/CClockNumberArray.hpp"

using namespace sf;

//constructor with references to values from clock
CClockNumberArray::CClockNumberArray(const float& radius, const float& thickness, const Vector2f& position, const Color& color) :
m_radius(radius),
m_thickness(thickness),
m_position(position),
m_color(color),
//allocate memory for 12 objects
m_number_array(new CClockNumber[12])
{
    this->update();
}

//deletes all entries in numberArray
CClockNumberArray::~CClockNumberArray()
{
    delete[] m_number_array;
}

//updates all entries of numberArray
void CClockNumberArray::update()
{
    //set static origin member variable to passed reference parameter from constructor
    m_number_array->setOrigin(Vector2f(0, (m_thickness)/ 2));
    //set static position member variable to passed reference parameter from constructor
    m_number_array->setPosition(m_position);
    //set static radius member variable to passed reference parameter from constructor
    m_number_array->setRadius(m_radius);
    //loop through all elements of array
    for (int i = 0; i < 12; i++)
    {
        //set color
        m_number_array[i].setColor(m_color);
        //set number and font size
        m_number_array[i].setNumber(i, m_thickness * 10);
        //set size of element (first size for visible line, second size for invisible line)
        m_number_array[i].setSize(Vector2f(m_radius/15, m_thickness));
        //set rotation according to n
        m_number_array[i].setRotation(i * 30);
        //update origin and position of both lines in object
        m_number_array[i].update();
    }
}

//virtual draw function loops through all objects and draws them
void CClockNumberArray::draw(RenderTarget& target, RenderStates states) const
{
    for (int i = 0; i < 12; i++)
    {
        target.draw(m_number_array[i]);
    }
}