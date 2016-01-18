#ifndef _POINT2_H_
#define _POINT2_H_

#include "units.h"

class DCVector2;

/*
    Represents a two dimensional point in space.  Units
    of measure are millimeters.
*/
class Point2
{
public:
    Point2(mm x_arg = NAN, mm y_arg = NAN);
    virtual ~Point2();

    bool operator==(const Point2& right) const;
    Point2 operator-(const DCVector2& right) const;
    Point2 operator-=(const DCVector2& right);
    Point2 operator+(const DCVector2& right) const;
    Point2 operator+=(const DCVector2& right);

    mm GetX() const;
    mm GetY() const;

    void SetX(mm x);
    void SetY(mm y);

    /*
        Returns the distance between this point and j
        in millimeters.
    */
    mm Distance(Point2 j) const;

    /*
        IsRational is used to check whether this Point2
        is complete.  It will return true if x, y, and z
        are actual points.  It will return false if they
        are not numbers.
    */
    bool IsRational() const;

private:
    mm _x;
    mm _y;
};


#endif //_POINT2_H_
