#ifndef _DESCARTES_VECTOR2_H_
#define _DESCARTES_VECTOR2_H_

#include "units.h"
#include "point2.h"


/*
    A vector is a direction from 0,0,0.
*/
class DCVector2 : public Point2
{
public:
    DCVector2(const float& x, const float& y);
	DCVector2(Point2 p_arg);
	DCVector2(Point2 origin_arg, Point2 destination_arg);

	DCVector2 operator*(const float& s) const;
	DCVector2 operator*=(const float& s);
	DCVector2 operator/(const float& s) const;
	DCVector2 operator/=(const float& s);

    /*
        Returns the magnitude (the length) of this vector
        from 0,0,0.
    */
    mm Magnitude() const;

    /*
        Calculate the dot product between this vector and v.
    */
    mm Dot(DCVector2 v) const;

    /*
        Calculate the angle in degrees between this vector and v.
    */
    degrees AngleBetween(DCVector2 v) const;

    /*
        Evaluate whether the point p lies along this vector.
    */
    LRO LeftRightOrOn(Point2 p) const;
};

#endif //_DESCARTES_VECTOR2_H_
