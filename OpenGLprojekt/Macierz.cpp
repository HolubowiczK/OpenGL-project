#include "Macierz.h"
using namespace std;

	Macierz::Macierz()
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				m_values[i][j] = 0;
			}
		}
	}

	Macierz::Macierz(float value)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
				m_values[i][j] = value;
		}
	}

	Macierz::Macierz(float matrix[4][4])
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
				m_values[i][j] = matrix[i][j];
		}
	}

	Macierz::Macierz(float matrix[3][3])
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
				m_values[i][j] = matrix[i][j];
			for (int i = 3; i < 4; i++)
			{
				for (int j = 3; j < 4; j++)
					m_values[i][j] = 0;
			}
		}
	}

	Macierz::Macierz(const Macierz & matrix)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				m_values[i][j] = matrix.m_values[i][j];
			}
		}
	}


	Macierz Macierz::operator=(const Macierz & matrix)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				m_values[i][j] = matrix.m_values[i][j];
			}
		}
		return *this;
	}

	Macierz Macierz::operator+(Macierz & matrix)
	{
		Macierz l_matrix;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				l_matrix.m_values[i][j] = m_values[i][j] + matrix.m_values[i][j];
			}
		}
		return l_matrix;
	}

	Macierz & Macierz::operator+=(Macierz & matrix)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				m_values[i][j] += matrix.m_values[i][j];
			}
		}
		return *this;
	}

	Macierz Macierz::operator-(Macierz & matrix)
	{
		Macierz l_matrix;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				l_matrix.m_values[i][j] = m_values[i][j] - matrix.m_values[i][j];
			}
		}
		return l_matrix;
	}

	Macierz & Macierz::operator-=(Macierz & matrix)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				m_values[i][j] -= matrix.m_values[i][j];
			}
		}
		return *this;
	}

	Macierz Macierz::operator*(float value)
	{
		Macierz l_matrix;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				l_matrix.m_values[i][j] = m_values[i][j] * value;
			}
		}
		return l_matrix;
	}
	Macierz & Macierz::operator*=(float value)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				m_values[i][j] *= value;
			}
		}
		return *this;
	}

	Macierz Macierz::operator*(Macierz & matrix)
	{
		Macierz l_matrix;
		for (int i = 0; i < 4; i++)
		{
			for (int k = 0; k < 4; k++)
			{
				float value = 0.0f;
				for (int j = 0; j < 4; j++)
				{
					value += (m_values[i][j] * matrix.m_values[j][k]);
				}
				l_matrix.m_values[i][k] = value;
			}

		}
		return l_matrix;
	}

	Macierz & Macierz::operator*=(Macierz & matrix)
	{
		Macierz l_matrix = *this;
		for (int i = 0; i < 4; i++)
		{
			for (int k = 0; k < 4; k++)
			{
				float value = 0.0f;
				for (int j = 0; j < 4; j++)
				{
					value += (l_matrix.m_values[i][j] * matrix.m_values[j][k]);
				}
				m_values[i][k] = value;
			}
		}
		return *this;
	}

	Wektor Macierz::operator*(Wektor & vector)
	{
		Wektor  l_vector;
		for (int i = 0; i < 4; i++)
		{
			float value = 0.0f;
			for (int j = 0; j < 4; j++)
			{
				value += vector[j] * m_values[j][i];
			}
			l_vector[i] = value;
		}
		return l_vector;
	}

	ostream & operator<<(ostream & out, const Macierz & matrix)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				out << matrix.m_values[i][j] << ", ";
			}
			out << endl;
		}
		return out;
	}

	float Macierz::getElement(int row, int column)
	{
		return m_values[row][column];
	}

	void Macierz::setElement(int row, int column, float value)
	{
		m_values[row][column] = value;
	}

	float * Macierz::getRow(int row)
	{
		return m_values[row];
	}
	

	void Macierz::identity()
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				m_values[i][j] = i == j ? 1.f : 0.f;
			}
		}
	}

	void Macierz::transpose()
	{
		Macierz matrixTemp(m_values);
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				m_values[j][i] = matrixTemp.m_values[i][j];
			}
		}
	}

	float Macierz::det3D()
	{
		return ((m_values[0][0] * m_values[1][1] * m_values[2][2]) +
			(m_values[0][1] * m_values[1][2] * m_values[2][0]) +
			(m_values[0][2] * m_values[1][0] * m_values[2][1])) -
			((m_values[0][2] * m_values[1][1] * m_values[2][0]) +
			(m_values[0][1] * m_values[1][0] * m_values[2][2]) +
				(m_values[0][0] * m_values[1][2] * m_values[2][1]));
	}

	float Macierz::det4D()
	{
		float result = 0.0f;
		float valuesForFirstParam[3][3]
		{
			{m_values[1][1], m_values[1][2], m_values[1][3]},
			{m_values[2][1], m_values[2][2], m_values[2][3]},
			{m_values[3][1], m_values[3][2], m_values[3][3]}
		};

		Macierz matrix3dTemp(valuesForFirstParam);

		result += (m_values[0][0] * matrix3dTemp.det3D());

		matrix3dTemp.setElement(0, 0, m_values[1][0]);
		matrix3dTemp.setElement(1, 0, m_values[2][0]);
		matrix3dTemp.setElement(2, 0, m_values[3][0]);

		result -= (m_values[0][1] * matrix3dTemp.det3D());

		matrix3dTemp.setElement(0, 1, m_values[1][1]);
		matrix3dTemp.setElement(1, 1, m_values[2][1]);
		matrix3dTemp.setElement(2, 1, m_values[3][1]);

		result += (m_values[0][2] * matrix3dTemp.det3D());

		matrix3dTemp.setElement(0, 2, m_values[1][2]);
		matrix3dTemp.setElement(1, 2, m_values[2][2]);
		matrix3dTemp.setElement(2, 2, m_values[3][2]);

		result -= (m_values[0][3] * matrix3dTemp.det3D());

		return result;
	}

	Macierz Macierz::cofactor3D()
	{
		Macierz resultMatrix;
		float l_values[4];
		int elements = 0;

		for (int row = 0; row < 3; row++)
		{
			for (int column = 0; column < 3; column++)
			{
				for (int i = 0; i < 3; i++)
				{
					for (int j = 0; j < 3; j++)
					{
						if (i != row && j != column)
						{
							l_values[elements++] = m_values[i][j];
						}
					}
				}
				elements = 0;
				float element = (l_values[0] * l_values[3]) - (l_values[1] * l_values[2]);
				if ((row + column) % 2 == 0)
					resultMatrix.setElement(row, column, element);
				else
					resultMatrix.setElement(row, column, -element);
			}
		}
		resultMatrix.transpose();
		return resultMatrix;
	}

	Macierz Macierz::cofactor4D()
	{
		Macierz resultMatrix;
		float l_values[3][3];
		int rowElements = 0;
		int columnElements = 0;

		for (int row = 0; row < 4; row++)
		{
			for (int column = 0; column < 4; column++)
			{
				for (int i = 0; i < 4; i++)
				{
					for (int j = 0; j < 4; j++)
					{
						if (i != row && j != column)
						{
							l_values[rowElements][columnElements++] = m_values[i][j];
						}
					}
					if (columnElements >= 3)
					{
						columnElements = 0;
						rowElements++;
					}
				}
				Macierz tempMatrix(l_values);
				rowElements = 0;
				columnElements = 0;
				float element = tempMatrix.det3D();
				if ((row + column) % 2 == 0)
					resultMatrix.setElement(row, column, element);
				else
					resultMatrix.setElement(row, column, -element);
			}
		}
		resultMatrix.transpose();
		return resultMatrix;
	}

	void Macierz::inverse4D()
	{
		Macierz tempMatrix = *this;
		float det = tempMatrix.det4D();
		if (det == 0)//gdy wyznacznik jest równy 0 macierz jest nieodwracalna
		{
			cerr << "Cannot inverse matrix" << endl;
			return;
		}
		float inverseDet = 1.0f / det;
		*this = tempMatrix.cofactor4D();

		*this *= inverseDet;
	}

	void Macierz::inverse3D()
	{
		Macierz tempMatrix = *this;
		float det = tempMatrix.det3D();
		if (det == 0)
		{
			cerr << "Cannot inverse matrix" << endl;
			return;
		}
		float inverseDet = 1.0f / det;
		*this = tempMatrix.cofactor3D();

		*this *= inverseDet;
	}

	
