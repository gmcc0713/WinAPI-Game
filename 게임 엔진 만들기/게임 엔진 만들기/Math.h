#include <cmath>

#ifndef ENGINE_MATH_H
#define ENGINE_MATH_H

namespace ENGINE
{
	struct Vector2
	{
		float x, y;

		Vector2() : x(0), y(0) {}
		Vector2(float x, float y) : x(x), y(y) {}

		Vector2 operator-() const { return Vector2(-x, -y); }

		Vector2 operator*(const float& value) const { return Vector2(x*value,y*value); }
		Vector2 operator/(const float& value) const { return Vector2(x / value, y / value); }
		Vector2 operator*=(const float& value) { return Vector2(x *= value, y *= value); }
		Vector2 operator/=(const float& value) { return Vector2(x /= value, y /= value); }

		Vector2 operator+(const Vector2& v) const { return Vector2(x + v.x, y + v.y); }
		Vector2 operator-(const Vector2& v) const { return Vector2(x - v.x, y - v.y); }
		Vector2 operator+=(const Vector2& v) { return Vector2(x += v.x, y += v.y); }
		Vector2 operator-=(const Vector2& v) { return Vector2(x -= v.x, y -= v.y); }

	};

	inline bool operator== (const Vector2& lhs, const Vector2& rhs) { return lhs.x == rhs.x && lhs.y == rhs.y; }
	inline bool operator!= (const Vector2& lhs, const Vector2& rhs) { return !(lhs == rhs); }

	const float Epsilon = 0.0001f;

	inline bool Equal(float lhs, float rhs) { return (std::abs(lhs - rhs) <= Epsilon); }

#ifndef clamp
#define clamp(v, a, b) (a < b) ? min(max(v, a), b) : min(max(v, b), a)
#endif // !clamp

	int Repeat(int value, const int& max);
}

#endif // !ENGINE_MATH_H