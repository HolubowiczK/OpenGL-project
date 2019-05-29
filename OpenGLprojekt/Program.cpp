#include "Program.h"
#include <Windows.h>

using namespace std;

GLuint ProgramMPGK::VAO;//bufory
GLuint ProgramMPGK::VBO;
GLuint ProgramMPGK::IBO;
GLuint ProgramMPGK::programZShaderami;//program
GLuint ProgramMPGK::vertexShaderId;//id shaderów
GLuint ProgramMPGK::fragmentShaderId;
GLint MVP;//id zmiennych z vshadera
float ProgramMPGK::aspect;
bool ProgramMPGK::moveFront = false;//flagi przesuwania obiektu
bool ProgramMPGK::moveBack = false;
bool ProgramMPGK::moveRight = false;
bool ProgramMPGK::moveLeft = false;
bool ProgramMPGK::moveUp = false;
bool ProgramMPGK::moveDown = false;
float ProgramMPGK::pitch = 0.0f;//kąty obrotu
float ProgramMPGK::yaw = 90.0f;
float ProgramMPGK::xOffset = 0.0f;//przesunięcie
float ProgramMPGK::yOffset = 0.0f;
bool ProgramMPGK::rotateUp = false;//flagi obrotu obiektu
bool ProgramMPGK::rotateDown = false;
bool ProgramMPGK::rotateLeft = false;
bool ProgramMPGK::rotateRight = false;
Wektor ProgramMPGK::m_cameraPos;//wektory kamery
Wektor ProgramMPGK::m_cameraFront;
Wektor ProgramMPGK::m_cameraUp;
const float speed = 0.005f;//szybkość przesuwania obiektu
const float sensitivity = 25.0f;//czułość przesówania

template<typename Type>
Type allMoves(Type matrix)
{
	return matrix;
}

template<typename Type, typename... Args>
Type allMoves(Type matrix, Args... matrices)//funkcja mnożąca wiele macierzy
{
	return allMoves(matrices...) * matrix;
}

string loadShader(const char* source)//ładowanie shadera z pliku
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

void saveShader(const char* source, char* shader)//zapis shadera do pliku
{
	ofstream file;
	file.open(source);
	file << shader;
	file.close();
}

void ProgramMPGK::keyPressed(unsigned char key, int x, int y)//obsługa wciśnięcia przycisku
{
	switch (key)
	{
	case 'f':
		glutFullScreenToggle();//zał/wył trybu pełnoekranowego
		break;
	case VK_ESCAPE: //przycik escape
		glutExit();//zakończenie działania programu
		break;
	case 'w':
		moveUp = true;
		break;
	case 's':
		moveDown = true;
		break;
	case 'a':
		moveLeft = true;
		break;
	case 'd':
		moveRight = true;
		break;
	case '[':
		moveFront = true;
		break;
	case ']':
		moveBack = true;
		break;
	}
}

void ProgramMPGK::keyUp(unsigned char key, int x, int y)//obsługa puszczenia  przycisku
{
	switch (key)
	{
	case 'w':
		moveUp = false;
		break;
	case 's':
		moveDown = false;
		break;
	case 'a':
		moveLeft = false;
		break;
	case 'd':
		moveRight = false;
		break;
	case '[':
		moveFront = false;
		break;
	case ']':
		moveBack = false;
		break;
	}
}

void ProgramMPGK::keySpecials(int key, int x, int y)//wciśnięcie przycisków strzałek
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		rotateLeft = true;
		break;
	case GLUT_KEY_RIGHT:
		rotateRight = true;
		break;
	case GLUT_KEY_UP:
		rotateUp = true;
		break;
	case GLUT_KEY_DOWN:
		rotateDown = true;
		break;
	}
}

void ProgramMPGK::keySpecialsUp(int key, int x, int y)//puszczenie przycisku strzałek
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		rotateLeft = false;
		break;
	case GLUT_KEY_RIGHT:
		rotateRight = false;
		break;
	case GLUT_KEY_UP:
		rotateUp = false;
		break;
	case GLUT_KEY_DOWN:
		rotateDown = false;
		break;
	}
}

