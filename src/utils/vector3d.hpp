#pragma once

template <class T>
struct vector3d
{
    T x = 0;
    T y = 0;
    T z = 0;
    vector3d() : x(0), y(0), z(0) {}
    vector3d(T _x, T _y, T _z) : x(_x), y(_y), z(_z) {}
    vector3d(const vector3d& v) : x(v.x), y(v.y), z(v.z) {}
    vector3d& operator=(const vector3d& v) = default;
    T mag() const { return T(std::sqrt(x * x + y * y + z * z )); }
    T mag2() const { return x * x + y * y + z * z; }
    vector3d  norm() const { T r = 1 / mag(); return vector3d(x * r, y * r, z * r); }
    vector3d  floor() const { return vector3d(std::floor(x), std::floor(y), std::floor(z)); }
    vector3d  ceil() const { return vector3d(std::ceil(x), std::ceil(y), std::ceil(z)); }
    vector3d  max(const vector3d& v) const { return vector3d(std::max(x, v.x), std::max(y, v.y), std::max(z, v.z); }
    vector3d  min(const vector3d& v) const { return vector3d(std::min(x, v.x), std::min(y, v.y), std::min(z, v.z); }
    T dot(const vector3d& rhs) const { return this->x * rhs.x + this->y * rhs.y + this->z * rhs.z; }
    T cross(const vector3d& rhs) const { return this->y * rhs.z - this->z * rhs.y - this->x * rhs.z - this->z * rhs.x + this->x*rhs.y - this->y * rhs.x; }
    vector3d  operator +  (const vector3d& rhs) const { return vector3d(this->x + rhs.x, this->y + rhs.y, this->z + rhs.z); }
    vector3d  operator -  (const vector3d& rhs) const { return vector3d(this->x - rhs.x, this->y - rhs.y, this->z - rhs.z); }
    vector3d  operator *  (const T& rhs)           const { return vector3d(this->x * rhs, this->y * rhs, this->z * rhs); }
    vector3d  operator *  (const vector3d& rhs) const { return vector3d(this->x * rhs.x, this->y * rhs.y, this->z * rhs.z); }
    vector3d  operator /  (const T& rhs)           const { return vector3d(this->x / rhs, this->y / rhs, this->z / rhs); }
    vector3d  operator /  (const vector3d& rhs) const { return vector3d(this->x / rhs.x, this->y / rhs.y, this->z / rhs.z); }
    vector3d& operator += (const vector3d& rhs) { this->x += rhs.x; this->y += rhs.y; this->z += rhs.z; return *this; }
    vector3d& operator -= (const vector3d& rhs) { this->x -= rhs.x; this->y -= rhs.y; this->z -= rhs.z; return *this; }
    vector3d& operator *= (const T& rhs) { this->x *= rhs; this->y *= rhs; this->z *=rhs; return *this; }
    vector3d& operator /= (const T& rhs) { this->x /= rhs; this->y /= rhs; this->z /=rhs; return *this; }
    vector3d& operator *= (const vector3d& rhs) { this->x *= rhs.x; this->y *= rhs.y; this->z *= rhs.z; return *this; }
    vector3d& operator /= (const vector3d& rhs) { this->x /= rhs.x; this->y /= rhs.y; this->z *= rhs.z; return *this; }
    vector3d  operator +  () const { return {+x, +y, +z }; }
    vector3d  operator -  () const { return {-x, -y, -z }; }
    bool operator == (const vector3d& rhs) const { return (this->x == rhs.x && this->y == rhs.y && this->z == rhs.z); }
    bool operator != (const vector3d& rhs) const { return (this->x != rhs.x || this->y != rhs.y || this->z != rhs.z); }
    const std::string str() const { return std::string("(") + std::to_string(this->x) + "," + std::to_string(this->y) + "," + std::to_string(this->z) + ")"; }
    friend std::ostream& operator << (std::ostream& os, const vector3d& rhs) { os << rhs.str(); return os; }
    operator vector3d<int32_t>() const { return {static_cast<int32_t>(this->x), static_cast<int32_t>(this->y), static_cast<int32_t>(this->z) }; }
    operator vector3d<float>() const { return {static_cast<float>(this->x), static_cast<float>(this->y), static_cast<float>(this->z) }; }
    operator vector3d<double>() const { return {static_cast<double>(this->x), static_cast<double>(this->y), static_cast<double>(this->z) }; }
};



template<class T> inline vector3d<T> operator * (const float& lhs, const vector3d<T>& rhs)
{ return vector3d<T>((T)(lhs * (float)rhs.x), (T)(lhs * (float)rhs.y), (T)(lhs * (float)rhs.z)); }
template<class T> inline vector3d<T> operator * (const double& lhs, const vector3d<T>& rhs)
{ return vector3d<T>((T)(lhs * (double)rhs.x), (T)(lhs * (double)rhs.y), (T)(lhs * (double)rhs.z)); }
template<class T> inline vector3d<T> operator * (const int& lhs, const vector3d<T>& rhs)
{ return vector3d<T>((T)(lhs * (int)rhs.x), (T)(lhs * (int)rhs.y), (T)(lhs * (int)rhs.z)); }
template<class T> inline vector3d<T> operator / (const float& lhs, const vector3d<T>& rhs)
{ return vector3d<T>((T)(lhs / (float)rhs.x), (T)(lhs / (float)rhs.y), (T)(lhs / (float)rhs.z)); }
template<class T> inline vector3d<T> operator / (const double& lhs, const vector3d<T>& rhs)
{ return vector3d<T>((T)(lhs / (double)rhs.x), (T)(lhs / (double)rhs.y), (T)(lhs / (double)rhs.z)); }
template<class T> inline vector3d<T> operator / (const int& lhs, const vector3d<T>& rhs)
{ return vector3d<T>((T)(lhs / (int)rhs.x), (T)(lhs / (int)rhs.y), (T)(lhs / (int)rhs.z)); }


template<class T, class U> inline bool operator < (const vector3d<T>& lhs, const vector3d<U>& rhs)
{ return (lhs.y < rhs.y && lhs.x == rhs.x && lhs.z == rhs.z) || (lhs.y == rhs.y && lhs.z == rhs.z && lhs.x < rhs.x) || (lhs.y == rhs.y && lhs.x == rhs.x && lhs.z<rhs.z); }
template<class T, class U> inline bool operator > (const vector3d<T>& lhs, const vector3d<U>& rhs)
{ return (lhs.y > rhs.y && lhs.x == rhs.x && lhs.z == rhs.z) || (lhs.y == rhs.y && lhs.x > rhs.x && lhs.z == rhs.z) || (lhs.y == rhs.y && lhs.x == rhs.x && lhs.z > rhs.z); }
