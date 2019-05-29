#pragma once

#include <string.h>
#include <math.h>
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "Przeksztalcenia.h"
#include <vector>
#include "Vector.h"
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>


class ProgramMPGK
{
private:
	int wysokoscOkna;
	int szerokoscOkna;
	int polozenieOknaX;
	int polozenieOknaY;
	static GLuint VAO;
	static GLuint VBO;
	static GLuint IBO;
	static GLuint programZShaderami;
	static GLuint vertexShaderId;
	static GLuint fragmentShaderId;
	static GLint zmiennaShader;
	static float aspect;
	static bool moveFront;
	static bool moveBack;
	static bool moveRight;
	static bool moveLeft;
	static bool moveUp;
	static bool moveDown;
	static Wektor m_cameraPos;
	static Wektor m_cameraFront;
	static Wektor m_cameraUp;
	static float yaw;
	static float pitch;
	static float xOffset;
	static float yOffset;
	static bool rotateUp;
	static bool rotateDown;
	static bool rotateLeft;
	static bool rotateRight;

public:
	static void keyPressed(unsigned char key, int x, int y);
	static void keyUp(unsigned char key, int x, int y);
	static void keySpecials(int key, int x, int y);
	static void keySpecialsUp(int key, int x, int y);
	static Macierz moveCamera();
	static void rotateCamera(float p_xSensitivity, float p_ySensitivity);
	ProgramMPGK(void);
	ProgramMPGK(int wysokoscOkna, int szerokoscOkna, int polozenieOknaX, int polozenieOknaY);
	void stworzenieOkna(int argc, char** argv);
	void inicjalizacjaGlew();
	static void wyswietl();
	static void usun();
	void stworzenieVAO();
	void stworzenieVBO();
	void stworzenieIBO();
	void stworzenieProgramu();
	GLuint dodanieDoProgramu(GLuint programZShaderami, const GLchar* tekstShadera, GLenum typShadera);
	void sprawdzenieWersji();
};
