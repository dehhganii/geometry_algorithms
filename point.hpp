#pragma once
#include <vector>
/**
 * @brief Basic class for all the algorithms and classes with having two coordinates and two methods to set and get the values for each point
 * 
 */
class point
{
public:
    /**
     * @brief Construct a new point object
     * 
     */
    point();
    /**
     * @brief Construct a new point object
     * 
     * @param _x The parameter for point coordinates
     */
    point(const double &_x);
    /**
     * @brief Construct a new point object
     * 
     * @param _x First parameter for x coordinate of point
     * @param _y Second parameter for y coordinate of point
     */
    point(const double &_x, const double &_y);

    /**
     * @brief Set the cooridnates object
     * 
     * @param _x First coordinate of the point
     * @param _y Second coordinate of the point
     */
    void set_cooridnates(const double &_x, const double &_y);
    /**
     * @brief Get the coordinates object
     * 
     * @return std::vector<double> First and second coordinate of the point
     */
    std::vector<double> get_coordinates() const;

private:
    // The initial coordinates of point
    double x = 0, y = 0;
};