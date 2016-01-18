#include "point.h"

#include "dcvector.h"

Point::Point(mm x_arg, mm y_arg, mm z_arg)
    : _x(x_arg), _y(y_arg), _z(z_arg)
{}


Point::~Point()
{
}


bool Point::operator==(const Point& right) const
{
    return FloatsEqual(_x, right._x) && FloatsEqual(_y, right._y) && FloatsEqual(_z, right._z);
}


Point Point::operator-(const DCVector& right) const
{
    Point temp;
    temp._x = this->_x - right._x;
    temp._y = this->_y - right._y;
    temp._z = this->_z - right._z;
    return temp;
}


Point Point::operator-=(const DCVector& right)
{
    *this = *this - right;
    return *this;
}


Point Point::operator+(const DCVector& right) const
{
    Point temp;
    temp._x = this->_x + right._x;
    temp._y = this->_y + right._y;
    temp._z = this->_z + right._z;
    return temp;
}


Point Point::operator+=(const DCVector& right)
{
    *this = *this + right;
    return *this;
}


mm Point::GetX() const
{
    return _x;
}


mm Point::GetY() const
{
    return _y;
}


mm Point::GetZ() const
{
    return _z;
}


void Point::SetX(mm x)
{
    _x = x;
}


void Point::SetY(mm y)
{
    _y = y;
}


void Point::SetZ(mm z)
{
    _z = z;
}


mm Point::Distance(Point j) const
{
    if (isnan(_x) || isnan(_y) || isnan(_z) || isnan(j._x) || isnan(j._y) || isnan(j._z))
        return NAN;

    Point temp = *this - j;

    return sqrt(temp._x*temp._x + temp._y*temp._y + temp._z*temp._z);
}


bool Point::IsRational() const
{
    return isan(_x) && isan(_y) && isan(_z);
}
