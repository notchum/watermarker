
#include "intersection.hpp"

bool isOverlapping(iPoint l1, iPoint r1, iPoint l2, iPoint r2) 
{
   // To check if either rectangle is actually a line
   // For example :  l1 ={-1,0}  r1={1,1}  l2={0,-1}  r2={0,1}
   if (l1.x == r1.x || l1.y == r2.y || l2.x == r2.x || l2.y == r2.y) 
   {
      // the line cannot have positive overlap
      return false;
   }

   // If one rectangle is on left side of other
   if (l1.x >= r2.x || l2.x >= r1.x)
   {
      return false;
   }

   // If one rectangle is above other
   if (l1.y <= r2.y || l2.y <= r1.y)
   {
      return false;
   }

   return true;
} // end isOverlapping()