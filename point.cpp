#include <iostream>
#include "point.hpp"
#include <vector>
using namespace std;
/**
 * @brief Construct a new point::point object
 * 
 */
point::point()
{
    set_cooridnates(0, 0);
}
/**
 * @brief Construct a new point::point object
 * 
 * @param _x Set both coordinate of the point as x
 */
point::point(const double &_x)
{
    set_cooridnates(_x, _x);
}
/**
 * @brief Construct a new point::point object
 * 
 * @param _x Set x coordinate as _x
 * @param _y Set y coordinate as _Y
 */
point::point(const double &_x, const double &_y)
{
    set_cooridnates(_x, _y);
}
/**
 * @brief Gets two value and set the coordinates of the point equal to them
 * 
 * @param _x First coordinate
 * @param _y Second coordinate
 */
void point::set_cooridnates(const double &_x, const double &_y)
{
    x = _x;
    y = _y;
}
/**
 * @brief Get a point andreturn its coordinates
 * 
 * @return std::vector<double> A vector with length 2 which returns the first and second coordinate of the point
 */
std::vector<double> point::get_coordinates() const
{
    vector<double> cooridnates(2); 
    cooridnates[0] = x;
    cooridnates[1] = y;
    return cooridnates;
}
