#pragma once

namespace vector
{
    template <class T> class Vector2D;
    using vector2Di_t = Vector2D<int32_t>;
    using vector2Du_t = Vector2D<uint32_t>;
    using vector2Df_t = Vector2D<float>;
    using vector2Dd_t = Vector2D<double>;
};


template <class T>
class vector::Vector2D
{
public:
	Vector2D() :x(0), y(0) {}
	Vector2D(T _x, T _y) : x(_x), y(_y) {}
	Vector2D(const Vector2D& v) : x(v.X()), y(v.Y()) {}
	Vector2D& operator= (const Vector2D& v) = default;

	T Magnitude() const { return T(std::sqrt(x * x + y * y)); }

	T Magnitude2() const{ return x * x + y * y; }

	Vector2D Normalized() const {
		T r = 1 / Magnitude(); return Vector2D(x * r, y * r);
	}

	T Dot(const Vector2D& rhs) const {
		return this->x * rhs.x + this->y * rhs.y;
	}
	T cross(const Vector2D& rhs) const {return this->x * rhs.y - this->y * rhs.x; }

	Vector2D  operator +  (const Vector2D& rhs) const { return Vector2D(this->x + rhs.x, this->y + rhs.y); }
	Vector2D  operator -  (const Vector2D& rhs) const { return Vector2D(this->x - rhs.x, this->y - rhs.y); }
	Vector2D  operator *  (const T& rhs)           const { return Vector2D(this->x * rhs, this->y * rhs); }
	Vector2D  operator /  (const T& rhs)           const { return Vector2D(this->x / rhs, this->y / rhs); }
	void X(T x) { this->x = x; }
	void Y(T y) { this->y = y; }
	T X() const { return x; }
	T Y() const { return y; }

	Vector2D& operator += (const Vector2D& rhs) { this->x += rhs.x; this->y += rhs.y; return *this; }
	Vector2D& operator -= (const Vector2D& rhs) { this->x -= rhs.x; this->y -= rhs.y; return *this; }
	Vector2D& operator *= (const T& rhs) { this->x *= rhs; this->y *= rhs; return *this; }
	Vector2D& operator /= (const T& rhs) { this->x /= rhs; this->y /= rhs; return *this; }

	bool operator == (const Vector2D& rhs) const { return (this->x == rhs.x && this->y == rhs.y); }
	bool operator != (const Vector2D& rhs) const { return (this->x != rhs.x || this->y != rhs.y); }

	const std::string str() const { return std::string("(") + std::to_string(this->x) + "," + std::to_string(this->y) + ")"; }
	friend std::ostream& operator << (std::ostream& os, const Vector2D& rhs) { os << rhs.str(); return os; }


	operator Vector2D<uint32_t>() const { return { static_cast<uint32_t>(this->x), static_cast<uint32_t>(this->y) }; }
	operator Vector2D<int32_t>() const { return { static_cast<int32_t>(this->x), static_cast<int32_t>(this->y) }; }
	operator Vector2D<float>() const { return { static_cast<float>(this->x), static_cast<float>(this->y) }; }
	operator Vector2D<double>() const { return { static_cast<double>(this->x), static_cast<double>(this->y) }; }

private:
	T x;
	T y;
};
