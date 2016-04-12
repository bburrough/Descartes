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
    Point();
    Point(const mm& x_arg, const mm& y_arg, const mm& z_arg);
    virtual ~Point();

    bool operator==(const Point& right) const;
    Point operator-(const DCVector& right) const;
    Point operator-=(const DCVector& right);
    Point operator+(const DCVector& right) const;
    Point operator+=(const DCVector& right);
    mm operator[](unsigned int index) const;

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
        are actual values.  It will return false if they
        are not numbers.
    */
    bool IsRational() const;


private:
    mm _x;
    mm _y;
    mm _z;
};


/*
class Point4 : public Point
{
    bool operator==(const Point& right) const;
    Point operator-(const DCVector& right) const;
    Point operator-=(const DCVector& right);
    Point operator+(const DCVector& right) const;
    Point operator+=(const DCVector& right);

};
*/

#endif //_POINT_H_
