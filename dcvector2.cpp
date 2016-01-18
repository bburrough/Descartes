#include "dcvector2.h"


DCVector2::DCVector2(const float& x, const float& y)
    : Point2(x,y)
{}


DCVector2::DCVector2(Point2 p_arg)
	: Point2(p_arg)
{}


DCVector2::DCVector2(Point2 origin_arg, Point2 destination_arg)
    : Point2(destination_arg.GetX() - origin_arg.GetX(), destination_arg.GetY() - origin_arg.GetY())
{}


mm DCVector2::Magnitude() const
{
	return sqrt(GetX()*GetX() + GetY()*GetY());
}


mm DCVector2::Dot(DCVector2 v) const
{
	return (GetX() * v.GetX()) + (GetY() * v.GetY());
}


degrees DCVector2::AngleBetween(DCVector2 v) const
{
	return acos( this->Dot(v) / (this->Magnitude() * v.Magnitude()) ) * (180.0f / PI);
}


DCVector2 DCVector2::operator*(const float& s) const
{
	DCVector2 temp(*this);
	temp.SetX(temp.GetX() * s);
    temp.SetY(temp.GetY() * s);
    return temp;
}


DCVector2 DCVector2::operator*=(const float& s)
{
	this->SetX(this->GetX() * s);
    this->SetY(this->GetY() * s);
    return *this;
}


DCVector2 DCVector2::operator/(const float& s) const
{
	DCVector2 temp(*this);
	temp.SetX(temp.GetX() / s);
    temp.SetY(temp.GetY() / s);
    return temp;
}


DCVector2 DCVector2::operator/=(const float& s)
{
    this->SetX(this->GetX() / s);
    this->SetY(this->GetY() / s);
    return *this;
}


LRO DCVector2::LeftRightOrOn(Point2 theta) const
{
    float val = GetX() * theta.GetY() - GetY() * theta.GetX();
    if (FloatsEqual(val, 0.0f))
        return ON;
    else if (val < 0.0f)
        return RIGHT;
    else
        return LEFT;
}
