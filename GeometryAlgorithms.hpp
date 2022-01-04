#pragma once
#include "point.hpp"
#include <vector>
#include <string>

class GeometryAlgorithms
{
public:
    /**
     * @brief general class for making objects based on virtual classes
     * 
     * @param address The address of the points file
     */
    virtual void read_points(std::string address);
    virtual void solve();
};
