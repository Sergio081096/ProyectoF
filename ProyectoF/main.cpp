


#include "texture.h"
#include "cmodel/CModel.h"
#include "Camera.h"

#if (_MSC_VER == 1900)
#   pragma comment( lib, "legacy_stdio_definitions.lib" )
#endif

int font = (int)GLUT_BITMAP_HELVETICA_18;

static GLdouble rotacion[9] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
static GLdouble traslacion[9] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
static GLdouble velocidad[9] = { 4.5, 3.7, 3.0, 2.0, 2.3, 1.8, 1.3, 0.8, 0.5 };

bool p = false;
bool o = false;

float camaraZ = 0.0;
float camaraX = 0.0;


int solT = 0;
int mercurioT = 0;
int venusT = 0;
int tierraT = 0, lunaT = 0;
int marteT = 0;
int jupiterT = 0;
int saturnoT = 0;
int uranoT = 0;
int neptunoT = 0;
int anillo = 0;

DWORD dwCurrentTime = 0;
DWORD dwLastUpdateTime = 0;
DWORD dwElapsedTime = 0;

CCamera objCamera;	//Create objet Camera

CTexture cubo;
CTexture sol;
CTexture espacio;
CTexture mercurio;
CTexture venus;
CTexture tierra;
CTexture marte;
CTexture jupiter;
CTexture saturno;
CTexture urano;
CTexture neptuno;
CTexture luna;
CTexture uss1;
CTexture uss2;
CTexture uss3;
CTexture uss4;
CTexture uss5;
CTexture uss6;

CModel satellite1;
CModel satellite2;
CModel satellite3;
CModel satellite4;
CModel spaceman;
CModel nave;
CModel nave1;
CModel nave2;

void init(void)
{
	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat position[] = { 0.0, 0.0, -420.0, 1.0 };
	GLfloat lmodel_ambient[] = { 0.4, 0.4, 0.4, 1.0 };
	GLfloat local_view[] = { 0.0 };

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

	//glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
	//glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT1, GL_POSITION, position);
	//glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.005);
	//glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.00001);
	//glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
	//glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glClearDepth(1.0f);									// Configuramos Depth Buffer
	glEnable(GL_DEPTH_TEST);							// Habilitamos Depth Testing
	glDepthFunc(GL_LEQUAL);								// Tipo de Depth Testing a realizar
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);

	cubo.LoadBMP("cubo.bmp");
	cubo.BuildGLTexture();
	cubo.ReleaseImage();

	sol.LoadBMP("sol.bmp");
	sol.BuildGLTexture();
	sol.ReleaseImage();

	espacio.LoadBMP("espacio.bmp");
	espacio.BuildGLTexture();
	espacio.ReleaseImage();

	mercurio.LoadBMP("mercury.bmp");
	mercurio.BuildGLTexture();
	mercurio.ReleaseImage();

	venus.LoadBMP("venus.bmp");
	venus.BuildGLTexture();
	venus.ReleaseImage();

	tierra.LoadBMP("tierra.bmp");
	tierra.BuildGLTexture();
	tierra.ReleaseImage();

	marte.LoadBMP("marte.bmp");
	marte.BuildGLTexture();
	marte.ReleaseImage();

	jupiter.LoadBMP("jupiter.bmp");
	jupiter.BuildGLTexture();
	jupiter.ReleaseImage();

	saturno.LoadBMP("saturno.bmp");
	saturno.BuildGLTexture();
	saturno.ReleaseImage();

	urano.LoadBMP("urano.bmp");
	urano.BuildGLTexture();
	urano.ReleaseImage();

	neptuno.LoadBMP("neptuno.bmp");
	neptuno.BuildGLTexture();
	neptuno.ReleaseImage();

	luna.LoadBMP("luna.bmp");
	luna.BuildGLTexture();
	luna.ReleaseImage();

	spaceman._3dsLoad("astro/Spaceman.3ds");
	spaceman.LoadTextureImages();
	spaceman.GLIniTextures();
	spaceman.ReleaseTextureImages();

	satellite1._3dsLoad("galileo.3ds");

	satellite2._3dsLoad("Satellite.3ds");

	satellite3._3dsLoad("SpaceStation.3ds");

	satellite4._3dsLoad("sat/Satellite.3ds");
	satellite4.LoadTextureImages();
	satellite4.GLIniTextures();
	satellite4.ReleaseTextureImages();

	nave._3dsLoad("Spaceship.3ds");

	nave1._3dsLoad("Lander.3ds");

	nave2._3dsLoad("space.3ds");

	uss1.LoadBMP("ussE/uss.bmp");
	uss1.BuildGLTexture();
	uss1.ReleaseImage();

	uss2.LoadBMP("ussE/usse.bmp");
	uss2.BuildGLTexture();
	uss2.ReleaseImage();

	uss3.LoadBMP("ussE/ussem.bmp");
	uss3.BuildGLTexture();
	uss3.ReleaseImage();

	uss4.LoadBMP("ussE/ussek.bmp");
	uss4.BuildGLTexture();
	uss4.ReleaseImage();

	uss5.LoadBMP("ussE/venm.bmp");
	uss5.BuildGLTexture();
	uss5.ReleaseImage();

	uss6.LoadBMP("ussE/ven.bmp");
	uss6.BuildGLTexture();
	uss6.ReleaseImage();
	
	objCamera.Position_Camera(0, 2.5f, 3, 0, 2.5f, 0, 0, 1, 0);
}

