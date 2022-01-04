/**
 * @file ClosestPair.hpp
 * @author dehghh1@mcmaster.ca
 * @brief 
 * @version 0.1
 * @date 2021-12-20
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#pragma once

#include "point.hpp"
#include "GeometryAlgorithms.hpp"
#include "Graphic.hpp"
#include <vector>

/**
 * @brief class for solving the closest pair problem
 * 
 */
class ClosestPair : public GeometryAlgorithms
{
public:
    /**
     * @brief the solving part of the algorithm with calling other class members
     * 
     */
    void solve() override;
    /**
     * @brief Read points with using Utility class members
     * 
     * @param address The address of the file.
     */
    void read_points(std::string address) override;
    /**
     * @brief Distance of two points using square distance member in Utility class
     * 
     * @param p1 First point
     * @param p2 Second point
     * @return double Distance between two points
     */
    double dist(const point &p1, const point &p2) const;
    /**
     * @brief Gets two number and return the minimum one
     * 
     * @param x First number
     * @param y Second number
     * @return double The minimum one
     */
    double min(double x, double y);
    /**
     * @brief The brute force algorithm for finding closest pair of points
     * 
     * @param ps points vector
     * @param n number of points
     * @return double Minimum distance between points
     */
    double brute_force(std::vector<point> ps, uint64_t n);
    /**
     * @brief Compare sorted points distance
     * 
     * @param strip Sorted points
     * @param size number of points
     * @param d Current minimum distance
     * @return double New minimum distance 
     */
    double strip_closest(std::vector<point> strip,uint64_t size, double d);
    /**
     * @brief Recursive function to return closest points
     * 
     * @param px Points sorted based on x coordinate
     * @param py Points sorted based on y coordinate
     * @param n number of points
     * @return double The closest distance
     */
    double closest_util(std::vector<point> px, std::vector<point> py, uint64_t n);
private:
    std::vector<point> points;
};
