#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <xmmintrin.h>
namespace TGL 
{
	struct Vector2
	{
		float x;
		float y;

		Vector2() = default;
		Vector2(float x_, float y_) { x = x_; y = y_; }
		Vector2(const Vector2& rhs);
		Vector2& operator==(const Vector2& rhs);

		float Length();
		float LengthSquared();
	};

	struct Vector3
	{
		float x;
		float y;
		float z;

		Vector3() = default;
		Vector3(float x_, float y_, float z_) { x = x_; y = y_; z = z_; }
		Vector3(const Vector3& rhs);
		Vector3& operator==(const Vector3& rhs);

		float Length();
		float LengthSquared();

		static Vector3 Cross(const Vector3& lhs, const Vector3& rhs);
	};

	struct Vector4
	{
		float x;
		float y;
		float z;
		float w;

		Vector4() = default;
		Vector4(float x_, float y_, float z_, float w_) { x = x_; y = y_; z = z_; w = w_; }
		Vector4(const Vector4& rhs);
		Vector4& operator==(const Vector4& rhs);

		float Length();
		float LengthSquared();
	};

	//---------------------------------------------------------------

	Vector2 operator+(const Vector2& lhs, const Vector2& rhs) noexcept;
	Vector2 operator-(const Vector2& lhs, const Vector2& rhs) noexcept;
	Vector2 operator*(const Vector2& lhs, float scalar) noexcept;
	Vector2 operator/(const Vector2& lhs, float scalar) noexcept;

	void operator -= (Vector2& lhs, const Vector2& rhs) noexcept;
	void operator += (Vector2& lhs, const Vector2& rhs) noexcept;
	void operator /= (Vector2& lhs, float scalar) noexcept;
	void operator *= (Vector2& lhs, float scalar) noexcept;

	//---------------------------------------------------------------

	Vector3 operator+(const Vector3& lhs, const Vector3& rhs) noexcept;
	Vector3 operator-(const Vector3& lhs, const Vector3& rhs) noexcept;
	Vector3 operator*(const Vector3& lhs, float scalar) noexcept;
	Vector3 operator/(const Vector3& lhs, float scalar) noexcept;

	void operator -= (Vector3& lhs, const Vector3& rhs) noexcept;
	void operator += (Vector3& lhs, const Vector3& rhs) noexcept;
	void operator /= (Vector3& lhs, float scalar) noexcept;
	void operator *= (Vector3& lhs, float scalar) noexcept;

	//---------------------------------------------------------------

	Vector4 operator+(const Vector4& lhs, const Vector4& rhs) noexcept;
	Vector4 operator-(const Vector4& lhs, const Vector4& rhs) noexcept;
	Vector4 operator*(const Vector4& lhs, float scalar) noexcept;
	Vector4 operator/(const Vector4& lhs, float scalar) noexcept;

	void operator -= (Vector4& lhs, const Vector4& rhs) noexcept;
	void operator += (Vector4& lhs, const Vector4& rhs) noexcept;
	void operator /= (Vector4& lhs, float scalar) noexcept;
	void operator *= (Vector4& lhs, float scalar) noexcept;
}



#endif