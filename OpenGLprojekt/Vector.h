#pragma once
#include <iostream>
#include <math.h>
#include <type_traits>


class Wektor
{
public:
	Wektor();//Konsyruktor bezparametrowe
	Wektor(float value);//Konstruktor z jedny parametrem
	Wektor(float x, float y, float z);//Konstruktor z 3 parametrami
	Wektor(float x, float y, float z, float w);//Konstruktor z 4 parametrami
	Wektor(float* tab);//Konstruktor z tablic�

	Wektor(const Wektor& vec);//Konstruktor kopiuj�cy

	Wektor operator+(Wektor& vec);//nadpisanie operator�w
	Wektor& operator+=(Wektor& vec);
	Wektor operator-(Wektor& vec);
	Wektor& operator-=(Wektor& vec);
	Wektor operator*(float scalar);
	Wektor& operator*=(float scalar);
	Wektor& operator=(const Wektor& vec);
	friend std::ostream& operator<<(std::ostream& out, const Wektor& vec);

	float& operator[](int index);

	float length3D();//d�ugo�� wektora
	float length4D();

	float dotProduct3D(Wektor& vec);//iloczyn skalarny
	float dotProduct4D(Wektor& vec);

	void normalize3D();//normalizacja wektora
	void normalize4D();

	Wektor crossProduct(Wektor & vec);//iloczyn wektorowy
		
	float getX();//Zwracanie parametr�w
	float getY();
	float getZ();
	float getW();
	void setX(float x);//ustawianie parametr�w
	void setY(float y);
	void setZ(float z);
	void setW(float w);

protected:
	float values[4];
};