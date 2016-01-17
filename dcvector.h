#ifndef _DESCARTES_VECTOR_H_
#define _DESCARTES_VECTOR_H_

#include "point.h"
#include "linesegment.h"
#include "units.h"



enum LRO
{
    ON,
    LEFT,
    RIGHT
};


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
    mm Magnitude() const;
    mm Dot(DCVector v) const;
    degrees AngleBetween(DCVector v) const;
    LRO LeftRightOrOn(Point p) const;

private:	
	Point p;
};

#endif //_DESCARTES_VECTOR_H_