Macierz ProgramMPGK::moveCamera()//przesuniecie kamery
{
	Wektor l_cameraFront = m_cameraFront * speed;
	if (moveFront)//jeżeli przesunąć do przodu
	{
		m_cameraPos += l_cameraFront;
	}
	if (moveBack)//jeżeli przesunąć do tyłu
	{
		m_cameraPos -= l_cameraFront;
	}
	Wektor l_cameraRight = m_cameraFront.crossProduct(m_cameraUp);
	if (moveLeft)//jeżeli przesunąć w lewo
	{
		l_cameraRight.normalize3D();
		l_cameraRight *= speed;
		m_cameraPos -= l_cameraRight;
	}
	if (moveRight)//jeżeli przesunąć w prawo
	{
		l_cameraRight.normalize3D();
		l_cameraRight *= speed;
		m_cameraPos += l_cameraRight;
	}
	if (moveUp)//jeżeli przesunąć do góry
	{
		Wektor l_cameraUp = m_cameraFront.crossProduct(l_cameraRight);
		l_cameraUp.normalize3D();
		l_cameraUp *= speed;
		m_cameraPos += l_cameraUp;
	}
	if (moveDown)//jeżeli przesunąć w dół
	{
		Wektor l_cameraUp = m_cameraFront.crossProduct(l_cameraRight);
		l_cameraUp.normalize3D();
		l_cameraUp *= speed;
		m_cameraPos -= l_cameraUp;
	}

	return Przeksztalcenia::lookAt(m_cameraPos, m_cameraFront*-1, m_cameraUp);
}

void ProgramMPGK::rotateCamera(float p_xSensitivity, float p_ySensitivity)//obrót kamery
{
	if (rotateUp)
	{
		yOffset = fmod((yOffset - (sensitivity * speed)), 360.0f);
	}
	if (rotateLeft)
	{
		xOffset = fmod((xOffset - (sensitivity * speed)), 360.0f);
	}
	if (rotateRight)
	{
		xOffset = fmod((xOffset + (sensitivity * speed)), 360.0f);
	}
	if (rotateDown)
	{
		yOffset = fmod((yOffset + (sensitivity * speed)), 360.0f);
	}

	xOffset *= p_xSensitivity;
	yOffset *= p_ySensitivity;
	yaw += xOffset;
	pitch += yOffset;

	if (pitch > 100.0f)//ograniczenie obratu w pionie
	{
		pitch = 100.0f;
	}
	else if (pitch < -100.0f)
	{
		pitch = -100.0f;
	}

	Wektor front;
	front.setX(cos(Przeksztalcenia::naRadiany(yaw)) * cos(Przeksztalcenia::naRadiany(pitch)));
	front.setY(sin(Przeksztalcenia::naRadiany(pitch)));
	front.setZ(sin(Przeksztalcenia::naRadiany(yaw)) * cos(Przeksztalcenia::naRadiany(pitch)));
	front.normalize3D();
	m_cameraFront = front;
}

ProgramMPGK::ProgramMPGK(void)//konstruktor bezparametrowy
{
	m_cameraPos = Wektor(1.0f, 0.0f, -3.0f);
	m_cameraFront = Wektor(0.0f, 0.0f, 1.0f);
	m_cameraUp = Wektor(0.0f, 1.0f, 0.0f);
	wysokoscOkna = 768;
	szerokoscOkna = 1024;
	polozenieOknaX = 100;
	polozenieOknaY = 100;
	aspect = (float)szerokoscOkna / (float)wysokoscOkna;
}

ProgramMPGK::ProgramMPGK(int wysokoscOkna, int szerokoscOkna, int polozenieOknaX, int polozenieOknaY)//konstruktor z parametrami okna
{
	m_cameraPos = Wektor(1.0f, 0.0f, -3.0f);
	m_cameraFront = Wektor(0.0f, 0.0f, 1.0f);
	m_cameraUp = Wektor(0.0f, 1.0f, 0.0f);
	this->wysokoscOkna = wysokoscOkna;//parametry okna
	this->szerokoscOkna = szerokoscOkna;
	this->polozenieOknaX = polozenieOknaX;
	this->polozenieOknaY = polozenieOknaY;
	aspect = (float)this->szerokoscOkna / (float)this->wysokoscOkna;
}

void ProgramMPGK::stworzenieOkna(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(szerokoscOkna, wysokoscOkna);//ustawienie wysokości i szerokości
	glutInitWindowPosition(polozenieOknaX, polozenieOknaY);//ustawienie położenia
	glutInitContextVersion(3, 3);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutCreateWindow("Program");//stworzenie okna o nazwie "program"
}

