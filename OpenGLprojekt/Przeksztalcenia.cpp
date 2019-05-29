#include "Przeksztalcenia.h"
using namespace std;

	const float Przeksztalcenia::M_PI = 3.1415927f;
	Macierz Przeksztalcenia::createScaleMatrix3D(float value)
	{
		Macierz matrix;
		matrix.identity();
		matrix.setElement(0, 0, value);
		matrix.setElement(1, 1, value);
		return matrix;
	}

	Macierz Przeksztalcenia::createScaleMatrix3D(float xValue, float yValue)

	{
		Macierz matrix;
		matrix.identity();
		matrix.setElement(0, 0, xValue);
		matrix.setElement(1, 1, yValue);
		return matrix;
	}

	Macierz Przeksztalcenia::createScaleMatrix3D(float * values)
	{
		Macierz matrix;
		matrix.identity();
		for (int i = 0; i < 2; i++)
		{
			matrix.setElement(i, i, values[i]);
		}
		return matrix;
	}

	Macierz Przeksztalcenia::createTranslateMatrix3D(float value)
	{
		Macierz matrix;
		matrix.identity();
		matrix.setElement(0, 2, value);
		matrix.setElement(1, 2, value);
		matrix.setElement(2, 2, matrix.getElement(2, 2));
		return matrix;
	}

	Macierz Przeksztalcenia::createTranslateMatrix3D(float xValue, float yValue)
	{
		Macierz matrix;
		matrix.identity();
		matrix.setElement(0, 2, xValue);
		matrix.setElement(1, 2, yValue);
		matrix.setElement(2, 2, matrix.getElement(2, 2));
		return matrix;
	}

	Macierz Przeksztalcenia::createTranslateMatrix3D(float * values)
	{
		Macierz matrix;
		matrix.identity();
		for (int i = 0; i < 2; i++)
		{
			matrix.setElement(i, 2, values[i]);
		}
		matrix.setElement(2, 2, matrix.getElement(2, 2));
		return matrix;
	}

	Macierz Przeksztalcenia::rotate3D(float angle)
	{
		Macierz matrix;
		matrix.identity();
		float radians = naRadiany(angle);
		matrix.setElement(0, 0, cos(radians));
		matrix.setElement(0, 1, -sin(radians));
		matrix.setElement(1, 0, sin(radians));
		matrix.setElement(1, 1, cos(radians));
		return matrix;
	}

	Macierz Przeksztalcenia::createScaleMatrix4D(float value)
	{
		Macierz matrix;
		matrix.identity();
		matrix.setElement(0, 0, value);
		matrix.setElement(1, 1, value);
		matrix.setElement(2, 2, value);
		matrix.setElement(3, 3, matrix.getElement(3, 3));
		return matrix;
	}

	Macierz Przeksztalcenia::createScaleMatrix4D(float xValue, float yValue, float zValue)
	{
		Macierz matrix;
		matrix.identity();
		matrix.setElement(0, 0, xValue);
		matrix.setElement(1, 1, yValue);
		matrix.setElement(2, 2, zValue);
		matrix.setElement(3, 3, matrix.getElement(3, 3));
		return matrix;
	}

	Macierz Przeksztalcenia::createScaleMatrix4D(float * values)
	{
		Macierz matrix;
		matrix.identity();
		for (int i = 0; i < 3; i++)
		{
			matrix.setElement(i, i, values[i]);
		}
		matrix.setElement(3, 3, matrix.getElement(3, 3));
		return matrix;
	}

	Macierz Przeksztalcenia::createTranslateMatrix4D(float value)
	{
		Macierz matrix;
		matrix.identity();
		matrix.setElement(0, 3, -value);
		matrix.setElement(1, 3, value);
		matrix.setElement(2, 3, value);
		matrix.setElement(3, 3, matrix.getElement(3, 3));
		return matrix;
	}

	Macierz Przeksztalcenia::createTranslateMatrix4D(float xValue, float yValue, float zValue)
	{
		Macierz matrix;
		matrix.identity();
		matrix.setElement(0, 3, -xValue);
		matrix.setElement(1, 3, yValue);
		matrix.setElement(2, 3, zValue);
		matrix.setElement(3, 3, matrix.getElement(3, 3));
		return matrix;
	}

	Macierz Przeksztalcenia::createTranslateMatrix4D(float * values)
	{
		Macierz matrix;
		matrix.identity();
		for (int i = 0; i < 3; i++)
		{
			matrix.setElement(i, 3, values[i]);
		}
		matrix.setElement(0, 3, -values[0]);
		matrix.setElement(3, 3, matrix.getElement(3, 3));
		return matrix;
	}
	Macierz Przeksztalcenia::rotateX(float angle)
	{
		Macierz matrix;
		matrix.identity();
		float radians = naRadiany(angle);
		matrix.setElement(1, 1, cos(radians));
		matrix.setElement(1, 2, -sin(radians));
		matrix.setElement(2, 1, sin(radians));
		matrix.setElement(2, 2, cos(radians));
		return matrix;
	}
	Macierz Przeksztalcenia::rotateY(float angle)
	{
		Macierz matrix;
		matrix.identity();
		float radians = naRadiany(angle);
		matrix.setElement(0, 0, cos(radians));
		matrix.setElement(0, 2, sin(radians));
		matrix.setElement(2, 0, -sin(radians));
		matrix.setElement(2, 2, cos(radians));
		return matrix;
	}
	Macierz Przeksztalcenia::rotateZ(float angle)
	{
		Macierz matrix;
		matrix.identity();
		float radians = naRadiany(angle);
		matrix.setElement(0, 0, cos(radians));
		matrix.setElement(0, 1, -sin(radians));
		matrix.setElement(1, 0, sin(radians));
		matrix.setElement(1, 1, cos(radians));
		return matrix;
	}

	Macierz Przeksztalcenia::lookAt(Wektor camera, Wektor center, Wektor up)
	{
		Macierz matrix;
		matrix.identity();
		Wektor l_camera = camera;
		Wektor l_center = center;
		Wektor l_up = up;

		Wektor forward = center;
		forward.normalize3D();

		Wektor right = forward.crossProduct(l_up);
		right.normalize3D();

		l_up = right.crossProduct(forward);

		for (int i = 0; i < 3; i++)
		{
			matrix.setElement(0, i, right[i]);
			matrix.setElement(1, i, l_up[i]);
			matrix.setElement(2, i, -forward[i]);
		}

		matrix.setElement(0, 3, right.dotProduct3D(l_camera));
		matrix.setElement(1, 3, l_up.dotProduct3D(l_camera));
		matrix.setElement(2, 3, -forward.dotProduct3D(l_camera));
		matrix.setElement(3, 3, 1.0f);

		return matrix;
	}

	Macierz Przeksztalcenia::createProjectionMatrix(const float fovy, const float aspect, const float near, const float far)
	{
		const float scale = 1.0f / tan(fovy * 0.5 * M_PI / 180);

		Macierz matrix;
		matrix.identity();

		matrix.setElement(0, 0, scale);
		matrix.setElement(1, 1, scale);
		matrix.setElement(2, 2, -far/ (far - near));
		matrix.setElement(3, 2, -1.0f);
		matrix.setElement(2, 3, -far * near / (far - near));

		return matrix;
	}

	float Przeksztalcenia::naStopnie(float rad)
	{
		return rad * 180.0 / M_PI;
	}

	float Przeksztalcenia::naRadiany(float stopnie)
	{
		return stopnie * M_PI / 180.0;
	}
