#pragma once
#include "Vector.h"
using namespace std;

	class Macierz
	{
	public:
		Macierz();//konstruktor bezparametrowy
		Macierz(float value);//konstriktor z 1 parametrem
		Macierz(float matrix[4][4]);//konstruktory przyjmuj�ce tablice dwuwymiarowe 4x4
		Macierz(float matrix[3][3]);//3x3

		Macierz(const Macierz& matrix);//konstruktor kopiuj�cy

		Macierz operator=(const Macierz& matrix);//nadpisanie operator�w
		Macierz operator+(Macierz & matrix);
		Macierz& operator+=(Macierz & matrix);
		Macierz operator-(Macierz & matrix);
		Macierz & operator-=(Macierz & matrix);
		Macierz operator*(float value);
		Macierz& operator*=(float value);
		Macierz operator*(Macierz & matrix);
		Macierz& operator*=(Macierz & matrix);
		Wektor operator*(Wektor  & vector);
		friend std::ostream & operator<<(std::ostream & out, const Macierz & matrix);

		float getElement(int row, int column);//ustawienie i zwr�cenie elementu macierzy
		void setElement(int row, int column, float value);

		float* getRow(int row);//uzyskanie pojedy�czego rz�du macierzy

		void identity();//macierz jednostkowa

		void transpose();//transpozycja macierzy

		float det3D();//wyliczanie wyznacznika
		float det4D();

		Macierz cofactor3D();//tworzenie macierzy dope�nie�
		Macierz cofactor4D();

		void inverse4D();//obliczanie macierzy odwr�conej
		void inverse3D();

	protected:
		float m_values[4][4];
	};

