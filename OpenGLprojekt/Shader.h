#pragma once
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

class Shader
{
public:
	Shader(const char* vShader, const char* fShader);
	string getVShader();
	string getFShader();
	string loadShader(const char* source);

private:
	string vertexShader;
	string fragmentShader;
};