void ProgramMPGK::inicjalizacjaGlew()
{
	GLenum wynik = glewInit();
	if (wynik != GLEW_OK)//Błąd przy inicjalizacji
	{
		cerr << "Nie udalo sie zainicjalizowac GLEW. Blad: " << glewGetErrorString(wynik) << endl;
		//system("pause");
		exit(1);
	}
}

void ProgramMPGK::wyswietl()
{
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);//ustawienie wartości użytej do porównywania bufera głebi

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//czyszczenie buforów
	
	Macierz translate = Przeksztalcenia::createTranslateMatrix4D(1.0f, 0.0f, 0.0f);
	Macierz scale = Przeksztalcenia::createScaleMatrix4D(0.6f);

	//static GLfloat zmiana = 0.0f;
	//zmiana += 0.002f;
	//Macierz l_rotateY = Przeksztalcenia::rotateY(15.0f * zmiana);
	//Macierz l_rotateZ = Przeksztalcenia::rotateZ(35.0f);
	Macierz l_rotateX = Przeksztalcenia::rotateX(30.0f);

	Macierz model;//macierz modelu
	model.identity();
	model = allMoves(model, scale, l_rotateX, translate);

	Macierz view;//macierz kamery
	view.identity();
	rotateCamera(0.2f, 0.2f);
	view = moveCamera();

	Macierz projection;//macierz perspektywy
	projection.identity();
	projection = Przeksztalcenia::createProjectionMatrix(45.0f, aspect, 0.01f, 100.0f);
	Macierz mMvp = projection * view * model;
	glUniformMatrix4fv(MVP, 1, GL_TRUE, mMvp.getRow(0));//przekazanie macierzymMvp do shadera

	glEnableVertexAttribArray(0);//załączenie dostępu do elementów 0,1
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);//przypisanie bufera VBO dla GL_ARRAY_BUFFER
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, 0);//określenie grupowania danych, kroku przeszukiwania i początku danych
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, (GLvoid*)(sizeof(GLfloat) * 4));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);//przypisanie bufera IBO dla GL_ELEMENT_ARRAY_BUFFER

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);//narysowanie trójkątów dla 36 punktów

	glDisableVertexAttribArray(0);//zamknięcie dostępu do elementów 0,1
	glDisableVertexAttribArray(1);

	glutSwapBuffers();//zamiana wyświetlanych buferów
}

void ProgramMPGK::usun()//usuwanie obiektów programu
{
	glDeleteShader(vertexShaderId);
	glDeleteShader(fragmentShaderId);
	glDeleteProgram(programZShaderami);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &IBO);
	glDeleteVertexArrays(1, &VAO);
}

void ProgramMPGK::stworzenieVAO()
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
}

void ProgramMPGK::stworzenieVBO()
{
	Wektor wierzcholki[] = {
		Wektor(-0.5f, -0.5f, -0.5f), Wektor(1.0f, 0.0f, 0.0f),//lewa połowa położenie wierzchołków
		Wektor(0.5f, -0.5f, -0.5f), Wektor(1.0f, 0.0f, 0.0f),//prawa połowa kolory
		Wektor(0.5f, 0.5f, -0.5f), Wektor(1.0f, 0.0f, 0.0f),
		Wektor(-0.5f, 0.5f, -0.5f), Wektor(1.0f, 0.0f, 0.0f),// Tył

		Wektor(0.5f, -0.5f, 0.5f), Wektor(1.0f, 0.0f, 1.0f),
		Wektor(0.5f, 0.5f, 0.5f), Wektor(1.0f, 0.0f, 1.0f),
		Wektor(-0.5f, 0.5f, 0.5f), Wektor(1.0f, 0.0f, 1.0f),
		Wektor(-0.5f, -0.5f, 0.5f), Wektor(1.0f, 0.0f, 1.0f), // Przód

		Wektor(-0.5f, -0.5f, 0.5f), Wektor(0.0f, 0.0f, 1.0f),
		Wektor(-0.5f, -0.5f, -0.5f), Wektor(0.0f, 0.0f, 1.0f),
		Wektor(-0.5f, 0.5f, -0.5f), Wektor(0.0f, 0.0f, 1.0f),
		Wektor(-0.5f, 0.5f, 0.5f), Wektor(0.0f, 0.0f, 1.0f),// Lewo

		Wektor(0.5f, -0.5f, -0.5f), Wektor(0.5f, 0.5f, 0.5f),
		Wektor(0.5f, -0.5f, 0.5f), Wektor(0.5f, 0.5f, 0.5f),
		Wektor(0.5f, 0.5f, 0.5f), Wektor(0.5f, 0.5f, 0.5f),
		Wektor(0.5f, 0.5f, -0.5f), Wektor(0.5f, 0.5f, 0.5f),// Prawo

		Wektor(-0.5f, 0.5f, -0.5f), Wektor(0.5f, 0.5f, 0.0f),
		Wektor(0.5f, 0.5f, -0.5f), Wektor(0.5f, 0.5f, 0.0f),
		Wektor(0.5f, 0.5f, 0.5f), Wektor(0.5f, 0.5f, 0.0f),
		Wektor(-0.5f, 0.5f, 0.5f), Wektor(0.5f, 0.5f, 0.0f),// Góra

		Wektor(-0.5f, -0.5f, 0.5f), Wektor(0.0f, 0.0f, 0.0f),
		Wektor(0.5f, -0.5f, 0.5f), Wektor(0.0f, 0.0f, 0.0f),
		Wektor(0.5f, -0.5f, -0.5f), Wektor(0.0f, 0.0f, 0.0f),
		Wektor(-0.5f, -0.5f, -0.5f), Wektor(0.0f, 0.0f, 0.0f)// Dół
	};
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);//przypisanie bufora o nazwie VBO do GL_ARRAY_BUFFER
	glBufferData(GL_ARRAY_BUFFER, sizeof(wierzcholki), &wierzcholki[0], GL_STATIC_DRAW);//stworzenie bufora z danymi dla GL_ARRAY_BUFFER, wskazanie wielkości danych i ich źródła
}

