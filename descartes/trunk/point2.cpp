#include "point2.h"

#include "dcvector2.h"

Point2::Point2(mm x_arg, mm y_arg)
    : _x(x_arg), _y(y_arg)
{}


Point2::~Point2()
{
}


bool Point2::operator==(const Point2& right) const
{
    return FloatsEqual(_x, right._x) && FloatsEqual(_y, right._y);
}


Point2 Point2::operator-(const DCVector2& right) const
{
    Point2 temp;
    temp._x = this->_x - right._x;
    temp._y = this->_y - right._y;
    return temp;
}


Point2 Point2::operator-=(const DCVector2& right)
{
    *this = *this - right;
    return *this;
}


Point2 Point2::operator+(const DCVector2& right) const
{
    Point2 temp;
    temp._x = this->_x + right._x;
    temp._y = this->_y + right._y;
    return temp;
}


Point2 Point2::operator+=(const DCVector2& right)
{
    *this = *this + right;
    return *this;
}


mm Point2::GetX() const
{
    return _x;
}


mm Point2::GetY() const
{
    return _y;
}


void Point2::SetX(mm x)
{
    _x = x;
}


void Point2::SetY(mm y)
{
    _y = y;
}


mm Point2::Distance(Point2 j) const
{
    if (isnan(_x) || isnan(_y) || isnan(j._x) || isnan(j._y))
        return NAN;

    Point2 temp = *this - j;

    return sqrt(temp._x*temp._x + temp._y*temp._y);
}


bool Point2::IsRational() const
{
    return isan(_x) && isan(_y);
}