void camaraP() {
	//camara primera persona
	gluLookAt(objCamera.mPos.x, objCamera.mPos.y, objCamera.mPos.z,
		objCamera.mView.x, objCamera.mView.y, objCamera.mView.z,
		objCamera.mUp.x, objCamera.mUp.y, objCamera.mUp.z);
}

void camaraT() {
	//camara topdown
	gluLookAt(0.0 - 0.5*objCamera.mPos.z, 400.0 + 10*objCamera.mPos.y, -250.0 + 0.5*objCamera.mPos.x, 
		0.0 - 0.5*objCamera.mPos.z, 0.0 + objCamera.mPos.y , -250.0 + 0.5*objCamera.mPos.x,
		1, 0, 0.0);

}

void timerFunction() 
{
	dwCurrentTime = GetTickCount(); // Even better to use timeGetTime()--contador
	dwElapsedTime = dwCurrentTime - dwLastUpdateTime;

	if (dwElapsedTime >= 50 && o )
	{
		solT = (solT - 5) % 360;
		mercurioT = (mercurioT - 6) % 360;
		venusT = (venusT - 5) % 360;
		lunaT = (lunaT - 3) % 360;
		tierraT = (tierraT - 2) % 360;
		marteT = (marteT - 3) % 360;
		jupiterT = (jupiterT - 6) % 360;
		saturnoT = (saturnoT - 3) % 360;
		uranoT = (uranoT - 7) % 360;
		neptunoT = (uranoT - 7) % 360;
		dwLastUpdateTime = dwCurrentTime;
	}
	glutPostRedisplay();
	//glutTimerFunc(20, timerFunction, 1);
}

void skybox(float largo, float altura, float profundidad, GLuint text)  //Funcion creacion cielo
{

	GLfloat vertice[8][3] = {
				{0.5*largo ,-0.5*altura, 0.5*profundidad},    //Coordenadas Vértice 1 V1
				{-0.5*largo ,-0.5*altura , 0.5*profundidad},    //Coordenadas Vértice 2 V2
				{-0.5*largo ,-0.5*altura , -0.5*profundidad},    //Coordenadas Vértice 3 V3
				{0.5*largo ,-0.5*altura , -0.5*profundidad},    //Coordenadas Vértice 4 V4
				{0.5*largo ,0.5*altura , 0.5*profundidad},    //Coordenadas Vértice 5 V5
				{0.5*largo ,0.5*altura , -0.5*profundidad},    //Coordenadas Vértice 6 V6
				{-0.5*largo ,0.5*altura , -0.5*profundidad},    //Coordenadas Vértice 7 V7
				{-0.5*largo ,0.5*altura , 0.5*profundidad},    //Coordenadas Vértice 8 V8
	};

	glBindTexture(GL_TEXTURE_2D, text);   // choose the texture to use.
	//glBindTexture(GL_TEXTURE_2D, texture[filter]);   // choose the texture to use.
	glBegin(GL_POLYGON);	//Front
		//glColor3f(0.0,0.0,1.0);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[0]);
	glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertice[4]);
	glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertice[7]);
	glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertice[1]);
	glEnd();

	glBegin(GL_POLYGON);	//Right
		//glColor3f(0.0,0.0,1.0);
	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[0]);
	glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertice[3]);
	glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertice[5]);
	glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertice[4]);
	glEnd();

	glBegin(GL_POLYGON);	//Back
		//glColor3f(0.0,1.0,0.0);
	glNormal3f(0.0f, 0.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertice[6]);
	glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertice[5]);
	glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertice[3]);
	glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[2]);
	glEnd();

	glBegin(GL_POLYGON);  //Left
		//glColor3f(1.0,1.0,1.0);
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertice[1]);
	glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertice[7]);
	glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertice[6]);
	glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[2]);
	glEnd();

	glBegin(GL_POLYGON);  //Bottom
		//glColor3f(0.4,0.2,0.6);
	glNormal3f(0.0f, -1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[0]);
	glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertice[1]);
	glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertice[2]);
	glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertice[3]);
	glEnd();

	glBegin(GL_POLYGON);  //Top
		//glColor3f(0.8,0.2,0.4);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[4]);
	glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertice[5]);
	glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertice[6]);
	glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertice[7]);
	glEnd();
}

