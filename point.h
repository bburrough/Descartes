#ifndef _POINT_H_
#define _POINT_H_

#include "units.h"

class Point
{
public:
    Point(mm x_arg = NAN, mm y_arg = NAN, mm z_arg = NAN);

    virtual ~Point();

    bool operator==(const Point& right) const;

    Point operator-(const Point& right) const;

    Point operator+(const Point& right) const;

    mm GetX() const;
    mm GetY() const;
    mm GetZ() const;

    void SetX(mm x);
    void SetY(mm y);
    void SetZ(mm z);

    mm Distance(Point j) const;

    bool IsRational() const;

private:
    mm _x;
    mm _y;
    mm _z;
};


#endif //_POINT_H_