void ProgramMPGK::stworzenieIBO()
{
	GLuint indeksyTab[] = {//tablica używana do rysowania trójkątów
		0, 1, 2, 0, 3, 2, // Tył
		4, 5, 6, 4, 7, 6, //Przód
		8, 9, 10, 8, 11, 10, //Lewo
		12, 13, 14, 12, 15, 14, //Prawo
		16, 17, 18, 16, 19, 18, //Góra
		20, 21, 22, 20, 23, 22 //Dół
	};

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);//przypisanie bufora
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indeksyTab), indeksyTab, GL_STATIC_DRAW);//stworzenie bufora
}

void ProgramMPGK::stworzenieProgramu()
{
	programZShaderami = glCreateProgram();//tworzenie programu

	if (programZShaderami == 0)//błąd w tworzeniu programu
	{
		cerr << "Blad podczas tworzenia programu shaderow." << endl;
		system("pause");
		exit(1);
	}

	string vertexShader = loadShader("vertexShader.txt");//załadowanie tektów shaderów
	string fragmentShader = loadShader("fragmentShader.txt");

	vertexShaderId = dodanieDoProgramu(programZShaderami, vertexShader.c_str(), GL_VERTEX_SHADER);//dodanie shaderów do programu
	fragmentShaderId = dodanieDoProgramu(programZShaderami, fragmentShader.c_str(), GL_FRAGMENT_SHADER);

	GLint linkowanieOK = 0;
	glLinkProgram(programZShaderami);
	glGetProgramiv(programZShaderami, GL_LINK_STATUS, &linkowanieOK);
	if (linkowanieOK == GL_FALSE) {//błąd w linkowaniu programu
		GLint dlugoscLoga = 0;
		glGetProgramiv(programZShaderami, GL_INFO_LOG_LENGTH, &dlugoscLoga);
		vector<GLchar> log(dlugoscLoga);//log z informacją o błędzie
		glGetProgramInfoLog(programZShaderami, dlugoscLoga, NULL, &log[0]);
		cerr << "Blad podczas linkowania programu shaderow." << endl;//wypisanie błędu
		for (vector<GLchar>::const_iterator i = log.begin(); i != log.end(); ++i)
			cerr << *i;
		cerr << endl;
		glDeleteProgram(programZShaderami);//usunięcie programu
		system("pause");
		exit(1);
	}

	GLint walidacjaOK = 0;
	glValidateProgram(programZShaderami);//walidacja programu
	glGetProgramiv(programZShaderami, GL_VALIDATE_STATUS, &walidacjaOK);
	if (walidacjaOK == GL_FALSE) {//błąd walidacji
		GLint dlugoscLoga = 0;
		glGetProgramiv(programZShaderami, GL_INFO_LOG_LENGTH, &dlugoscLoga);
		vector<GLchar> log(dlugoscLoga);
		glGetProgramInfoLog(programZShaderami, dlugoscLoga, NULL, &log[0]);
		cerr << "Blad podczas walidacji programu shaderow." << endl;
		for (vector<GLchar>::const_iterator i = log.begin(); i != log.end(); ++i)
			cerr << *i;
		cerr << endl;
		glDeleteProgram(programZShaderami);
		system("pause");
		exit(1);
	}

	glUseProgram(programZShaderami);//użycie programu przy renderowaniu

	MVP = glGetUniformLocation(programZShaderami, "MVPmatrix");//indeks zmiennej z vshadera

}