void dibujarSol(GLfloat radio, int meridianos, int paralelos)
{
	float ctext_s = 1.0 / meridianos;
	float ctext_t = 1.0 / paralelos;

	glBindTexture(GL_TEXTURE_2D, sol.GLindex);   // choose the texture to use.
	float v1[] = { 0.0, 0.0, 0.0 };
	float v2[] = { 0.0, 0.0, 0.0 };
	float v3[] = { 0.0, 0.0, 0.0 };
	float v4[] = { 0.0, 0.0, 0.0 };
	int i, j;
	float angulom, angulop;
	angulom = 2 * 3.141592654 / meridianos;
	angulop = 3.141592654 / paralelos;
	for (i = 0; i < meridianos; i++)
	{
		for (j = 0; j < paralelos; j++)
		{
			v1[0] = radio * cos(angulom*i)*sin(angulop*j);
			v1[1] = radio * cos(angulop*j);
			v1[2] = radio * sin(angulom*i)*sin(angulop*j);

			v2[0] = radio * cos(angulom*i)*sin(angulop*(j + 1));
			v2[1] = radio * cos(angulop*(j + 1));
			v2[2] = radio * sin(angulom*i)*sin(angulop*(j + 1));

			v3[0] = radio * cos(angulom*(i + 1))*sin(angulop*(j + 1));
			v3[1] = radio * cos(angulop*(j + 1));
			v3[2] = radio * sin(angulom*(i + 1))*sin(angulop*(j + 1));

			v4[0] = radio * cos(angulom*(i + 1))*sin(angulop*j);
			v4[1] = radio * cos(angulop*j);
			v4[2] = radio * sin(angulom*(i + 1))*sin(angulop*j);

			glBegin(GL_POLYGON);
			glNormal3fv(v1);
			glTexCoord2f(ctext_s*i, -ctext_t * j);
			glVertex3fv(v1);
			glNormal3fv(v2);
			glTexCoord2f(ctext_s*i, -ctext_t * (j + 1));
			glVertex3fv(v2);
			glNormal3fv(v3);
			glTexCoord2f(ctext_s*(i + 1), -ctext_t * (j + 1));
			glVertex3fv(v3);
			glNormal3fv(v4);
			glTexCoord2f(ctext_s*(i + 1), -ctext_t * j);
			glVertex3fv(v4);
			glEnd();
		}
	}
}

void dibujarPlaneta(GLfloat radio, int meridianos, int paralelos,int planeta, GLuint text, int posicion)
{
	glPushMatrix();
	
	glTranslatef(posicion, 0.2, 0.2);
	glRotatef(0.5*traslacion[planeta], 0.0, 1.0, 0.0);
	float ctext_s = 1.0 / meridianos;
	float ctext_t = 1.0 / paralelos;

	glBindTexture(GL_TEXTURE_2D, text);   // choose the texture to use.
	float v1[] = { 0.0, 0.0, 0.0 };
	float v2[] = { 0.0, 0.0, 0.0 };
	float v3[] = { 0.0, 0.0, 0.0 };
	float v4[] = { 0.0, 0.0, 0.0 };
	int i, j;
	float angulom, angulop;
	angulom = 2 * 3.141592654 / meridianos;
	angulop = 3.141592654 / paralelos;
	for (i = 0; i < meridianos; i++)
	{
		for (j = 0; j < paralelos; j++)
		{
			v1[0] = radio * cos(angulom*i)*sin(angulop*j);
			v1[1] = radio * cos(angulop*j);
			v1[2] = radio * sin(angulom*i)*sin(angulop*j);

			v2[0] = radio * cos(angulom*i)*sin(angulop*(j + 1));
			v2[1] = radio * cos(angulop*(j + 1));
			v2[2] = radio * sin(angulom*i)*sin(angulop*(j + 1));

			v3[0] = radio * cos(angulom*(i + 1))*sin(angulop*(j + 1));
			v3[1] = radio * cos(angulop*(j + 1));
			v3[2] = radio * sin(angulom*(i + 1))*sin(angulop*(j + 1));

			v4[0] = radio * cos(angulom*(i + 1))*sin(angulop*j);
			v4[1] = radio * cos(angulop*j);
			v4[2] = radio * sin(angulom*(i + 1))*sin(angulop*j);

			glBegin(GL_POLYGON);
			glNormal3fv(v1);
			glTexCoord2f(ctext_s*i, -ctext_t * j);
			glVertex3fv(v1);
			glNormal3fv(v2);
			glTexCoord2f(ctext_s*i, -ctext_t * (j + 1));
			glVertex3fv(v2);
			glNormal3fv(v3);
			glTexCoord2f(ctext_s*(i + 1), -ctext_t * (j + 1));
			glVertex3fv(v3);
			glNormal3fv(v4);
			glTexCoord2f(ctext_s*(i + 1), -ctext_t * j);
			glVertex3fv(v4);
			glEnd();
		}
	}
	glPopMatrix();

	traslacion[planeta] += velocidad[planeta];
}

