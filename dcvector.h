#ifndef _DESCARTES_VECTOR_H_
#define _DESCARTES_VECTOR_H_

#include "linesegment.h"
#include "units.h"


/*
    A vector is a direction from 0,0,0.
*/
class DCVector : public Point
{
public:
    DCVector(const float& x, const float& y, const float& z);
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
};

#endif //_DESCARTES_VECTOR_H_
