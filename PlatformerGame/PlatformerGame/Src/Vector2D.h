#pragma once
#include <iostream>

struct Vector2D
{
	Vector2D();
	Vector2D(float xpos, float ypos);

	Vector2D& Add(const Vector2D& vec);
	Vector2D& Subtract(const Vector2D& vec);

	Vector2D& normalize();
	float mag();
	float magSqr();

	friend Vector2D& operator+(Vector2D& v1, const Vector2D& v2);
	friend Vector2D& operator-(Vector2D& v1, const Vector2D& v2);
	friend Vector2D operator*(Vector2D& v1, const float val);
	friend Vector2D operator/(Vector2D& v1, const float val);

	Vector2D& operator+=(const Vector2D& vec);
	Vector2D& operator-=(const Vector2D& vec);
	Vector2D& operator*=(const float val);
	Vector2D& operator/=(const float val);

	friend std::ostream& operator<<(std::ostream& stream, const Vector2D& vec);

	float x;
	float y;
};

