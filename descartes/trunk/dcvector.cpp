#include "dcvector.h"



DCVector::DCVector(const mm& x, const mm& y, const mm& z)
    : Point(x,y,z)
{}


DCVector::DCVector(Point p_arg)
	: Point(p_arg)
{}


DCVector::DCVector(Point origin_arg, Point destination_arg)
    : Point(destination_arg.GetX() - origin_arg.GetX(), destination_arg.GetY() - origin_arg.GetY(), destination_arg.GetZ() - origin_arg.GetZ())
{}


DCVector::DCVector(LineSegment line_arg)
    : Point(line_arg.GetB().GetX() - line_arg.GetA().GetX(), line_arg.GetB().GetY() - line_arg.GetA().GetY(), line_arg.GetB().GetZ() - line_arg.GetA().GetZ())
{}


mm DCVector::Magnitude() const
{
    /*
    FUNDAMENTAL_NUMERIC_TYPE a = GetX().GetValue();
    FUNDAMENTAL_NUMERIC_TYPE b = GetY().GetValue();
    FUNDAMENTAL_NUMERIC_TYPE c = GetZ().GetValue();
    */
    return sqrt(GetX()*GetX() + GetY()*GetY() + GetZ()*GetZ());
}


mm2 DCVector::Dot(const DCVector& v) const
{
	return GetX() * v.GetX() + GetY() * v.GetY() + GetZ() * v.GetZ();
}


degrees DCVector::AngleBetween(DCVector v) const
{
    return degrees(acos(this->Dot(v) / (this->Magnitude() * v.Magnitude())));
}


DCVector DCVector::operator*(const float& s) const
{
	DCVector temp(*this);
	temp.SetX(temp.GetX() * s);
    temp.SetY(temp.GetY() * s);
    temp.SetZ(temp.GetZ() * s);
    return temp;
}


DCVector DCVector::operator*=(const float& s)
{
	this->SetX(this->GetX() * s);
    this->SetY(this->GetY() * s);
    this->SetZ(this->GetZ() * s);
    return *this;
}


DCVector DCVector::operator/(const float& s) const
{
	DCVector temp(*this);
	temp.SetX(temp.GetX() / s);
    temp.SetY(temp.GetY() / s);
    temp.SetZ(temp.GetZ() / s);
    return temp;
}


DCVector DCVector::operator/=(const float& s)
{
    this->SetX(this->GetX() / s);
    this->SetY(this->GetY() / s);
    this->SetZ(this->GetZ() / s);
    return *this;
}


LRO DCVector::LeftRightOrOn(Point theta) const
{
    // (Bx - Ax) * (Cy - Ay) - (By - Ay) * (Cx - Ax)
    // (Bx - 0) * (Cy - 0) - (By - 0) * (Cx - 0)
    // Bx * Cy - By * Cx
    mm2 val = GetX() * theta.GetY() - GetY() * theta.GetX();
    if (val == 0.0f)
        return ON;
    else if (val < 0.0f)
        return RIGHT;
    else
        return LEFT;
}
