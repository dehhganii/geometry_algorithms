#include "GeometryAlgorithms.hpp"
#include "Polygon.hpp"
#include "point.hpp"
#include "Utility.hpp"
#include "Graphic.hpp"
#include <iostream>
#include <vector>

using namespace std;
/**
 * @brief Read points with using Utility class
 * 
 * @param address The address of the file points must be read from
 */
void Polygon::read_points(std::string address)
{
    points = Utility::read_points(address);
}
/**
 * @brief The position of three points in respect to eachother. 
 * 0 --> Collinear
 * 1 --> Clockwise
 * 2 --> Counterclockwise
 * @param p First point
 * @param q Second point
 * @param r Third point
 * @return int8_t The position could be 0, 1, and 2
 */
int8_t Polygon::orientation(const point &p, const point &q, const point &r)
{
    double val = ((q.get_coordinates()[1] - p.get_coordinates()[1]) * (r.get_coordinates()[0] - q.get_coordinates()[0]) - 
                  (q.get_coordinates()[0] - p.get_coordinates()[0]) * (r.get_coordinates()[1] - q.get_coordinates()[1]));
    if(val == 0)
    {
        return 0;
    }
    return (val > 0)? 1: 2;
}

/**
 * @brief Gets three collinear points check if q lies on line pr or not
 * 
 * @param p First point of line
 * @param q Point needes to be checked
 * @param r Second point of line
 * @return true If q point lies on pr line
 * @return false Otherwise
 */
bool Polygon::on_segment(const point &p, const point &q, const point &r)
{
    if((q.get_coordinates()[0] <= max(p.get_coordinates()[0], r.get_coordinates()[0])) &&
       (q.get_coordinates()[0] >= min(p.get_coordinates()[0], r.get_coordinates()[0])) &&
       (q.get_coordinates()[1] <= max(p.get_coordinates()[1], r.get_coordinates()[1])) &&
       (q.get_coordinates()[1] >= min(p.get_coordinates()[1], r.get_coordinates()[1])))
       {
           return true;
       }
    return false;
}
/**
 * @brief Based on comparison of orientation of four points checks whether line p1q1 intersect with p2q2 line or not
 * 
 * @param p1 First point of first line
 * @param q1 Second point of first line
 * @param p2 First point of second line
 * @param q2 Second point of second line
 * @return true If these two lines intersect
 * @return false Otherwise
 */
bool Polygon::do_intersect(const point &p1, const point &q1, const point &p2, const point &q2)
{
    // Orientation of first line with p2
    int8_t o1 = orientation(p1, q1, p2);
    // Orientation of first line with q2
    int8_t o2 = orientation(p1, q1, q2);
    // Orientation of second line with p1
    int8_t o3 = orientation(p2, q2, p1);
    // Orientation of second line with q1
    int8_t o4 = orientation(p2, q2, q1);

    if(o1 != o2 && o3 != o4)
    {
        return true;
    } 
    // p1, q1 and p2 are collinear and p2 lies on segment p1q1
    if(o1 == 0 && on_segment(p1, p2, q1))
    {
        return true;
    }
    // p1, q1 and q2 are collinear and q2 lies on segment p1q1
    if(o2 == 0 && on_segment(p1, q2, q1))
    {
        return true;
    }
    // p2, q2 and p1 are collinear and p1 lies on segment p2q2
    if(o3 == 0 && on_segment(p2, p1, q2))
    {
        return true;
    }
    // p2, q2 and q1 are collinear and q1 lies on segment p2q2
    if(o4 == 0 && on_segment(p2, q1, q2))
    {
        return true;
    }

    return false;
}

/**
 * @brief Based on number of intersects method returns whether the point is inside or outside the polygon
 * 
 * @return true If point is inside
 * @return false If point is outside
 */
bool Polygon::is_inside()
{
    uint64_t number_of_points = points.size();
    // When there is no polygon at all
    if ( number_of_points < 3)
    {
        return false;
    }
    // A point with minimum value for x coordinate and same as give point y coordinate
    point extreme(__DBL_MIN__, given_point.get_coordinates()[1]);
    // Number of intersects
    uint8_t count = 0;
    // Index of the point
    uint64_t i = 0;

    do 
    {
        uint64_t next_point = (i+1) % number_of_points;
        // Check intersect of line p-extreme with polygon[i]-polygon[i+1]
        if(do_intersect(points[i], points[next_point], given_point, extreme))
        {
            // If p is collinear with line i-next 
            if(orientation(points[i], given_point, points[next_point]) == 0)
            {
                // Check if it lies on segment
                return on_segment(points[i], given_point, points[next_point]);
            }
            count ++;
        }
        i = next_point;
    }
    while(i != 0);
    // Return true if count is odd
    return (count %2 == 1);
}
/**
 * @brief Main method for visualizing and solving the problem with using other methods
 * 
 */
void Polygon::solve()
{
    // The size of the bmp file
    double max_coordinate = 0;
    for(size_t i = 0; i < points.size(); i++)
    {
        // Find the max value for points
        if(max(points[i].get_coordinates()[0], points[i].get_coordinates()[1]) > max_coordinate)
        {
            max_coordinate = max(points[i].get_coordinates()[0], points[i].get_coordinates()[1]); 
        }
    }
    // Compare with the given point as well
    if(max(given_point.get_coordinates()[0], given_point.get_coordinates()[1]) > max_coordinate)
    {
        max_coordinate = max(given_point.get_coordinates()[0], given_point.get_coordinates()[1]);
    }
    // Set the plot bigger than the max value 
    const int64_t width = (int64_t) max_coordinate + 50;
    const int64_t height = (int64_t) max_coordinate + 50;
    // Construct the plot
    Graphic graphic(width, height);
    for(size_t i = 0; i < points.size(); i++)
    {
        graphic.draw_point(Color(0, 100, 100), (int64_t) (points[i].get_coordinates()[0]), (int64_t) (points[i].get_coordinates()[1]));
    }
    if(is_inside() == 1)
    {
        cout << "The point is inside the polygon" << endl;
    }

    else
    {
        cout << " The point is outside the polygon" << endl;
    }
    // Draw points 
    graphic.draw_point(Color(100, 0, 0), (int64_t) (given_point.get_coordinates()[0]), (int64_t) (given_point.get_coordinates()[1]));
    // Draw edges of the polygon
    for(size_t i = 0; i < points.size() - 1; i++)
    {
        graphic.draw_line(Color(0, 100, 0), (int64_t) (points[i].get_coordinates()[0]), (int64_t) (points[i].get_coordinates()[1]),
         (int64_t) (points[i+1].get_coordinates()[0]), (int64_t) (points[i+1].get_coordinates()[1]), Utility::line_slope(points[i], points[i+1]));
    }
    graphic.draw_line(Color(0, 100, 0), (int64_t) points[points.size() - 1].get_coordinates()[0], (int64_t) (points[points.size() - 1].get_coordinates()[1]),
         (int64_t) (points[0].get_coordinates()[0]), (int64_t) (points[0].get_coordinates()[1]), Utility::line_slope(points[points.size() - 1], points[0]));
    // Save the file as a bmp file with name polygon
    graphic.Export("polygon.bmp");
}
