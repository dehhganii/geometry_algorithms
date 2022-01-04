#pragma once

#include <vector>
/**
 * @brief The classes for visualizing the result with being able to set width and height of the output.
 * Drawing dots and lines
 */
struct Color
{
    float r, g, b;

    Color();
    Color(float r, float g, float b);
    ~Color();
};

/**
 * @brief The class for visualizing the output
 * 
 */
class Graphic
{
public:
    /**
    * @brief Construct a new Graphic object
    * 
    * @param width Default width of the frame
    * @param height Default height of the frame
    */
    Graphic(uint64_t width, uint64_t height);
    /**
     * @brief Destroy the Graphic object
     * 
     */
    ~Graphic();
    /**
     * @brief Get the color object
     * 
     * @param x firs coordinate
     * @param y second coordinate
     * @return Color the (r, g, b) color of the pixel
     */
    Color get_color(uint16_t x, uint16_t y) const;
    /**
     * @brief Set the color object
     * 
     * @param color (r, g, b) tuple to set
     * @param x First coordinate of the pixel
     * @param y Second coordinate of the pixel
     */
    void set_color(const Color& color, int64_t x, int64_t y);
    /**
     * @brief Draw a point with not just a pixel for better illustration
     * 
     * @param color The color of the point
     * @param x First coordinate of the pixel
     * @param y Second coordinate of the pixel
     */
    void draw_point(const Color& color, int64_t x, int64_t y);
    /**
     * @brief Draw a line between to given points
     * 
     * @param color The color of the line
     * @param x1 First coordinate of the first point
     * @param y1 Second coordinate of the first point
     * @param x2 First coordinate of the second point
     * @param y2 Second coordinate of the second point
     * @param m The slope between these two points
     */
    void draw_line(const Color& color, int64_t x1, int64_t y1, int64_t x2, int64_t y2, double m);
    /**
     * @brief Store the result and make a bmp file
     * 
     * @param path The address of the stored file
     */
    void Export(const char* path) const;

private:
    uint64_t m_width;
    uint64_t m_height;
    std::vector<Color> m_colors;
};
