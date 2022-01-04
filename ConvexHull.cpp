
/**
 * @file ConvexHull.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-12-19
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "GeometryAlgorithms.hpp"
#include "point.hpp"
#include "ConvexHull.hpp"
#include "Utility.hpp"
#include "Graphic.hpp"
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;
void ConvexHull::read_points(std::string address)
{
    points = Utility::read_points(address);
}

/**
 * @brief Main method to solve the problem with calling other methods in the classes
 * 
 */
void ConvexHull::solve()
{
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
    double y_min = points[0].get_coordinates()[1];
    int64_t min = 0;
    for (size_t i = 0; i < points.size(); i++)
    {
        double y = points[i].get_coordinates()[1];
        if ((y < y_min) || (y_min == y && points[i].get_coordinates()[0] < points[min].get_coordinates()[0]))
        {
            y_min = points[i].get_coordinates()[1];
            min = i;
        }
    }
    // cout ;<< min << endl
    // change index of a first point with lowest most left point in the points
    swap(points[0], points[min]);
    // define a point variable and set the coordinates as same as points[0]
    p0.set_cooridnates(points[0].get_coordinates()[0], points[0].get_coordinates()[1]);
    // sort all the point based on the orientation of them with p0
    sort(points.begin() + 1, points.end(),
         [&](const point &lhs, const point &rhs) -> bool
         {
             int8_t o = orientation(p0, lhs, rhs);

             if (o == 0)
             {
                 if (Utility::square_distance(p0, rhs) >= Utility::square_distance(p0, lhs))
                 {
                     return 1;
                 }
                 else
                 {
                     return 0;
                 }
             }
             if (o == 2)
             {
                 return 1;
             }
             else
             {
                 return 0;
             }
         });
    // print out the points and change the color of these points in the .bmp file
    cout << "------------" << endl;
    for (size_t i = 0; i < points.size(); i++)
    {
        cout << "(" << points[i].get_coordinates()[0] << ", " << points[i].get_coordinates()[1] << ")" << endl;
    }
    cout << "------------" << endl;
    uint64_t m = 1;
    for (size_t i = 1; i < points.size(); i++)
    {
        while (i < points.size() - 1 && orientation(p0, points[i], points[i + 1]) == 0)
        {
            i++;
        }
        points[m] = points[i];
        m++;
    }

    if (m < 3)
    {
        return;
    }
    // Stack to build the answer of the problem
    stack<point> s;
    s.push(points[0]);
    s.push(points[1]);
    s.push(points[2]);

    for (size_t i = 3; i < m; i++)
    {
        while (s.size() > 1 && orientation(nextToTop(s), s.top(), points[i]) != 2)
        {
            s.pop();
        }
        s.push(points[i]);
    }
    vector<point> ans_points;
    while (!s.empty())
    {
        // Change color of the points in the answer
        point p = s.top();
        cout << "(" << p.get_coordinates()[0] << ", " << p.get_coordinates()[1] << ")" << endl;
        ans_points.push_back(p);
        graphic.draw_point(Color(100, 0, 0), (int64_t)p.get_coordinates()[0], (int64_t)p.get_coordinates()[1]);
        s.pop();
    }
    cout << "SIZE IS: " << ans_points.size() << endl;
    for (size_t i = 0; i < ans_points.size() - 1; i++)
    {
        graphic.draw_line(Color(100, 100, 100), (int64_t)ans_points[i].get_coordinates()[0], (int64_t)ans_points[i].get_coordinates()[1],
                          (int64_t)ans_points[i + 1].get_coordinates()[0], (int64_t)ans_points[i + 1].get_coordinates()[1], Utility::line_slope(ans_points[i], ans_points[i + 1]));
    }
    graphic.draw_line(Color(100, 100, 100), (int64_t)ans_points[ans_points.size() - 1].get_coordinates()[0], (int64_t)ans_points[ans_points.size() - 1].get_coordinates()[1],
                      (int64_t)ans_points[0].get_coordinates()[0], (int64_t)ans_points[0].get_coordinates()[1], Utility::line_slope(ans_points[ans_points.size() - 1], ans_points[0]));
    graphic.Export("convex_hull.bmp");
}
/**
 * @brief Get the stack and return second top point of the stack
 * 
 * @param s The stack
 * @return point The second top point
 */
point ConvexHull::nextToTop(stack<point> &s)
{
    point p = s.top();
    s.pop();
    point res = s.top();
    s.push(p);
    return res;
}
/**
 * @brief Swap two given points index in points vector
 * 
 * @param p1 First point
 * @param p2 Second point
 */
void ConvexHull::swap(point &p1, point &p2)
{
    point temp = p1;
    p1 = p2;
    p2 = temp;
}

/**
 * @brief The position of three points
 * collinear, clockwise, and countclockwise
 * @param p First point
 * @param q Second point
 * @param r Third point
 * @return int8_t 
 */
int8_t ConvexHull::orientation(const point &p, const point &q, const point &r)
{
    double val = ((q.get_coordinates()[1] - p.get_coordinates()[1]) * (r.get_coordinates()[0] - q.get_coordinates()[0]) -
                  (q.get_coordinates()[0] - p.get_coordinates()[0]) * (r.get_coordinates()[1] - q.get_coordinates()[1]));
    if (val == 0)
    {
        return 0;
    }
    return (val > 0) ? 1 : 2;
}

/**
 * @brief Compare two points based on orientation to the p0 point
 * 
 * @param vp1 First point
 * @param vp2 Second point
 * @return int8_t {-1, 0, 1}
 */
int8_t ConvexHull::compare(const void *vp1, const void *vp2)
{
    point *p1 = (point *)vp1;
    point *p2 = (point *)vp2;

    int8_t o = orientation(p0, *p1, *p2);

    if (o == 0)
    {
        if (Utility::square_distance(p0, *p2) >= Utility::square_distance(p0, *p1))
        {
            return -1;
        }
        else
        {
            return 1;
        }
    }
    return (o == 2) ? -1 : 1;
}