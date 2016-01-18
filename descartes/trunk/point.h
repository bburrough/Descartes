#ifndef _POINT_H_
#define _POINT_H_

#include "units.h"

class DCVector;

/*
    Represents a three dimensional point in space.  Units
    of measure are millimeters.
*/
class Point
{
public:
    Point(mm x_arg = NAN, mm y_arg = NAN, mm z_arg = NAN);
    virtual ~Point();

    bool operator==(const Point& right) const;
    Point operator-(const DCVector& right) const;
    Point operator-=(const DCVector& right);
    Point operator+(const DCVector& right) const;
    Point operator+=(const DCVector& right);

    mm GetX() const;
    mm GetY() const;
    mm GetZ() const;

    void SetX(mm x);
    void SetY(mm y);
    void SetZ(mm z);

    /*
        Returns the distance between this point and j
        in millimeters.
    */
    mm Distance(Point j) const;

    /*
        IsRational is used to check whether this Point
        is complete.  It will return true if x, y, and z
        are actual points.  It will return false if they
        are not numbers.
    */
    bool IsRational() const;

private:
    mm _x;
    mm _y;
    mm _z;
};


#endif //_POINT_H_
