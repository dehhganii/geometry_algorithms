# CSE 701 Third Project #

## Introduction ##

This repository is for the third project of CSE 701 course in Fall 2021.

This project is applying three different geometric algorithms with considering time complexity of algorithms.

### 1. Closest pair points ###

The problem is that there are several points with two coordinates. The goal is to find the minimum distance between two points. The brute force approach for solving this problem is computing the distance between each two points. Then return the minimum distance. The time complexity of this approach is *O(n^2)*. This is not the ideal approach for sure. With using divide and conquer approach the time complexity could be reduced to *O(n log n)*.

### 2. Convex Hull ###

The problem is there are set of points. The goal is to find subset of that, the way the result of connecting points of the subset will be a convex hull and all other points will lie inside the polygons. There are two well-known algorithms for solving this problem. The first one is **Jarvis's algorithm**. The worst time complexity of this algorithm is *O(n^2)*. However, the implemented algorithm **Graham's scan** can solve the problem in *O(n Log n)*.

### 3. A point lies inside a polygon or not ###

The problem is that there is a set of points which makes a polygon. There is a given point. The goal is to find whether the point is inside or outside of the polygon.

The motivation behind choosing this title for the project is to experience another context of algorithms which is geometrical ones.

On top of that, Since this project was a practice for writing object oriented programming. Different geometrical classes made this topic a good way in terms of this practice.

## Implementation ##

### Classes ###

* point
  * This class is the main foundation of all the classes. All the input types are based on this class. Consisting of constructors for no variable, one variable, and two variables. Since the point coordinates are private; two methods are needed for setting them and getting them also.

* Utility
  * This class only has static methods. As a result, there is no need to have specific type of object. In this class different methods is implemented which were used in different classes.
    * Read points from a file.

    * Square distance, distance between two points.

    * Return_part, get a vector and a nonnegative integer. return part of a vector starting from the n index.

    * Line_slope, return the slope between two given points.

* Graphic

* This class is for visualizing the result of algorithms. The visualization without using any third party libraries. Using bitmap files. The other class is Color class which has only a constructor and three inputs meaning the red, green, and blue in the picture. There are five methods
  * Get_color, get a triple vector as a color.
  * Set_color, gets the triple vector color and coordinates to set that pixel in the frame to the color.
  * draw_point, draw a pixel and it's neighbors for better visualization.
  * Draw_line, gets two points and draw a line between them.
  * Export, to export the output as .bmp file.

* GeometryAlgorithm
  * This class is a parent class with only two methods, reading input and solve. No definition is needed for this class because each algorithm inherit from this class and the definition of this two methods will be override in those classes.

* Convex_hull
  * The first step in this algorithm is to find the point with the lowest y-coordinate. If the lowest y-coordinate exists in more than one point in the set, the point with the lowest x-coordinate out of the candidates should be chosen. Call this point P. This step takes O(n), where n is the number of points in question.
  * Next, the set of points must be sorted in increasing order of the angle they and the point P make with the x-axis.
  * The algorithm proceeds by considering each of the points in the sorted array in sequence. For each point, it is first determined whether traveling from the two points immediately preceding this point constitutes making a left turn or a right turn. If a right turn, the second-to-last point is not part of the convex hull, and lies 'inside' it. The same determination is then made for the set of the latest point and the two points that immediately precede the point found to have been inside the hull, and is repeated until a "left turn" set is encountered, at which point the algorithm moves on to the next point in the set of points in the sorted array minus any points that were found to be inside the hull; there is no need to consider these points again. (If at any stage the three points are collinear, one may opt either to discard or to report it, since in some applications it is required to find all points on the boundary of the convex hull).
  * This class solve the problem of finding the convex hull of n given points with using graham scan. In the lower time complexity in comparison with other well-known algorithms. There are several method in this class
  * Read_points, call read point method from Utility class.
  * Swap, change index of two points in a vector.
  * next_to_top, with getting an stack return the second top point of the stack.
  * compare, gets two point and compare it with the most left down point of the vector, which is a public variable in this class.
  * orientation, gets three different point and return the position of these three points. Three different position collinear, clockwise, and counter clockwise.

* Closest pair
  * We sort all points according to x coordinates.
  * Divide all points in two halves.
  * Recursively find the smallest distances in both subarrays.
  * Take the minimum of two smallest distances. Let the minimum be d.
  * Create an array strip[] that stores all points which are at most d distance away from the middle line dividing the two sets
  * Find the smallest distance in strip[].
  * Return the minimum of d and the smallest distance calculated in above previous step.
  * This class find the closest distance of two points in a given set of points. Different methods are in this class
    * read_points, call the method from Utility class.
    * min, find the minimum of two points based on the coordinates.
    * dist, return the sqrt of called method of Utility.
  
* Polygon
  * Draw a horizontal line to the right of each point and extend it to infinity
  * Count the number of times the line intersects with polygon edges.
  * A point is inside the polygon if either count of intersections is odd or
   point lies on an edge of polygon.  If none of the conditions is true, then
   point lies outside.
  * The class gets a polygon with having all the vertices of polygon. Then comparing with another given point. It is checked whether it is inside the polygon or not.
    * read_points, call the method from utility
    * orientation, the position of three different points in respect to each other
    * on_segment, with getting a line and a point check if the point lies within the line or not
    * do_intersect, gets two lines and check if these two lines intersect or not.
    * is_inside, check with using other method is the point inside or outside of the polygon.
    * solve, with calling other method and an object of graphic class show the result and create a file as visualization.

* Main function
  * The main function only make the variables and check the input file to be appropriate for the algorithms.

## Output ##

### How to use the code ###

write down ./geometric_algorithms and after that three file address is needed. Then x, and y coordinate for the polygon algorithm

* First points for convex hull
* Second for the closest pair
* Third for polygon points
* Fourth the x coordinate of the given point
* Fifth the y coordinate of the given point

the input file should be a txt file each line at max has two integer values.

with "," separated

>like this:

    12,30
    11,7
    .
    .
    .

### some sample outputs ###

```

./geometric_algorithms convex_hull_points.txt closest_pair_points.txt
polygon_points.txt
4
14

```

| Points_convex|
| ------------- |
(0, 0)  
(30, 10)
(10, 10)
(20, 20)
(30, 30)
(40, 40)
(10, 20)
(0, 30)

| Convex_hull |
| ----------- |
(0, 30)
(40, 40)
(30, 10)
(0, 0)

| Polygon_points |
| -------------- |
(20, 30)
(12, 35)
(40, 50)
(50, 10)
(12, 10)
(30, 40)

| closest_points |
| -------------- |
(5, 5)
(15, 5)
(15, 15)
(5, 15)
(12, 10)

The points for the closest pair the output is the distance
>9.43398

The result of polygon
> The point is outside the polygon

### Invalid Inputs ###

* if any negative input is in file.
  * > input must be nonnegative integer
* if double input is in file
  * > input must be nonnegative integer

* number of inputs something not equal five
  * > "Usage: ./geometric_algorithms  closest_pair file address convex_hull points address polygon points address given x given y"

* more than two values in one line
  * > The coordinate must be a positive integer
* error opening file
  * > Error opening file

* the algorithms run for variables in range int64 however, for visualization the variables must be integer less than 1000.

#### In this implementation I used geeksforgeeks site ####
