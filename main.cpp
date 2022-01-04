/**
 * @file main.cpp
 * @author dehghh1@mcmaster.ca
 * @brief The main function to get inputs from terminal, check if they are valid inputs.
 * Construct objects of different algorithms. Call the solve method to get the output of each algorithm.
 * @version 0.1
 * @date 2022-01-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "point.hpp"
#include "GeometryAlgorithms.hpp"
#include "Utility.hpp"
#include "ConvexHull.hpp"
#include "graphic.hpp"
#include "ClosestPair.hpp"
#include "Polygon.hpp"
#include <iostream>
#include <vector>

using namespace std;
/**
 * @brief The main function to run and call all the algorithms
 * 
 * @param argc Number of inputs from terminal
 * @param argv Each input that is gotten from the terminal
 * @return int If the code reached the end
 */
int main(int argc, char *argv[])
{
    // Check if number of inputs are right or not
    if(argc != 6)
    {
        cout << "Usage: ./geometric_algorithms  <closest pair file address> <convex hull points address> <polygon points address> <given x> <given y>"<< endl;
        return -1;
    }

    /**
     * @brief Make an object from convex hull class which inherits from geometry algorithms class
     * Get the address to read points. Call the solve method.
     */
    GeometryAlgorithms* alg;

    ConvexHull convex_hull;

    alg = &convex_hull;
    alg->read_points(argv[1]);
    alg->solve();
    
    
    /**
     * @brief Make an object from closest pair class which inherits from geometry class
     * Get the address to read points. Call the solve method.
     */
    GeometryAlgorithms* alg1;
    ClosestPair closest_pair;

    alg1 = &closest_pair;
    alg1->read_points(argv[2]);
    alg1->solve();
    
    // Check if the given point coordinates for polygon algorithm is positive integer or not
    if(!Utility::isPosNumber(argv[4]))
    {
        cout << "the x coordinate of given point for polygon must be positive integer" << endl;
        return -1;
    }
    if(!Utility::isPosNumber(argv[5]))
    {
        cout << "the y coordinate of given point for polygon must be positive integer" << endl;
        return -1;
    }
    /**
     * @brief Make an object from polygon class which inherits from geometry class
     * Get the address and given point to read points. Call the solve method.
     */
    GeometryAlgorithms* alg2;
    Polygon polygon;
    polygon.given_point.set_cooridnates(stoi(argv[4]), stoi(argv[5]));
    alg2 = &polygon;
    alg2->read_points(argv[3]);
    alg2->solve();
    return 0;
    
}

