/**
 * @file Utility.cpp
 * @author dehghh1@mcmaster.ca
 * @brief 
 * @version 0.1
 * @date 2021-12-20
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "Utility.hpp"
#include "point.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

/**
 * @brief The method gets an address and by using ifstream checks each line
 * @param address The file address
 * @return vector<point> 
 */
vector<point> Utility::read_points(string address)
{
    /**
     * @brief Declare a vector to store point objects in it
     * Get the address and check if it gets open properly or not.
     * If the file is open then read each line of file.
     */
    vector<point> points;
    ifstream input(address);
    if(!input.is_open())
    {
        cout << "Error opening file" << std::endl; 
        exit(-1);
    }
    string line;
    /**
     * @brief Add an object to the vector
     * If a line has no value the default constructor with no value would be called from point class.
     * If only one value is in the file, the a constructor 
     * The file should be comma separated
    */ 
    while(getline(input, line))
    {   
        uint64_t pos = line.find(",");
        if(pos == string::npos && line.size() == 0)
        {
            points.push_back(point());
        }
        else
        {
            if(pos == string::npos)
            {
                if(isPosNumber(line))
                {
                    points.push_back(point(stod(line)));
                }
                else
                {
                    cout << "The coordinate must be a positive integers" << endl;
                    exit(-1);
                }
            }
            else
            {
                if(isPosNumber(line.substr(0, pos)) && isPosNumber(line.substr(pos+1)))
                {
                    points.push_back(point(stod(line.substr(0, pos)), stod(line.substr(pos + 1))));
                }
                else
                {
                    cout << "The coordinate must be a positive integer" << endl;
                    exit(-2);
                }
            }

        }
    }
    return points;
}

/**
 * @brief Gets two point as inputs and compute the square distance of them.
 * 
 * @param p1 Input as the first input
 * @param p2 Input as the second input
 * @return double 
 */
double Utility::square_distance(const point &p1, const point &p2)
{
    return  ((p1.get_coordinates()[0] - p2.get_coordinates()[0]) * (p1.get_coordinates()[0] - p2.get_coordinates()[0])) + 
            ((p1.get_coordinates()[1] - p2.get_coordinates()[1]) * (p1.get_coordinates()[1] - p2.get_coordinates()[1]));
            
}

/**
 * @brief The method to pass part of vector instead of the whole vector
 * 
 * @param points Input as a vector of points
 * @param part The index that will 
 * @return vector<point> 
 */
vector<point> Utility::return_part(vector<point> points, uint64_t part)
{
    vector<point> answer;
    for(size_t i = part; i < points.size(); i++)
    {
        answer.push_back(points[i]);
    }
    return answer;
}

/**
 * @brief The method gets two points and calculate the slope between these two points
 * 
 * @param p1 The first given point
 * @param p2 The second given point
 * @return double The slope it returns
 */
double Utility::line_slope(const point &p1, const point &p2)
{
    return (p2.get_coordinates()[1] - p1.get_coordinates()[1]) / (p2.get_coordinates()[0] - p1.get_coordinates()[0]);
}

/**
 * @brief The method checks whether an string is a positive integer or not
 * 
 * @param s The given string
 * @return true If the string is positive integer it returns true
 * @return false Otherwise
 */
bool Utility::isPosNumber(string s)
{
    uint64_t i = 0;

    // Checking for negative numbers
    if (s[0] == '-')
        return false;
    for (; s[i] != 0; i++)
    {
        // If (number[i] > '9' || number[i] < '0')
        if (!isdigit(s[i]))
            return false;
    }
    return true;
}