GLuint ProgramMPGK::dodanieDoProgramu(GLuint programZShaderami, const GLchar * tekstShadera, GLenum typShadera)
{
	GLuint shader = glCreateShader(typShadera);//tworzenie shadera

	// 35633 -> vertex shader, 35632 -> fragment shader
	const GLchar* typShaderaTekst = typShadera == 35633 ? "vertex" : "fragment";

	if (shader == 0) {//błąd w utworzeniu shadera
		cerr << "Blad podczas tworzenia " << typShaderaTekst << " shadera." << endl;
		//system("pause");
		exit(0);
	}

	const GLchar* tekstShaderaTab[1];
	tekstShaderaTab[0] = tekstShadera;//tekst shadera
	GLint dlugoscShadera[1];
	dlugoscShadera[0] = strlen(tekstShadera);//długość shadera
	glShaderSource(shader, 1, tekstShaderaTab, dlugoscShadera);//przypisanie tekstu i wartości do shadera - przyjmuje tablice

	glCompileShader(shader);//kompilacja shadera
	GLint kompilacjaOK = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &kompilacjaOK);//sprawdzenie poprawności shadera
	if (kompilacjaOK == GL_FALSE)//informacje o miejscu błędu w shaderze
	{
		GLint dlugoscLoga = 0;//log z informacją o błędzie
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &dlugoscLoga);
		vector<GLchar> log(dlugoscLoga);
		glGetShaderInfoLog(shader, dlugoscLoga, NULL, &log[0]);
		cerr << endl;
		cerr << "Blad podczas kompilacji " << typShaderaTekst << " shadera." << endl;//wypisanie informacji o błędach
		cerr << endl;
		cerr << "log: ";
		for (auto i = log.cbegin(); i != log.cend(); ++i)
			cerr << *i;
		cerr << endl;
		glDeleteShader(shader);//usunięcie błędnego shadera
		system("pause");
		exit(1);
	}

	glAttachShader(programZShaderami, shader);//dodanie shadera do programu
	return shader;//zwrócenie id rodzaju shaddera
}
void ProgramMPGK::sprawdzenieWersji()
{
	cout << "Wersja GLEW: " << glewGetString(GLEW_VERSION) << endl;//informacje o bibliotekach
	cout << "Wersja VENDOR: " << glGetString(GL_VENDOR) << endl;
	cout << "Wersja REDERER: " << glGetString(GL_RENDERER) << endl;
	cout << "Wersja GL: " << glGetString(GL_VERSION) << endl;
	cout << "Wersja GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}

int main(int argc, char** argv)
{

	ProgramMPGK obiektMPGK(786, 786, 100, 100);

	obiektMPGK.stworzenieOkna(argc, argv);
	obiektMPGK.inicjalizacjaGlew();
	obiektMPGK.sprawdzenieWersji();
	obiektMPGK.stworzenieVAO();
	obiektMPGK.stworzenieVBO();
	obiektMPGK.stworzenieIBO();
	obiektMPGK.stworzenieProgramu();
	glutDisplayFunc(obiektMPGK.wyswietl);//przypisanie funkcji wyświetlania do obsługi wyświetlania biblioteki glut
	glutIdleFunc(obiektMPGK.wyswietl);
	glutCloseFunc(obiektMPGK.usun);//przypisanie funkcji usuwania elementów do obsługi zamykania aplikacji biblioteki glut
	glutKeyboardFunc(obiektMPGK.keyPressed);//przypisanie własnych metod obsługi klawiatury do funkcji 
	glutKeyboardUpFunc(obiektMPGK.keyUp);
	glutSpecialFunc(obiektMPGK.keySpecials);
	glutSpecialUpFunc(obiektMPGK.keySpecialsUp);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);//ustawienie wartośći domyślnych przy czyszczeniu bufora kolorów (kolor tła)

	glutMainLoop();//start programu
	

	//system("pause");
	return 0;
}
