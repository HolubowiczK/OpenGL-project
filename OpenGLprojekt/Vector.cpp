#include "Vector.h"

Wektor::Wektor()
{
	for (int i = 0; i < 4; i++)
	{
		values[i] = 0.0f;
	}
}

Wektor::Wektor(float value)
{
	for (int i = 0; i < 4; i++)
	{
		values[i] = value;
	}
}

Wektor::Wektor(float x, float y, float z)
{
	values[0] = x;
	values[1] = y;
	values[2] = z;
	values[3] = 1.0f;
}

Wektor::Wektor(float x, float y, float z, float w)
{
	values[0] = x;
	values[1] = y;
	values[2] = z;
	values[3] = w;
}

Wektor::Wektor(float * tab)
{
	for (int i = 0; i < 4; i++)
	{
		values[i] = tab[i];
	}
}

float Wektor::getX()
{
	return values[0];
}

float Wektor::getY()
{
	return values[1];
}

float Wektor::getZ()
{
	return values[2];
}

float Wektor::getW()
{
	return values[3];
}

void Wektor::setX(float x)
{
	values[0] = x;
}

void Wektor::setY(float y)
{
	values[1] = y;
}

void Wektor::setZ(float z)
{
	values[2] = z;
}

void Wektor::setW(float w)
{
	values[3] = w;
}


Wektor::Wektor(const Wektor & vec)
{
	for (int i = 0; i < 4; i++)
	{
		values[i] = vec.values[i];
	}
}


Wektor Wektor::operator+(Wektor & vec)
{
	Wektor l_vec;
	for (int i = 0; i < 4; i++)
	{
		l_vec.values[i] = values[i] + vec[i];
	}
	l_vec.values[3] = 1.0f;
	return l_vec;
}

Wektor & Wektor::operator-=(Wektor & vec)
{
	for (int i = 0; i < 4; i++)
	{
		values[i] -= vec[i];
	}
	values[3] = 1.0f;
	return *this;
}

Wektor Wektor::operator-(Wektor & vec)
{
	Wektor l_vec;
	for (int i = 0; i < 4; i++)
	{
		l_vec.values[i] = values[i] - vec[i];
	}
	l_vec.values[3] = 1.0f;
	return l_vec;
}

Wektor & Wektor::operator+=(Wektor & vec)
{
	for (int i = 0; i < 4; i++)
	{
		values[i] += vec[i];
	}
	values[3] = 1.0f;
	return *this;
}

Wektor Wektor::operator*(float scalar)
{
	Wektor l_vec;
	for (int i = 0; i < 3; i++)
	{
		l_vec.values[i] = this->values[i] * scalar;
	}
	l_vec.values[3] = 1.0f;
	return l_vec;
}

Wektor & Wektor::operator*=(float scalar)
{
	for (int i = 0; i < 4; i++)
	{
		values[i] *= scalar;
	}
	values[3] = 1.0f;
	return *this;
}

Wektor& Wektor::operator=(const Wektor & vec)
{
	for (int i = 0; i < 4; i++)
	{
		values[i] = vec.values[i];
	}
	return *this;
}


float& Wektor::operator[](int index)
{
	return values[index];
}

float Wektor::length3D()
{
	float result = 0.0f;
	for (int i = 0; i < 3; i++)
	{
		result += (values[i] * values[i]);
	}
	return sqrt(result);
}

float Wektor::length4D()
{
	float result = 0.0f;
	for (int i = 0; i < 4; i++)
	{
		result += (values[i] * values[i]);
	}
	return sqrt(result);
}

float Wektor::dotProduct3D(Wektor & vec)
{
	float result = 0;
	for (int i = 0; i < 3; i++)
	{
		result += (values[i] * vec.values[i]);
	}
	return result;
}

float Wektor::dotProduct4D(Wektor & vec)
{
	float result = 0;
	for (int i = 0; i < 4; i++)
	{
		result += (values[i] * vec.values[i]);
	}
	return result;
}

void Wektor::normalize3D()
{
	float vecLength = length3D();
	if (vecLength == 0)//brak mo¿liwoœci normalizacji
	{
		std::cerr << "Cannot normalize vector length equals 0" << std::endl;
		return;
	}
	for (int i = 0; i < 4; i++)
	{
		values[i] /= vecLength;
	}
}

void Wektor::normalize4D()
{
	float vecLength = length4D();
	if (vecLength == 0)
	{
		std::cerr << "Cannot normalize vector length equals 0" << std::endl;
		return;
	}
	for (int i = 0; i < 4; i++)
	{
		values[i] /= vecLength;
	}

}

Wektor Wektor::crossProduct(Wektor& vec)
{
	return Wektor((values[1] * vec.values[2] - values[2] * vec.values[1]),
			        -(values[0] * vec.values[2] - values[2] * vec.values[0]),
			        (values[0] * vec.values[1] - values[1] * vec.values[0]),
			        values[3]);
}

std::ostream& operator<<(std::ostream& out, const Wektor& vec)
{
	out << "( ";
	for (int i = 0; i < 4; i++)
	{
		if (i == 3)
			out << vec.values[i];
		else
			out << vec.values[i] << ", ";
	}
	out << " )";
	return out;
}