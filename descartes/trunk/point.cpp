#include "point.h"

#include "dcvector.h"

#include <stdexcept>

using namespace std;


Point::Point()
    : _x(NAN), _y(NAN), _z(NAN)
{}


Point::Point(const mm& x_arg, const mm& y_arg, const mm& z_arg)
    : _x(x_arg), _y(y_arg), _z(z_arg)
{}


Point::~Point()
{
}


bool Point::operator==(const Point& right) const
{
    return _x == right._x && _y == right._y && _z == right._z;
}


Point Point::operator-(const DCVector& right) const
{
    mm x = this->_x - right._x;
    mm y = this->_y - right._y;
    mm z = this->_z - right._z;
    return Point(_x, _y, _z);
}


Point Point::operator-=(const DCVector& right)
{
    *this = *this - right;
    return *this;
}


Point Point::operator+(const DCVector& right) const
{
    mm x = this->_x + right._x;
    mm y = this->_y + right._y;
    mm z = this->_z + right._z;
    return Point(_x, _y, _z);
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
    if (!IsRational())
        return mm(NAN);

    Point temp = *this - j;

    return sqrt(temp._x*temp._x + temp._y*temp._y + temp._z*temp._z);
}


bool Point::IsRational() const
{
    return isan(_x) && isan(_y) && isan(_z);
}


mm Point::operator[](unsigned int index) const
{
    switch (index)
    {
    case 0:
        return _x;
    case 1:
        return _y;
    case 2:
        return _z;
    default:
        throw(runtime_error("You tried to access an axis of this point that doesn't exist."));
    }
}