void cilindro(float radio, float altura, int resolucion, GLuint text)
{

	float v1[] = { 0.0, 0.0, 0.0 };
	float v2[] = { 0.0, 0.0, 0.0 };
	float v3[] = { 0.0, 0.0, 0.0 };
	float v4[] = { 0.0, 0.0, 0.0 };
	float v5[] = { 0.0, 0.0, 0.0 };

	float angulo = 2 * 3.14 / resolucion;

	//float ctext_s = 1/resolucion-1;
	float ctext_s = 1.0 / resolucion;
	float ctext_t = 0.0;


	for (int i = 0; i < resolucion; i++)
	{

		v2[0] = radio * cos(angulo*i);
		v2[1] = 0;
		v2[2] = radio * sin(angulo*i);

		v3[0] = radio * cos(angulo*(i + 1));
		v3[1] = 0;
		v3[2] = radio * sin(angulo*(i + 1));

		v4[0] = radio * cos(angulo*i);
		v4[1] = altura;
		v4[2] = radio * sin(angulo*i);

		v5[0] = radio * cos(angulo*(i + 1));
		v5[1] = altura;
		v5[2] = radio * sin(angulo*(i + 1));

		glBegin(GL_POLYGON);
		glNormal3f(0.0f, -1.0f, 0.0f);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3fv(v2);
		glVertex3fv(v3);
		glEnd();

		glBegin(GL_POLYGON);
		glNormal3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.0, altura, 0.0);
		glVertex3fv(v4);
		glVertex3fv(v5);
		glEnd();

		glBindTexture(GL_TEXTURE_2D, text);
		glBegin(GL_POLYGON);
		glNormal3f(v2[0], 0.0f, v2[2]);
		glTexCoord2f(ctext_s*i, 0.0f);		glVertex3fv(v2);
		glTexCoord2f(ctext_s*(i + 1), 0.0f);	glVertex3fv(v3);
		glTexCoord2f(ctext_s*(i + 1), 1.0f);	glVertex3fv(v5);
		glTexCoord2f(ctext_s*i, 1.0f);		glVertex3fv(v4);
		glEnd();
	}
}

void esfera(GLfloat radio, int meridianos, int paralelos, GLuint text)
{
	GLdouble theta, phi;

	float ctext_s = 1.0 / meridianos;
	float ctext_t = 1.0 / paralelos;

	glBindTexture(GL_TEXTURE_2D, text);   // choose the texture to use.

	float v1[] = { 0.0, 0.0, 0.0 };
	float v2[] = { 0.0, 0.0, 0.0 };
	float v3[] = { 0.0, 0.0, 0.0 };
	float v4[] = { 0.0, 0.0, 0.0 };
	int i, j;
	float angulom, angulop;
	angulom = 2 * 3.141592654 / meridianos;
	angulop = 3.141592654 / paralelos;
	for (i = 0; i < meridianos; i++)
	{
		for (j = 0; j < paralelos; j++)
		{
			v1[0] = radio * cos(angulom*i)*sin(angulop*j);
			v1[1] = radio * cos(angulop*j);
			v1[2] = radio * sin(angulom*i)*sin(angulop*j);

			v2[0] = radio * cos(angulom*i)*sin(angulop*(j + 1));
			v2[1] = radio * cos(angulop*(j + 1));
			v2[2] = radio * sin(angulom*i)*sin(angulop*(j + 1));

			v3[0] = radio * cos(angulom*(i + 1))*sin(angulop*(j + 1));
			v3[1] = radio * cos(angulop*(j + 1));
			v3[2] = radio * sin(angulom*(i + 1))*sin(angulop*(j + 1));

			v4[0] = radio * cos(angulom*(i + 1))*sin(angulop*j);
			v4[1] = radio * cos(angulop*j);
			v4[2] = radio * sin(angulom*(i + 1))*sin(angulop*j);

			glBegin(GL_POLYGON);
			glNormal3fv(v1);
			glTexCoord2f(ctext_s*i, -ctext_t * j);
			glVertex3fv(v1);
			glNormal3fv(v2);
			glTexCoord2f(ctext_s*i, -ctext_t * (j + 1));
			glVertex3fv(v2);
			glNormal3fv(v3);
			glTexCoord2f(ctext_s*(i + 1), -ctext_t * (j + 1));
			glVertex3fv(v3);
			glNormal3fv(v4);
			glTexCoord2f(ctext_s*(i + 1), -ctext_t * j);
			glVertex3fv(v4);
			glEnd();
		}
	}
}

