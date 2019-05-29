#pragma once
#include "Macierz.h"


	class Przeksztalcenia
	{
		public:
			static Macierz createScaleMatrix3D(float value);//metody generuj¹ce macierz skalowania 3x3
			static Macierz createScaleMatrix3D(float xValue, float yValue);
			static Macierz createScaleMatrix3D(float * values);
			static Macierz rotate3D(float angle);//macierz obrotu na podstawie k¹ta
			static Macierz createTranslateMatrix3D(float value);//metody generuj¹ce macierz przesuniêcia 3x3
			static Macierz createTranslateMatrix3D(float xValue, float yValue);
			static Macierz createTranslateMatrix3D(float * values);
			static Macierz createScaleMatrix4D(float value);//metody generuj¹ce macierz skalowania 4x4
			static Macierz createScaleMatrix4D(float xValue, float yValue, float zValue);
			static Macierz createScaleMatrix4D(float * values);
			static Macierz createTranslateMatrix4D(float value);//metody generuj¹ce macierz przesuniêcia 4x4
			static Macierz createTranslateMatrix4D(float xValue, float yValue, float zValue);
			static Macierz createTranslateMatrix4D(float * values);
			static Macierz rotateX(float angle);//metody obrotu macierzy
			static Macierz rotateY(float angle);
			static Macierz rotateZ(float angle);
			static Macierz createProjectionMatrix(const float fovy, const float aspect, const float near, const float far);//macierz perspektywy
			static Macierz lookAt(Wektor camera, Wektor center, Wektor up);//macierz kamery
			static float naStopnie(float rad);//metody zamieniaj¹ce k¹ty i radiany
			static float naRadiany(float stopnie);

		private:
			Macierz m_matrix;
			static const float M_PI;
	};

