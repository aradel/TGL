#include "Vector.hpp"
#include <math.h>
#include <cassert>
namespace TGL
{
	Vector2::Vector2(const Vector2& rhs)
	{
		x = rhs.x;
		y = rhs.y;
	}

	Vector2& Vector2::operator==(const Vector2& rhs)
	{
		x = rhs.x;
		y = rhs.y;

		return *this;
	}

	float Vector2::Length() 
	{
		return sqrtf((x * x) + (y * y));
	}

	float Vector2::LengthSquared() 
	{
		return (x * x) + (y * y);
	}

	Vector2 operator+(const Vector2& lhs, const Vector2& rhs) noexcept
	{
		return Vector2(lhs.x + rhs.x, lhs.y + rhs.y);
	}

	Vector2 operator-(const Vector2& lhs, const Vector2& rhs) noexcept
	{
		return Vector2(lhs.x - rhs.x, lhs.y - rhs.y);
	}

	Vector2 operator*(const Vector2& lhs, const float scalar) noexcept
	{
		return Vector2(lhs.x * scalar, lhs.y * scalar);
	}

	Vector2 operator/(const Vector2& lhs, float scalar) noexcept
	{
		assert(scalar != 0);
		return Vector2(lhs.x / scalar, lhs.y / scalar);
	}

	void operator += (Vector2& lhs, const Vector2& rhs) noexcept
	{
		lhs.x += rhs.x;
		lhs.y += rhs.y;
	}

	void operator -= (Vector2& lhs, const Vector2& rhs) noexcept
	{
		lhs.x -= rhs.x;
		lhs.y -= rhs.y;
	}

	void operator *= (Vector2& lhs, const float scalar) noexcept
	{
		lhs.x *= scalar;
		lhs.y *= scalar;
	}

	void operator /= (Vector2& lhs, const float scalar) noexcept 
	{
		assert(scalar != 0);
		lhs.x /= scalar;
		lhs.y /= scalar;
	}

	//---------------------------------------------------------------

	Vector3::Vector3(const Vector3& rhs) 
	{
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
	}

	Vector3& Vector3::operator==(const Vector3& rhs) 
	{
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
		return *this;
	}

	float Vector3::Length()
	{
		return sqrtf((x * x) + (y * y) + (z * z));
	}

	float Vector3::LengthSquared()
	{
		return (x * x) + (y * y) + (z * z);
	}

	Vector3 operator+(const Vector3& lhs, const Vector3& rhs) noexcept
	{
		return Vector3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
	}

	Vector3 operator-(const Vector3& lhs, const Vector3& rhs) noexcept
	{
		return Vector3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
	}

	Vector3 operator*(const Vector3& lhs, const float scalar) noexcept
	{
		return Vector3(lhs.x * scalar, lhs.y * scalar, lhs.z * scalar);
	}

	Vector3 operator/(const Vector3& lhs, float scalar) noexcept
	{
		assert(scalar != 0);
		return Vector3(lhs.x / scalar, lhs.y / scalar, lhs.z / scalar);
	}

	void operator += (Vector3& lhs, const Vector3& rhs) noexcept
	{
		lhs.x += rhs.x;
		lhs.y += rhs.y;
		lhs.z += rhs.z;
	}

	void operator -= (Vector3& lhs, const Vector3& rhs) noexcept
	{
		lhs.x -= rhs.x;
		lhs.y -= rhs.y;
		lhs.z -= rhs.z;
	}

	void operator *= (Vector3& lhs, const float scalar) noexcept
	{
		lhs.x *= scalar;
		lhs.y *= scalar;
		lhs.z *= scalar;
	}

	void operator /= (Vector3& lhs, const float scalar) noexcept
	{
		assert(scalar != 0);
		lhs.x /= scalar;
		lhs.y /= scalar;
		lhs.z /= scalar;
	}

	Vector3 Vector3::Cross(const Vector3& lhs, const Vector3& rhs) 
	{
		struct NOT_IMPLEMENTED {};
		throw NOT_IMPLEMENTED();
	}

	//---------------------------------------------------------------

	Vector4::Vector4(const Vector4& rhs)
	{
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
	}

	Vector4& Vector4::operator==(const Vector4& rhs)
	{
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
		w = rhs.z;

		return *this;
	}

	float Vector4::Length()
	{
		return sqrtf((x * x) + (y * y) + (z * z) + (w * w));
	}

	float Vector4::LengthSquared()
	{
		return (x * x) + (y * y) + (z * z) + (w * w);
	}

	Vector4 operator+(const Vector4& lhs, const Vector4& rhs) noexcept
	{
		return Vector4(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w);
	}

	Vector4 operator-(const Vector4& lhs, const Vector4& rhs) noexcept
	{
		return Vector4(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w);
	}

	Vector4 operator*(const Vector4& lhs, const float scalar) noexcept
	{
		return Vector4(lhs.x * scalar, lhs.y * scalar, lhs.z * scalar, lhs.w * scalar);
	}

	Vector4 operator/(const Vector4& lhs, float scalar) noexcept
	{
		assert(scalar != 0);
		return Vector4(lhs.x / scalar, lhs.y / scalar, lhs.z / scalar, lhs.w / scalar);
	}

	void operator += (Vector4& lhs, const Vector4& rhs) noexcept
	{
		lhs.x += rhs.x;
		lhs.y += rhs.y;
		lhs.z += rhs.z;
		lhs.w += rhs.w;
	}

	void operator -= (Vector4& lhs, const Vector4& rhs) noexcept
	{
		lhs.x -= rhs.x;
		lhs.y -= rhs.y;
		lhs.z -= rhs.z;
		lhs.w -= rhs.w;
	}

	void operator *= (Vector4& lhs, const float scalar) noexcept
	{
		lhs.x *= scalar;
		lhs.y *= scalar;
		lhs.z *= scalar;
		lhs.w *= scalar;
	}

	void operator /= (Vector4& lhs, const float scalar) noexcept
	{
		assert(scalar != 0);
		lhs.x /= scalar;
		lhs.y /= scalar;
		lhs.z /= scalar;
		lhs.w /= scalar;
	}

}