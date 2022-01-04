#include "graphic.hpp"
#include <cmath>
#include <iostream>
#include <fstream>
using namespace std;
/**
 * @brief Construct a new Color:: Color object. It Set the color of a pixel based on three main colors.
 * The range would be in range (0, 255).
 * 
 */
Color::Color()
    : r(0), g(0), b(0)
{

}

Color::Color(float r, float g, float b)
    :r(r), g(g), b(b)
{

}

Color::~Color()
{

}
/**
 * @brief Construct a new Graphic:: Graphic object Set a bmp file with fixed width and height. Default color, black, 
 * 
 * @param width width of the file
 * @param height height of the file
 */
Graphic::Graphic(uint64_t width, uint64_t height)
    :m_width(width), m_height(height), m_colors(vector<Color>(width * height))
{

}

Graphic::~Graphic()
{

}
// A 1d vector to store the information(color of each pixel)
Color Graphic::get_color(uint16_t x, uint16_t y) const
{
    return m_colors[y * m_width + x];
}
/**
 * @brief Method to set the color of a given pixel with the coordinates being (x, y)
 * 
 * @param color The color of the pixel
 * @param x first coordinates
 * @param y Second coordinates
 */
void Graphic::set_color(const Color& color, int64_t x, int64_t y)
{
    m_colors[y * m_width + x].r = color.r;
    m_colors[y * m_width + x].g = color.g;
    m_colors[y * m_width + x].b = color.b;
}

/**
 * @brief Draw a point with changing the color of more than one point for better illustration
 * 
 * @param color color of the pixel
 * @param x the x centre of the point
 * @param y the y centre of the point
 */
void Graphic::draw_point(const Color& color, int64_t x, int64_t y)
{
    set_color(color, x, y);
    set_color(color, x-1, y);
    set_color(color, x+1, y);
    set_color(color, x, y-1);
    set_color(color, x, y+1);
}
/**
 * @brief Method to get two point and draw a line between them.
 * 
 * @param color color of the line
 * @param x1 first input x 
 * @param y1 first input
 * @param x2 second input
 * @param y2 second input
 * @param m the slope between these two points
 */
void Graphic::draw_line(const Color& color, int64_t x1, int64_t y1, int64_t x2, int64_t y2, double  m)
{
    // To draw a vertical line
    if(x1 == x2)
    {
        for(size_t i = min(y1, y2); i < (uint64_t)max(y1, y2); i++)
        {
            set_color(color, x1, i);
        }
    }
    // To draw a horizontal line
    if(y1 == y2)
    {
        for(size_t i = min(x1, x2); i < (uint64_t)max(x1, x2); i ++)
        {
            set_color(color, i, y1);
        }
    }
    // Draw a line with given slope and two given points
    else{
        if(x1 < x2)
        {
            for(int64_t i = x1; i < x2; i++)
            {
                int64_t temp = (int64_t) roundtol((m * (double)i) + ((double)y1 - m * (double)x1));
                set_color(color, i, temp);
            }
        }
        else
        {
            for(int64_t i = x2; i < x1; i++)
            {
                int64_t temp = (int64_t) roundtol((m * (double)i) + ((double)y2 - m * (double)x2));
                set_color(color, i, temp);
            }
        }
    }

}
/**
 * @brief Set a .bmp output file 
 * 
 * @param path the address of the output file
 */
void Graphic::Export(const char* path) const
{
    ofstream my_file;
    my_file.open(path, ios::out | ios::binary);

    if(!my_file.is_open())
    {
        cout << "File could not be opened" << endl;
        return;
    }
    // Set up the header of the .bmp file
    unsigned char bmpPad[3] = {0, 0, 0};
    const int64_t padding_amount = ((4 - (m_width * 3) % 4) % 4);

    const int64_t file_header_size = 14;
    const int64_t information_header_size = 40;
    const int64_t file_size = file_header_size + information_header_size + m_width * m_height * 3 + padding_amount * m_height;

    unsigned char file_header[file_header_size];
    // File type
    file_header[0] = 'B';
    file_header[1] = 'M';
    // File size
    file_header[2] = (unsigned char) file_size;
    file_header[3] = (unsigned char) (file_size >> 8);
    file_header[4] = (unsigned char) (file_size >> 16);
    file_header[5] = (unsigned char) (file_size >> 24);
    // Reserved 1 (not used)
    file_header[6] = 0;
    file_header[7] = 0;
    // Reserved 2 (not used)
    file_header[8] = 0;
    file_header[9] = 0;
    // pixel data offset
    file_header[10] = file_header_size + information_header_size;
    file_header[11] = 0;
    file_header[12] = 0;
    file_header[13] = 0;

    unsigned char information_header[information_header_size];

    // Header size
    information_header[0] = information_header_size;
    information_header[1] = 0;
    information_header[2] = 0;
    information_header[3] = 0;

    information_header[4] = (unsigned char) m_width;
    information_header[5] = (unsigned char) (m_width >> 8);
    information_header[6] = (unsigned char) (m_width >> 16);
    information_header[7] = (unsigned char) (m_width >> 24);

    information_header[8] = (unsigned char) m_height;
    information_header[9] = (unsigned char) (m_height >> 8); 
    information_header[10] = (unsigned char) (m_height >> 16);
    information_header[11] = (unsigned char) (m_height >> 24);

    information_header[12] = 1;
    information_header[13] = 0;

    information_header[14] = 24;
    information_header[15] = 0;

    information_header[16] = 0;
    information_header[17] = 0;
    information_header[18] = 0;
    information_header[19] = 0;

    information_header[20] = 0;
    information_header[21] = 0;
    information_header[22] = 0;
    information_header[23] = 0;

    information_header[24] = 0;
    information_header[25] = 0;
    information_header[26] = 0;
    information_header[27] = 0;

    information_header[28] = 0;
    information_header[29] = 0;
    information_header[30] = 0;
    information_header[31] = 0;

    information_header[32] = 0;
    information_header[33] = 0;
    information_header[34] = 0;
    information_header[35] = 0;

    information_header[36] = 0;
    information_header[37] = 0;
    information_header[38] = 0;
    information_header[39] = 0;
    // Write to the file
    my_file.write(reinterpret_cast<char*> (file_header), file_header_size);
    my_file.write(reinterpret_cast<char*> ( information_header), information_header_size);
    /**
     * @brief Set all the pixels of the bmp file to a plain plot of a color. With combination of red, blue, and green
     * 
     */
    for(size_t y = 0; y < m_height; y++)
    {
        for(size_t x = 0; x < m_width; x++)
        {
            unsigned char r = static_cast<unsigned char> (get_color((uint16_t) x, (uint16_t) y).r * 255.0f);
            unsigned char g = static_cast<unsigned char> (get_color((uint16_t) x, (uint16_t) y).g * 255.0f);
            unsigned char b = static_cast<unsigned char> (get_color((uint16_t) x, (uint16_t) y).b * 255.0f);

            unsigned char color[] = {b, g, r};

            my_file.write(reinterpret_cast<char*>(color), 3);
        }

        my_file.write(reinterpret_cast<char*>(bmpPad), padding_amount);
    }

    my_file.close();
    // Print out if the creating file gets done properly
    cout << "File created" << endl;


}