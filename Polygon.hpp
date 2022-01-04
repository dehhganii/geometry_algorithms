#pragma once

#include "point.hpp"
#include "GeometryAlgorithms.hpp"
#include <vector>
/**
 * @brief This class is for number of points which construct a polygon, the order of points is the order of vertices of the polygon
 * Another point is given and in the solve method it figure out whether the point is inside or outside of the polygon
 */
class Polygon : public GeometryAlgorithms
{
public:
    /**
     * @brief The general method which the solving part of class happens here
     * 
     */
    void solve() override;
    /**
     * @brief Read points from file using Utility class
     * 
     */
    void read_points(std::string) override;
    /**
     * @brief The position of the points in respect to eachother.
     * 
     * @param p First point
     * @param q Second point
     * @param r Third point
     * @return int8_t {0, 1, 2} based on the position
     */
    int8_t orientation(const point &p, const point &q, const point &r);
    /**
     * @brief Check whether the point is on the one of the edges of the polygon oer not
     * 
     * @param p First point
     * @param q Second point
     * @param r Third point
     * @return true On the pr line
     * @return false otherwise
     */
    bool on_segment(const point &p, const point &q, const point &r);
    /**
     * @brief Check whether a point has intersect with a line given by two points
     * 
     * @param p1 First point in first line
     * @param q1 Second point in first line
     * @param p2 First point in second line
     * @param q2 Second point in second line
     * @return true If two lines intersect
     * @return false Otherwise
     */
    bool do_intersect(const point &p1, const point &q1, const point &p2, const point &q2);
    /**
     * @brief Check whether the point is inside or outside of the polygon
     * 
     * @return true If point is insided polygon
     * @return false Otherwise
     */
    bool is_inside();
    /**
     * @brief The given point which is needed to get checked 
     * 
     */
    point given_point;
private:
    std::vector<point> points;
    
};