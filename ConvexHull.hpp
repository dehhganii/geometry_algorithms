#pragma once
#include "point.hpp"
#include "GeometryAlgorithms.hpp"
#include <vector>
#include <stack>
/**
 * @brief Class for getting all points and return the convex hull of them
 * 
 */
class ConvexHull : public GeometryAlgorithms
{
public:
    /**
     * @brief Call other class members to solve the convex hull problem
     * 
     */
    void solve() override;
    /**
     * @brief Read points from file
     * 
     */
    void read_points(std::string) override;
    /**
     * @brief Get stack and get second top points of the stack
     * 
     * @param s The stack
     * @return point The second top point in stack
     */
    point nextToTop(std::stack<point> &s);
    /**
     * @brief Swap points of two points
     * 
     * @param p1 First point
     * @param p2 Second point
     */
    void swap(point &p1, point &p2);
    /**
     * @brief Compare function for two points
     * 
     * @param vp1 First point
     * @param vp2 Second point
     * @return int8_t The comparison result {-1, 0, 1}
     */
    int8_t compare(const void *vp1, const void *vp2);
    /**
     * @brief The position of three points in respect to each other
     * 
     * @param p First point
     * @param q Second point
     * @param r Third point
     * @return int8_t {0, 1, 2}
     */
    int8_t orientation(const point &p, const point &q, const point &r);
    point p0;   
private:
    std::vector<point> points;

};

