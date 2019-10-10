#include "Vector2D.h"

Vector2D::Vector2D() : x(0), y(0)
{
}

Vector2D::Vector2D(float xpos, float ypos) : x(xpos), y(ypos)
{
}

Vector2D& Vector2D::Add(const Vector2D& vec)
{
	this->x += vec.x;
	this->y += vec.y;

	return *this;
}

Vector2D& Vector2D::Subtract(const Vector2D& vec)
{
	this->x -= vec.x;
	this->y -= vec.y;

	return *this;
}

Vector2D& Vector2D::normalize()
{
	float magn = mag();
	if (magn > 0)
	{
		(*this) /= magn;
	}
	return *this;
}

float Vector2D::mag()
{
	return sqrt(magSqr());
}

float Vector2D::magSqr()
{
	return ((this->x * this->x) + (this->y * this->y));
}

Vector2D& Vector2D::operator+=(const Vector2D& vec)
{
	return this->Add(vec);
}

Vector2D& Vector2D::operator-=(const Vector2D& vec)
{
	return this->Subtract(vec);
}

Vector2D& Vector2D::operator*=(const float val)
{
	this->x *= val;
	this->y *= val;
	return *this;
}

Vector2D& Vector2D::operator/=(const float val)
{
	this->x /= val;
	this->y /= val;
	return *this;
}

Vector2D& operator+(Vector2D& v1, const Vector2D& v2)
{
	return v1.Add(v2);
}

Vector2D& operator-(Vector2D& v1, const Vector2D& v2)
{
	return v1.Subtract(v2);
}

Vector2D operator*(Vector2D& v1, const float val)
{
	Vector2D mult(v1.x * val, v1.y * val);
	return mult;
}

Vector2D operator/(Vector2D& v1, const float val)
{
	Vector2D divide(v1.x / val, v1.y / val);
	return divide;
}

std::ostream& operator<<(std::ostream& stream, const Vector2D& vec)
{
	stream << "(" << vec.x << ", " << vec.y << ")";
	return stream;
}
