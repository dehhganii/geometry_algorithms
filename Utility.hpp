#pragma once

#include <vector>
#include <string>
#include "point.hpp"
#include <string>

/**
 * @brief General class for defining method which different algorithms will use
 * 
 */
class Utility
{
public:
    /**
     * @brief Read points from a file
     * 
     * @return std::vector<point> return vector of the read points
     */
    static std::vector<point> read_points(std::string);
    /**
     * @brief The square distance between two points
     * 
     * @param p1 First point
     * @param p2 Second point
     * @return double The distance between the two points
     */
    static double square_distance(const point &p1, const point &p2);
    /**
     * @brief Get a vector and return only part of it related to the given index
     * 
     * @param points Vector of points
     * @param part The index that is given
     * @return std::vector<point> part of a given vector starting from index given
     */
    static std::vector<point> return_part(std::vector<point> points, uint64_t part);
    /**
     * @brief Gets two points as inputs and return the slope between the two points
     * 
     * @param p1 First point
     * @param p2 Second point
     * @return double The slope of the line
     */
    static double line_slope(const point &p1, const point &p2);
    /**
     * @brief To check whether the string which is read from file is positive number or not
     * 
     * @param s 
     * @return true 
     * @return false 
     */
    static bool isPosNumber(std::string s);
    
};
