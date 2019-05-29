#include "Shader.h"
#include <iostream>
#include <cstring>

using namespace std;




Shader::Shader(const char* vShader, const char* fShader)
{
	vertexShader = loadShader(vShader);
	fragmentShader = loadShader(fShader);
}

string Shader::getVShader()
{
	return vertexShader;
}

string Shader::getFShader()
{
	return fragmentShader;
}

string Shader::loadShader(const char* source)
{
	ifstream file;
	file.open(source);
	string shader;
	stringstream fileBuffer;
	fileBuffer << file.rdbuf();
	file.close();
	shader = fileBuffer.str();
	return shader;
}
