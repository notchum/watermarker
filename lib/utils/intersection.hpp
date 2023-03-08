/** 
 * @file   intersection.hpp
 * 
 * @brief  
 * 
 * @author Morgan Chumbley
 * 
 * @date   May 23rd, 2020
 */

#ifndef INTERSECTION_HPP
#define INTERSECTION_HPP

typedef struct 
{
   int x, y;
} iPoint;

/** 
 * @brief  Finds if two given rectangles overlap or not
 * 
 * @param  l1 top left coordinate of first rectangle
 * 
 * @param  r1 bottom right coordinate of first rectangle
 * 
 * @param  l2 top left coordinate of second rectangle
 * 
 * @param  r2 bottom right coordinate of second rectangle
 * 
 * @return true if the rectangles overlap, false otherwise
 */
bool isOverlapping(iPoint l1, iPoint r1, iPoint l2, iPoint r2);

#endif // INTERSECTION_HPP