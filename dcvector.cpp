#include "dcvector.h"

DCVector::DCVector(Point p_arg)
	: p(p_arg)
{}

DCVector::DCVector(Point origin_arg, Point destination_arg)
{
	p = destination_arg - origin_arg;
}

DCVector::DCVector(LineSegment line_arg)
{
	p = line_arg.B - line_arg.A;
}

mm DCVector::Magnitude()
{
	return sqrt(p.GetX()*p.GetX() + p.GetY()*p.GetY() + p.GetZ()*p.GetZ());
}

mm DCVector::Dot(Vector v)
{
	return (p.GetX() * v.p.GetX()) + (p.GetY() * v.p.GetY()) + (p.GetZ() * v.p.GetZ());
}

degrees DCVector::AngleBetween(Vector v)
{
	return acos( this->Dot(v) / (this->Magnitude() * v.Magnitude()) ) * (180.0f / PI);
}

DCVector DCVector::operator*(const float& s) const
{
	Vector temp(*this);
	temp.p.SetX(temp.p.GetX() * s);
    temp.p.SetY(temp.p.GetY() * s);
    temp.p.SetZ(temp.p.GetZ() * s);
    return temp;
}

DCVector DCVector::operator*=(const float& s)
{
	this->p.SetX(this->p.GetX() * s);
    this->p.SetY(this->p.GetY() * s);
    this->p.SetZ(this->p.GetZ() * s);
    return *this;
}

DCVector DCVector::operator/(const float& s) const
{
	Vector temp(*this);
	temp.p.SetX(temp.p.GetX() / s);
    temp.p.SetY(temp.p.GetY() / s);
    temp.p.SetZ(temp.p.GetZ() / s);
    return temp;
}

DCVector DCVector::operator/=(const float& s)
{
    this->p.SetX(this->p.GetX() / s);
    this->p.SetY(this->p.GetY() / s);
    this->p.SetZ(this->p.GetZ() / s);
    return *this;
}