void prisma(float altura, float largo, float profundidad, GLuint text)  //Funcion creacion prisma
{

	GLfloat vertice[8][3] = {
				{0.5*largo ,-0.5*altura, 0.5*profundidad},    //Coordenadas Vértice 1 V1
				{-0.5*largo ,-0.5*altura , 0.5*profundidad},    //Coordenadas Vértice 2 V2
				{-0.5*largo ,-0.5*altura , -0.5*profundidad},    //Coordenadas Vértice 3 V3
				{0.5*largo ,-0.5*altura , -0.5*profundidad},    //Coordenadas Vértice 4 V4
				{0.5*largo ,0.5*altura , 0.5*profundidad},    //Coordenadas Vértice 5 V5
				{0.5*largo ,0.5*altura , -0.5*profundidad},    //Coordenadas Vértice 6 V6
				{-0.5*largo ,0.5*altura , -0.5*profundidad},    //Coordenadas Vértice 7 V7
				{-0.5*largo ,0.5*altura , 0.5*profundidad},    //Coordenadas Vértice 8 V8
	};

	glBindTexture(GL_TEXTURE_2D, text);   // choose the texture to use.
	//glBindTexture(GL_TEXTURE_2D, texture[filter]);   // choose the texture to use.
	glBegin(GL_POLYGON);	//Front
		//glColor3f(0.0,0.0,1.0);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[0]);
	glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertice[4]);
	glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertice[7]);
	glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertice[1]);
	glEnd();

	glBegin(GL_POLYGON);	//Right
		//glColor3f(0.0,0.0,1.0);
	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[0]);
	glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertice[3]);
	glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertice[5]);
	glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertice[4]);
	glEnd();

	glBegin(GL_POLYGON);	//Back
		//glColor3f(0.0,1.0,0.0);
	glNormal3f(0.0f, 0.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertice[6]);
	glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertice[5]);
	glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertice[3]);
	glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[2]);
	glEnd();

	glBegin(GL_POLYGON);  //Left
		//glColor3f(1.0,1.0,1.0);
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertice[1]);
	glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertice[7]);
	glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertice[6]);
	glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[2]);
	glEnd();

	glBegin(GL_POLYGON);  //Bottom
		//glColor3f(0.4,0.2,0.6);
	glNormal3f(0.0f, -1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[0]);
	glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertice[1]);
	glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertice[2]);
	glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertice[3]);
	glEnd();

	glBegin(GL_POLYGON);  //Top
		//glColor3f(0.8,0.2,0.4);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[4]);
	glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertice[5]);
	glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertice[6]);
	glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertice[7]);
	glEnd();
}

