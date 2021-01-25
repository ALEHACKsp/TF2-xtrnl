#pragma once
#include <math.h>

#define M_RADPI		57.295779513082
#define PI			3.14159265358979323846
#define FLT_EPSILON 1.192092896e-07F
#define DEG2RAD(x)	((float)(x) * (float)((float)(PI) / 180.0f))
#define RAD2DEG(x)	((float)(x) * (float)(180.0f / (float)(PI)))

class Vector
{
public:
	float x, y, z;

public:
	Vector(void)
	{
		x = y = z = 0.0f;
	}

	void Zero()
	{
		x = y = z = 0.f;
	}

	Vector(float X, float Y, float Z)
	{
		x = X; y = Y; z = Z;
	}

	Vector(float *v)
	{
		x = v[0]; y = v[1]; z = v[2];
	}

	Vector(const float *v)
	{
		x = v[0]; y = v[1]; z = v[2];
	}

	Vector(const Vector &v)
	{
		x = v.x; y = v.y; z = v.z;
	}

	Vector &operator=(const Vector &v)
	{
		x = v.x; y = v.y; z = v.z; return *this;
	}

	float &operator[](int i)
	{
		return ((float *)this)[i];
	}

	float operator[](int i) const
	{
		return ((float *)this)[i];
	}

	Vector &operator+=(const Vector &v)
	{
		x += v.x; y += v.y; z += v.z; return *this;
	}

	Vector &operator-=(const Vector &v)
	{
		x -= v.x; y -= v.y; z -= v.z; return *this;
	}

	Vector &operator*=(const Vector &v)
	{
		x *= v.x; y *= v.y; z *= v.z; return *this;
	}

	Vector &operator/=(const Vector &v)
	{
		x /= v.x; y /= v.y; z /= v.z; return *this;
	}

	Vector &operator+=(float v)
	{
		x += v; y += v; z += v; return *this;
	}

	Vector &operator-=(float v)
	{
		x -= v; y -= v; z -= v; return *this;
	}

	Vector &operator*=(float v)
	{
		x *= v; y *= v; z *= v; return *this;
	}

	Vector &operator/=(float v)
	{
		x /= v; y /= v; z /= v; return *this;
	}

	Vector operator+(const Vector &v) const
	{
		return Vector(x + v.x, y + v.y, z + v.z);
	}

	Vector operator-(const Vector &v) const
	{
		return Vector(x - v.x, y - v.y, z - v.z);
	}

	Vector operator*(const Vector &v) const
	{
		return Vector(x * v.x, y * v.y, z * v.z);
	}

	Vector operator/(const Vector &v) const
	{
		return Vector(x / v.x, y / v.y, z / v.z);
	}

	Vector operator+(float v) const
	{
		return Vector(x + v, y + v, z + v);
	}

	Vector operator-(float v) const
	{
		return Vector(x - v, y - v, z - v);
	}

	Vector operator*(float v) const
	{
		return Vector(x * v, y * v, z * v);
	}

	Vector operator/(float v) const
	{
		return Vector(x / v, y / v, z / v);
	}

	void Set(float X = 0.0f, float Y = 0.0f, float Z = 0.0f)
	{
		x = X; y = Y; z = Z;
	}

	float Lenght(void) const
	{
		return sqrtf(x * x + y * y + z * z);
	}

	float LenghtSqr(void) const
	{
		return (x * x + y * y + z * z);
	}

	float Normalize()
	{
		float fl_lenght = Lenght();
		float fl_lenght_normal = 1.f / (FLT_EPSILON + fl_lenght);

		x = x * fl_lenght_normal;
		y = y * fl_lenght_normal;
		z = z * fl_lenght_normal;

		return fl_lenght;
	}

	void Rotate2D(const float &flYaw)
	{
		float s, c, r = DEG2RAD(flYaw);
		s = sin(r); c = cos(r);

		float _x = x, _y = y;

		x = (_x * c) - (_y * s);
		y = (_x * s) + (_y * c);
	}

	float NormalizeInPlace()
	{
		return Normalize();
	}

	float Lenght2D(void) const
	{
		return sqrtf(x * x + y * y);
	}

	float Lenght2DSqr(void) const
	{
		return (x * x + y * y);
	}

	float DistTo(const Vector &v) const
	{
		return (*this - v).Lenght();
	}

	float DistToSqr(const Vector &v) const
	{
		return (*this - v).LenghtSqr();
	}

	float Dot(const Vector &v) const
	{
		return (x * v.x + y * v.y + z * v.z);
	}

	Vector Cross(const Vector &v) const
	{
		return Vector(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
	}

	bool IsZero(void) const
	{
		return (x > -0.01f && x < 0.01f &&
			y > -0.01f && y < 0.01f &&
			z > -0.01f && z < 0.01f);
	}

	Vector Scale(float fl) {
		return Vector(x * fl, y * fl, z * fl);
	}

	void Init(float ix, float iy, float iz)
	{
		x = ix; y = iy; z = iz;
	}
};