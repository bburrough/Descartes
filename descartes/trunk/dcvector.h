#ifndef _DESCARTES_VECTOR_H_
#define _DESCARTES_VECTOR_H_

#include "point.h"
#include "units.h"

class DCVector
{
public:
	DCVector(Point p_arg);
	DCVector(Point origin_arg, Point destination_arg);
	DCVector(LineSegment line_arg);

	mm Magnitude() const;
	mm Dot(Vector v) const;
	degrees AngleBetween(Vector v) const;
	DCVector operator*(const float& s) const;
	DCVector operator*=(const float& s);
	DCVector operator/(const float& s) const;
	DCVector operator/=(const float& s);

private:	
	Point p;
};

#endif //_DESCARTES_VECTOR_H_