void uss()
{
	glPushMatrix();
		glDisable(GL_LIGHTING);
		//glRotatef(90,0,-1,0);
		glTranslatef(0, 3, 0);
		cilindro(7.5, 0.3, 80, uss1.GLindex);
		glPushMatrix();
			glTranslatef(0, 0.3, 0);
			cilindro(7.3, 0.3, 80, uss1.GLindex);
			glTranslatef(0, 0.35, 0);
			cilindro(5.5, 0.2, 80, uss2.GLindex);
			glTranslatef(0, 0.175, 0);
			cilindro(2.5, 0.15, 80, uss1.GLindex);
			glTranslatef(0, 0.175, 0);
			cilindro(1.5, 0.2, 80, uss2.GLindex);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0, -0.3, 0);
			cilindro(7.3, 0.3, 80, uss1.GLindex);
			glTranslatef(0, -0.25, 0);
			cilindro(5.5, 0.2, 80, uss2.GLindex);
			glTranslatef(0, -0.175, 0);
			cilindro(2.5, 0.15, 80, uss1.GLindex);
			glTranslatef(0, -0.175, 0);
			cilindro(1.5, 0.2, 80, uss2.GLindex);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(4, -2.0, 0);
			glRotatef(45, 0, 0, -1);
			prisma(2, 6, 1, uss3.GLindex);
			glRotatef(45, 0, 0, -1);
			glTranslatef(2.5, -2.0, 0);
			cilindro(1.2, 10, 80, uss1.GLindex);
			esfera(1.2, 80, 80, uss5.GLindex);
			glPushMatrix();
				glTranslatef(-3, 7.6, 2);
				glRotatef(20, 0, 1, 0);
				prisma(1, 6, 0.5, uss3.GLindex);
				glRotatef(20, 0, -1, 0);
				glTranslatef(-3, -2.5, 1);
				cilindro(0.5, 7, 80, uss1.GLindex);
				esfera(0.5, 80, 80, uss6.GLindex);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(-3, 7.6, -2);
				glRotatef(20, 0, -1, 0);
				prisma(1, 6, 0.5, uss3.GLindex);
				glRotatef(20, 0, -1, 0);
				glTranslatef(-3, -2.5, 1);
				cilindro(0.5, 7, 80, uss1.GLindex);
				esfera(0.5, 80, 80, uss6.GLindex);
			glPopMatrix();
		glPopMatrix();
		glEnable(GL_LIGHTING);
	glPopMatrix();
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glPushMatrix();

	if (p) 
	{
		camaraT();
	}
	else
	{
		camaraP();
	}

	


	glTranslatef(0.0, 0.0, -250.0);			//camara

	glPushMatrix();
		glRotatef(-tierraT, 0.0, 1.0, 0.0);
		glTranslatef(135,-10,-5);
		glScalef(0.5, 0.5, 0.5);
		glRotatef(-lunaT, 0.0, 1.0, 0.0);
		uss();
	glPopMatrix();

	glPushMatrix();
		glRotatef(-tierraT, 0.0, 1.0, 0.0);
		glDisable(GL_COLOR_MATERIAL);
		glTranslatef(163,0,0);
		glScalef(0.03,0.03,0.03);
		glRotatef(180,0,1,0);
		glRotatef(-lunaT, 0.0, 1.0, 1.0);
		spaceman.GLrender(NULL, _SHADED, 1.0);  //_WIRED O _POINTS
		glEnable(GL_COLOR_MATERIAL);
	glPopMatrix();

	glPushMatrix();
		glRotatef(-tierraT, 0.0, 1.0, 0.0);
		glDisable(GL_COLOR_MATERIAL);
		glTranslatef(161, 10, 5);
		glScalef(0.1, 0.1, 0.1);
		glRotatef(180, 0, 1, 1);
		glRotatef(-lunaT, 0.0, 1.0, 1.0);
		satellite1.GLrender(NULL, _SHADED, 1.0);  //_WIRED O _POINTS
		glEnable(GL_COLOR_MATERIAL);
	glPopMatrix();

	glPushMatrix();
		glRotatef(-0.8*marteT, 0.0, 1.0, 0.0);
		glDisable(GL_COLOR_MATERIAL);
		glTranslatef(180, 8, 5);
		glScalef(0.7, 0.7, 0.7);
		glRotatef(180, 0, 1, -1);
		glRotatef(-lunaT, 0.0, 1.0, 1.0);
		satellite2.GLrender(NULL, _SHADED, 1.0);  //_WIRED O _POINTS
		glEnable(GL_COLOR_MATERIAL);
	glPopMatrix();

	glPushMatrix();
		glRotatef(-jupiterT, 0.0, 1.0, 0.0);
		glDisable(GL_COLOR_MATERIAL);
		glTranslatef(210, -30, 5);
		glScalef(0.4, 0.4, 0.4);
		glRotatef(180, 0, 1, -1);
		glRotatef(-lunaT, 0.0, 1.0, 1.0);
		satellite3.GLrender(NULL, _SHADED, 1.0);  //_WIRED O _POINTS
		glEnable(GL_COLOR_MATERIAL);
	glPopMatrix();

	glPushMatrix();
		glRotatef(-0.99*mercurioT, 0.0, 1.0, 0.0);
		glDisable(GL_COLOR_MATERIAL);
		glTranslatef(90, -20, 5);
		glScalef(0.05, 0.05, 0.05);
		glRotatef(180, 0, 1, -1);
		glRotatef(-lunaT, 0.0, 1.0, 1.0);
		satellite4.GLrender(NULL, _SHADED, 1.0);  //_WIRED O _POINTS
		glEnable(GL_COLOR_MATERIAL);
	glPopMatrix();

	glPushMatrix();
		glRotatef(-jupiterT, 0.0, 1.0, 0.0);
		glDisable(GL_COLOR_MATERIAL);
		glTranslatef(240, 0, 40);
		glScalef(0.1, 0.1, 0.1);
		glRotatef(60, 0, 1, 0);
		glRotatef(-0.2*lunaT, 0.0, 1.0, 1.0);
		nave.GLrender(NULL, _SHADED, 1.0);  //_WIRED O _POINTS
		glEnable(GL_COLOR_MATERIAL);
	glPopMatrix();

	glPushMatrix();
		glRotatef(-jupiterT, 0.0, 1.0, 0.0);
		glDisable(GL_COLOR_MATERIAL);
		glTranslatef(200, 0, 5);
		glScalef(0.45, 0.45, 0.45);
		glRotatef(60, 0, 1, 0);
		glRotatef(-0.2*lunaT, 0.0, 1.0, 1.0);
		nave1.GLrender(NULL, _SHADED, 1.0);  //_WIRED O _POINTS
		glEnable(GL_COLOR_MATERIAL);
	glPopMatrix();

	glPushMatrix();
		glRotatef(-0.85*saturnoT, 0.0, 1.0, 0.0);
		glDisable(GL_COLOR_MATERIAL);
		glTranslatef(320, 20, 65);
		glScalef(0.45, 0.45, 0.45);
		glRotatef(60, 0, 1, 0);
		glRotatef(-0.2*lunaT, 0.0, 1.0, 1.0);
		nave2.GLrender(NULL, _SHADED, 1.0);  //_WIRED O _POINTS
		glEnable(GL_COLOR_MATERIAL);
	glPopMatrix();

	glPushMatrix();
		glRotatef(-1.3*tierraT, 0.0, 1.0, 0.0);
		glDisable(GL_LIGHTING);
		glTranslatef(-150, 0, 0);
		skybox(18.0, 18.0, 18.0, cubo.GLindex);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
		glDisable(GL_LIGHTING);
		glTranslatef(0, 0, 0);
		skybox(1000.0, 1000.0, 1000.0, espacio.GLindex);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
		glDisable(GL_LIGHTING);
		glRotatef(-solT, 0.0, 1.0, 0.0);
		dibujarSol(70.0, 80.0, 80.0);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
		glDisable(GL_LIGHTING);
		glRotatef(-mercurioT, 0.0, 1.0, 0.0);
		dibujarPlaneta(3.8, 80.0, 80.0, 0.0, mercurio.GLindex,90);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
		glDisable(GL_LIGHTING);		
		glRotatef(-venusT, 0.0, 1.0, 0.0);
		dibujarPlaneta(9.5,80.0,80.0,1.0,venus.GLindex,120);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
		glDisable(GL_LIGHTING);
		glRotatef(-tierraT, 0.0, 1.0, 0.0);
		dibujarPlaneta(10.0, 80.0, 80.0, 2.0, tierra.GLindex, 150);	
		glTranslatef(150, 0, 0);
		glPushMatrix();			
			glRotatef(-lunaT, 0.0, 1.0, 1.0);			
			dibujarPlaneta(2.0, 80, 80,0.0, luna.GLindex,15);
		glPopMatrix();		
		glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
		glDisable(GL_LIGHTING);
		glRotatef(-0.8*marteT, 0.0, 1.0, 0.0);
		dibujarPlaneta(5.3, 80.0, 80.0, 3.0, marte.GLindex, 180);
		glTranslatef(180, 0, 0);
		glPushMatrix();
			glRotatef(-2*lunaT, 0.0, 1.0, 1.0);
			dibujarPlaneta(1.3, 80, 80, 0.0, luna.GLindex, 8);
		glPopMatrix();
		glPushMatrix();
			glRotatef(-lunaT + 5, 0.0, 0.0, -1.0);
			dibujarPlaneta(1.4, 80, 80, 0.0, luna.GLindex, 8);
		glPopMatrix();
		glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
		glDisable(GL_LIGHTING);
		glRotatef(-jupiterT, 0.0, 1.0, 0.0);
		dibujarPlaneta(27.0 , 80.0, 80.0, 4.0, jupiter.GLindex, 240);
		glTranslatef(240, 0, 0);
		glPushMatrix();
			glRotatef(-2 * lunaT, 0.0, 1.0, -1.0);
			dibujarPlaneta(1.3, 80, 80, 0.0, luna.GLindex, 30);
		glPopMatrix();
		glPushMatrix();
			glRotatef(-2*lunaT + 5, 0.0, 1.0, 0.0);
			dibujarPlaneta(1.4, 80, 80, 0.0, luna.GLindex, 32);
		glPopMatrix();
		glPushMatrix();
			glRotatef(-2*lunaT + 7, 0.0, 0.0, 1.0);
			dibujarPlaneta(1.8, 80, 80, 0.0, luna.GLindex, 35);
		glPopMatrix();
		glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
		glDisable(GL_LIGHTING);
		glRotatef(-0.8*saturnoT, 0.0, 1.0, 0.0);
		dibujarPlaneta(17.0, 80.0, 80.0, 5.0, saturno.GLindex, 300);
		glEnable(GL_LIGHTING);
		glPushMatrix();
			glDisable(GL_LIGHTING);
			glTranslatef(300, 0, 0);
			glRotatef(traslacion[5], 1.0, 1.0, 1.0);
			glutSolidTorus(3.0, 25.0, 80.0, 80.0);
			glEnable(GL_LIGHTING);
		glPopMatrix();
		glPushMatrix();
			glDisable(GL_LIGHTING);
			glTranslatef(300, 0, 0);
			glPushMatrix();
			glRotatef(-2 * lunaT, 0.0, -1.0, 1.0);
			dibujarPlaneta(1.3, 80, 80, 0.0, luna.GLindex, 20);
			glPopMatrix();
			glPushMatrix();
			glRotatef(-lunaT + 5, 0.0, 1.0, 0.0);
			dibujarPlaneta(1.4, 80, 80, 0.0, luna.GLindex, 21);
			glPopMatrix();
			glPushMatrix();
			glRotatef(-lunaT + 7, 0.0, 0.0, 1.0);
			dibujarPlaneta(1.8, 80, 80, 0.0, luna.GLindex, 19);
			glPopMatrix();
			glEnable(GL_LIGHTING);
		glPopMatrix();

	glPopMatrix();

	glPushMatrix();
		glDisable(GL_LIGHTING);
		glRotatef(-uranoT*0.9, 0.0, 1.0, 0.0);
		dibujarPlaneta(13.0, 80.0, 80.0, 4.0, urano.GLindex, 360);
		glTranslatef(360, 0, 0);
		glPushMatrix();
			glRotatef(-2 * lunaT, 0.0, 1.0, 1.0);
			dibujarPlaneta(1.3, 80, 80, 0.0, luna.GLindex, 15);
			glPopMatrix();
			glPushMatrix();
			glRotatef(-2 * lunaT + 5, 0.0, 1.0, 0.0);
			dibujarPlaneta(1.4, 80, 80, 0.0, luna.GLindex, 17);
			glPopMatrix();
			glPushMatrix();
			glRotatef(-2 * lunaT + 7, 0.0, 0.0, -1.0);
			dibujarPlaneta(1.8, 80, 80, 0.0, luna.GLindex, 18);
		glPopMatrix();
		glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
		glDisable(GL_LIGHTING);
		glRotatef(-0.7*neptunoT, 0.0, 1.0, 0.0);
		dibujarPlaneta(13.0, 80.0, 80.0, 4.0, neptuno.GLindex, 400);
		glTranslatef(400, 0, 0);
		glPushMatrix();
			glRotatef(-2 * lunaT, 0.0, -1.0, 1.0);
			dibujarPlaneta(1.3, 80, 80, 0.0, luna.GLindex, 15);
			glPopMatrix();
			glPushMatrix();
			glRotatef(-2 * lunaT + 5, 0.0, -1.0, 0.0);
			dibujarPlaneta(1.4, 80, 80, 0.0, luna.GLindex, 17);
			glPopMatrix();
			glPushMatrix();
			glRotatef(-2 * lunaT + 7, 0.0, 0.0, 1.0);
			dibujarPlaneta(1.8, 80, 80, 0.0, luna.GLindex, 18);
		glPopMatrix();
		glEnable(GL_LIGHTING);
	glPopMatrix();
	
