#include <iostream>
#include <xmmintrin.h>

struct alignas(16) Matrix
{
	float m[16];
};

Matrix mul(const Matrix& lhs, const Matrix& rhs)
{
	Matrix local_return;

	__m128 a[4];
	__m128 b[4];

	a[0] = _mm_load_ps(&lhs.m[0]);
	a[1] = _mm_load_ps(&lhs.m[4]);
	a[2] = _mm_load_ps(&lhs.m[8]);
	a[3] = _mm_load_ps(&lhs.m[12]);

	b[0] = _mm_load_ps(&rhs.m[0]);
	b[1] = _mm_load_ps(&rhs.m[4]);
	b[2] = _mm_load_ps(&rhs.m[8]);
	b[3] = _mm_load_ps(&rhs.m[12]);

	for (size_t i = 0; i < 4; i++)
	{
		__m128 op0 = _mm_shuffle_ps(a[i], a[i], _MM_SHUFFLE(0, 0, 0, 0)); // SplatX
		__m128 op1 = _mm_shuffle_ps(a[i], a[i], _MM_SHUFFLE(1, 1, 1, 1)); // SplatY
		__m128 op2 = _mm_shuffle_ps(a[i], a[i], _MM_SHUFFLE(2, 2, 2, 2)); // SplatZ
		__m128 op3 = _mm_shuffle_ps(a[i], a[i], _MM_SHUFFLE(3, 3, 3, 3)); // SplatW

		op0 = _mm_mul_ps(op0, b[0]);
		op1 = _mm_mul_ps(op1, b[1]);
		op2 = _mm_mul_ps(op2, b[2]);
		op3 = _mm_mul_ps(op3, b[3]);

		__m128 row = _mm_add_ps(_mm_add_ps(op0, op1), _mm_add_ps(op2, op3));

		_mm_store_ps(&local_return.m[i * 4], row);
	}

	return local_return;
}
