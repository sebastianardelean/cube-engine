#pragma once
#include "cube.hpp"
template <class T>
struct vector2d
{
    T x = 0;
    T y = 0;
    vector2d() : x(0), y(0) {}
    vector2d(T _x, T _y) : x(_x), y(_y) {}
    vector2d(const vector2d& v) : x(v.x), y(v.y) {}
    vector2d& operator=(const vector2d& v) = default;
    T mag() const { return T(std::sqrt(x * x + y * y)); }
    T mag2() const { return x * x + y * y; }
    vector2d  norm() const { T r = 1 / mag(); return vector2d(x * r, y * r); }
    vector2d  perp() const { return vector2d(-y, x); }
    vector2d  floor() const { return vector2d(std::floor(x), std::floor(y)); }
    vector2d  ceil() const { return vector2d(std::ceil(x), std::ceil(y)); }
    vector2d  max(const vector2d& v) const { return vector2d(std::max(x, v.x), std::max(y, v.y)); }
    vector2d  min(const vector2d& v) const { return vector2d(std::min(x, v.x), std::min(y, v.y)); }
    vector2d  cart() { return {std::cos(y) * x, std::sin(y) * x }; }
    vector2d  polar() { return {mag(), std::atan2(y, x) }; }
    T dot(const vector2d& rhs) const { return this->x * rhs.x + this->y * rhs.y; }
    T cross(const vector2d& rhs) const { return this->x * rhs.y - this->y * rhs.x; }
    vector2d  operator +  (const vector2d& rhs) const { return vector2d(this->x + rhs.x, this->y + rhs.y); }
    vector2d  operator -  (const vector2d& rhs) const { return vector2d(this->x - rhs.x, this->y - rhs.y); }
    vector2d  operator *  (const T& rhs)           const { return vector2d(this->x * rhs, this->y * rhs); }
    vector2d  operator *  (const vector2d& rhs) const { return vector2d(this->x * rhs.x, this->y * rhs.y); }
    vector2d  operator /  (const T& rhs)           const { return vector2d(this->x / rhs, this->y / rhs); }
    vector2d  operator /  (const vector2d& rhs) const { return vector2d(this->x / rhs.x, this->y / rhs.y); }
    vector2d& operator += (const vector2d& rhs) { this->x += rhs.x; this->y += rhs.y; return *this; }
    vector2d& operator -= (const vector2d& rhs) { this->x -= rhs.x; this->y -= rhs.y; return *this; }
    vector2d& operator *= (const T& rhs) { this->x *= rhs; this->y *= rhs; return *this; }
    vector2d& operator /= (const T& rhs) { this->x /= rhs; this->y /= rhs; return *this; }
    vector2d& operator *= (const vector2d& rhs) { this->x *= rhs.x; this->y *= rhs.y; return *this; }
    vector2d& operator /= (const vector2d& rhs) { this->x /= rhs.x; this->y /= rhs.y; return *this; }
    vector2d  operator +  () const { return {+x, +y }; }
    vector2d  operator -  () const { return {-x, -y }; }
    bool operator == (const vector2d& rhs) const { return (this->x == rhs.x && this->y == rhs.y); }
    bool operator != (const vector2d& rhs) const { return (this->x != rhs.x || this->y != rhs.y); }
    const std::string str() const { return std::string("(") + std::to_string(this->x) + "," + std::to_string(this->y) + ")"; }
    friend std::ostream& operator << (std::ostream& os, const vector2d& rhs) { os << rhs.str(); return os; }
    operator vector2d<int32_t>() const { return {static_cast<int32_t>(this->x), static_cast<int32_t>(this->y) }; }
    operator vector2d<float>() const { return {static_cast<float>(this->x), static_cast<float>(this->y) }; }
    operator vector2d<double>() const { return {static_cast<double>(this->x), static_cast<double>(this->y) }; }
};



template<class T> inline vector2d<T> operator * (const float& lhs, const vector2d<T>& rhs)
{ return vector2d<T>((T)(lhs * (float)rhs.x), (T)(lhs * (float)rhs.y)); }
template<class T> inline vector2d<T> operator * (const double& lhs, const vector2d<T>& rhs)
{ return vector2d<T>((T)(lhs * (double)rhs.x), (T)(lhs * (double)rhs.y)); }
template<class T> inline vector2d<T> operator * (const int& lhs, const vector2d<T>& rhs)
{ return vector2d<T>((T)(lhs * (int)rhs.x), (T)(lhs * (int)rhs.y)); }
template<class T> inline vector2d<T> operator / (const float& lhs, const vector2d<T>& rhs)
{ return vector2d<T>((T)(lhs / (float)rhs.x), (T)(lhs / (float)rhs.y)); }
template<class T> inline vector2d<T> operator / (const double& lhs, const vector2d<T>& rhs)
{ return vector2d<T>((T)(lhs / (double)rhs.x), (T)(lhs / (double)rhs.y)); }
template<class T> inline vector2d<T> operator / (const int& lhs, const vector2d<T>& rhs)
{ return vector2d<T>((T)(lhs / (int)rhs.x), (T)(lhs / (int)rhs.y)); }


template<class T, class U> inline bool operator < (const vector2d<T>& lhs, const vector2d<U>& rhs)
{ return lhs.y < rhs.y || (lhs.y == rhs.y && lhs.x < rhs.x); }
template<class T, class U> inline bool operator > (const vector2d<T>& lhs, const vector2d<U>& rhs)
{ return lhs.y > rhs.y || (lhs.y == rhs.y && lhs.x > rhs.x); }