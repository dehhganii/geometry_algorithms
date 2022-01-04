/**
 * @file ClosestPair.cpp
 * @author dehghh1@mcmaster.ca
 * @brief In this class a vector of points is as an input.
 * There is an algorithm for finding the closest pair of points in terms of distance.
 * The brute force algorithm is of order O(n^2).
 * However, the implemented algorithm is order of O(n log n) with using sweep line approach. 
 * @version 0.1
 * @date 2021-12-20
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "ClosestPair.hpp"
#include "Utility.hpp"
#include "point.hpp"
#include "GeometryAlgorithms.hpp"
#include "Graphic.hpp"
#include <cmath>
#include <vector>
#include <iostream>

using namespace std;
/**
 * @brief Read points from a file and store them in a vector of points as a object of the class.
 * Use already defined method of the Utility class.
 * 
 * @param address the string hols address of the file code reads from that
 */
void ClosestPair::read_points(std::string address)
{
    points = Utility::read_points(address);
}

/**
 * @brief A method to compute the distance of two points. Using square root of already defined method of Utility class.
 * 
 * @param p1 The first point
 * @param p2 The second point to compute the distance with.
 * @return double Return the distance of two points.
 */
double ClosestPair::dist(const point &p1, const point &p2) const
{
    return sqrt(Utility::square_distance(p1, p2));
}

/**
 * @brief The method compare two values and return the smaller one.
 * 
 * @param x The first input for comparison.
 * @param y The second input for comparison.
 * @return double Return the smaller value.
 */
double ClosestPair::min(double x, double y)
{
    if (x < y)
    {
        return x;
    }
    else
    {
        return y;
    }
}

/**
 * @brief The brute force method to find the closest pair with comparing all the points distance
 * Make a bmp file as an outout of the algorithm 
 * @param ps the vector of points 
 * @param n the number of points in the vector
 * @return double: return the minimum distance between all the points
 */
double ClosestPair::brute_force(vector<point> ps, uint64_t n)
{
    size_t x1_ans = 0;
    size_t x2_ans = 1;
    double inf = __DBL_MAX__;
    for (size_t i = 0; i < n; i++)
    {

        for (size_t j = i + 1; j < n; j++)
        {
            if (dist(ps[i], ps[j]) < inf)
            {
                x1_ans = i;
                x2_ans = j;
                inf = dist(ps[i], ps[j]);
            }
        }
    }
    double max_coordinate = 0;
    for (size_t i = 0; i < points.size(); i++)
    {

        if (max(points[i].get_coordinates()[0], points[i].get_coordinates()[1]) > max_coordinate)
        {
            max_coordinate = max(points[i].get_coordinates()[0], points[i].get_coordinates()[1]);
        }
    }
    // The fixed size of the .bmp file of the output
    const int64_t width = (int64_t)max_coordinate + 50;
    const int64_t height = (int64_t)max_coordinate + 50;
    Graphic graphic(width, height);
    for (size_t i = 0; i < points.size(); i++)
    {
        graphic.draw_point(Color(0, 100, 100), (int64_t)points[i].get_coordinates()[0], (int64_t)points[i].get_coordinates()[1]);
    }
    // change the colors of those points with minimum distance
    graphic.draw_point(Color(100, 0, 0), (int64_t)points[x1_ans].get_coordinates()[0], (int64_t)points[x1_ans].get_coordinates()[1]);
    graphic.draw_point(Color(100, 0, 0), (int64_t)points[x2_ans].get_coordinates()[0], (int64_t)points[x2_ans].get_coordinates()[1]);
    // address of the output file
    graphic.Export("closest_points.bmp");
    return inf;
}
/**
 * @brief A method to find the distance between the closest points of strip of a given size.
 * The length of vector strip cannot be greater than 6 because the minimum distance could not be d anymore.
 * As a result the time complexity of the method remain O(n)
 * @param strip Vector of points sorted based on y coordinates. With d as the upper bound for distance
 * @param size The size of the strip vector
 * @param d The upper bound distance between
 * @return double Return the new minimum distance of two points.
 */