glPopMatrix();

	//glFlush();
	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (GLfloat)w / (GLfloat)h, 0.2, 1000.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 100.0, 500.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) 
	{
		case 27:
			exit(0);
			break;
		case 'w':   //Movimientos de camara
		case 'W':
			objCamera.Move_Camera(CAMERASPEED + 10);
			break;

		case 's':
		case 'S':
			objCamera.Move_Camera(-(CAMERASPEED + 10));
			break;

		case 'a':
		case 'A':
			objCamera.Strafe_Camera(-(CAMERASPEED + 10));
			break;

		case 'd':
		case 'D':
			objCamera.Strafe_Camera(CAMERASPEED + 10);
			break;
		case 'p':
		case 'P':
			p ^= true;
			break;
		case 'o':
		case 'O':
			o ^= true;
			PlaySound(TEXT("imperial.WAV"), NULL, SND_LOOP | SND_ASYNC);
			break;
		case 'i':
		case 'I':
			PlaySound(NULL, NULL, 0);
			break;
		case 'q':
		case 'Q':
			PlaySound(TEXT("Explosion.WAV"), NULL, SND_LOOP | SND_ASYNC);
			break;
		case 'e':
		case 'E':
			PlaySound(TEXT("Torpedo.WAV"), NULL, SND_LOOP | SND_ASYNC);
			break;
	}
}

void arrow_keys(int a_keys, int x, int y)  // Funcion para manejo de teclas especiales (arrow keys)
{
	switch (a_keys) {
	case GLUT_KEY_PAGE_UP:
		objCamera.UpDown_Camera(CAMERASPEED*5);
		break;

	case GLUT_KEY_PAGE_DOWN:
		objCamera.UpDown_Camera(-CAMERASPEED*5);
		break;

	default:
		break;
	}
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Proyecto");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(arrow_keys);	//Otras
	glutIdleFunc( timerFunction);
	glutMainLoop();
	return 0;
}
