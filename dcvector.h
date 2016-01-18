#ifndef _DESCARTES_VECTOR_H_
#define _DESCARTES_VECTOR_H_

#include "point.h"
#include "linesegment.h"
#include "units.h"


/*
    LRO is an enum that represents whether something is to
    the left or right of something else, or whether they
    are practically colinear.
*/
enum LRO
{
    ON,
    LEFT,
    RIGHT
};


/*
    A vector is a direction from 0,0,0.
*/
class DCVector
{
public:
	DCVector(Point p_arg);
	DCVector(Point origin_arg, Point destination_arg);
	DCVector(LineSegment line_arg);

	DCVector operator*(const float& s) const;
	DCVector operator*=(const float& s);
	DCVector operator/(const float& s) const;
	DCVector operator/=(const float& s);

    /*
        Returns the magnitude (the length) of this vector
        from 0,0,0.
    */
    mm Magnitude() const;

    /*
        Calculate the dot product between this vector and v.
    */
    mm Dot(DCVector v) const;

    /*
        Calculate the angle in degrees between this vector and v.
    */
    degrees AngleBetween(DCVector v) const;

    /*
        Evaluate whether the point p lies along this vector.
    */
    LRO LeftRightOrOn(Point p) const;

private:	
	Point p;
};

#endif //_DESCARTES_VECTOR_H_