double ClosestPair::strip_closest(vector<point> strip, uint64_t size, double d)
{
    double min = d;

    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = i + 1; j < size && (strip[j].get_coordinates()[1] - strip[i].get_coordinates()[1]) < min; j++)
        {
            if (dist(strip[i], strip[j]) < min)
            {
                min = dist(strip[i], strip[j]);
            }
        }
    }
    return min;
}

/**
 * @brief A recursive function to find the smallest distance
 * 
 * @param px Contains all pointes sorted according to x coordinates.
 * @param py Contains all pointes sorted according to y coordinates.
 * @param n  Number of points.    
 * @return double Return thee minimum distace of two points based on the length of given arrays.
 */
double ClosestPair::closest_util(vector<point> px, vector<point> py, uint64_t n)
{
    if (n < 3)
    {
        return brute_force(px, n);
    }
    uint64_t mid = n / 2;
    point midPoint = px[mid];
    vector<point> points_y_left(mid);
    vector<point> points_y_right(n - mid);
    uint64_t li = 0;
    uint64_t ri = 0;
    for (size_t i = 0; i < n; i++)
    {
        if ((py[i].get_coordinates()[0] < midPoint.get_coordinates()[0] || (py[i].get_coordinates()[0] == midPoint.get_coordinates()[0])) && li < mid)
        {
            points_y_left[li++] = py[i];
        }
        else
        {
            points_y_right[ri++] = py[i];
        }
    }
    double dl = closest_util(px, points_y_left, mid);
    double dr = closest_util(Utility::return_part(px, mid - 1), points_y_right, n - mid);

    double d = min(dl, dr);

    vector<point> strip(n);
    uint64_t j = 0;
    for (size_t i = 0; i < n; i++)
    {
        if (abs(py[i].get_coordinates()[0] - midPoint.get_coordinates()[0]) < d)
        {
            strip[j] = py[i];
            j++;
        }
    }
    return strip_closest(strip, j, d);
}
/**
 * @brief Main method to find the closest pairs. Calling other methods.
 * Print out the result
 */
void ClosestPair::solve()
{
    uint64_t n = points.size();
    vector<point> px;
    vector<point> py;
    // px and py are two vectors to store the points but sorted based on their x coordinate or y coordinate respectively.
    px.assign(points.begin(), points.end());
    py.assign(points.begin(), points.end());
    // sorting method using inline function
    sort(px.begin(), px.end(),
         [&](const point &lhs, const point &rhs) -> bool
         {
             if (lhs.get_coordinates()[0] != rhs.get_coordinates()[0])
             {
                 if ((lhs.get_coordinates()[0] - rhs.get_coordinates()[0] > 0))
                 {
                     return 0;
                 }
                 else
                 {
                     return 1;
                 }
             }
             else
             {
                 if ((lhs.get_coordinates()[1] - rhs.get_coordinates()[1] > 0))
                 {
                     return 0;
                 }
                 else
                 {
                     return 1;
                 }
             }
         });
    sort(py.begin(), py.end(),
         [&](const point &lhs, const point &rhs) -> bool
         {
             if (lhs.get_coordinates()[1] != rhs.get_coordinates()[1])
             {
                 if ((lhs.get_coordinates()[1] - rhs.get_coordinates()[1] > 0))
                 {
                     return 0;
                 }
                 else
                 {
                     return 1;
                 }
             }
             else
             {
                 if ((lhs.get_coordinates()[0] - rhs.get_coordinates()[0] > 0))
                 {
                     return 0;
                 }
                 else
                 {
                     return 1;
                 }
             }
         });
    // Print out the minimum distance.
    cout << "The answer:  " << closest_util(px, py, n) << endl;
}