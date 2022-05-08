#include <cmath>
#include <GL/glut.h>
#include <stdlib.h>
#include <cstdio>
#include <string>


// Obsluga wywolan zwrotnych, do stworzenia 3d
static void resize(int szerokosc, int wysokosc)
{
	const float ar = (float)szerokosc / (float)wysokosc;

	glViewport(0, 0, szerokosc, wysokosc);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);//Mnozenie macierzy przez macierz perspektywiczna, powstanie wymiaru 3D
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

//Klasa planet zawierajaca wszystkie niezbedne zmienne dla planety
class Planet {
public:
	std::string name = "";
	double x = 0;
	double y = 0;
	double r = 0;
	double g = 0;
	double b = 0;
	double f = 0;
	double a = 0;
	double s1 = 0;

	Planet(std::string, double, double, double, double, double, double);
	void glStuff(double k,double trojkaty,double t, double closeness);
	
};

//Konstruktor planety
Planet::Planet(std::string name = "", double r = 0, double g = 0, double b = 0, double f = 0, double a = 0, double s1 = 0) {
	this->name = name;
	this->x = 0; //wspolrzedna x
	this->y = 0; //wspolrzedna y
	this->r = r; //kolor
	this->g = g; //kolor
	this->b = b; //kolor
	this->f = f; //predkosc
	this->a = a; //odleglosc
	this->s1 = s1; //wielkosc
}

//wylicznie pozycji planet
void Planet::glStuff(double k,double trojkaty, double t, double closeness) {
	x = sin(k*t * f) * a * 1.5; 
	y = cos(k*t * f) * a * 1.5;

	glColor3d(r, g, b);
	glPushMatrix();
	glTranslated(x, y, closeness);
	glRotated(50.0 * t, 0, 0, 1);
	glutSolidSphere(s1, trojkaty, trojkaty);
	glPopMatrix();
}

static double closeness = -15.0;
Planet** planets;

//wspolrzedne ksiezycow i pierscieni (x i y)

double moon_x;
double moon_y; 

double ringx;
double ringy;

double ganymede_x; 
double ganymede_y; 

double europa_x; 
double europa_y; 

double io_x;
double io_y; 

double callisto_x; 
double callisto_y; 
static double t; 
double k = 1.0;
int trojkaty = 80;

static void display(void) 
{
	t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (int i = 0; i < 10; i++) {
		(*planets[i]).glStuff(k,trojkaty,t, closeness);
	}


	// ring
	ringx =planets[6]->x;
	ringy= planets[6]->y;
	
	glColor3d(1, 1, 0.8);
	glPushMatrix();
	glTranslated(ringx, ringy, closeness);
	gluOrtho2D(-0.7, 0.7, -1.2, 1.2);
	glutSolidSphere(0.8, 80, 80);
	glPopMatrix();


	//ksiezyc ziemii
	moon_x = -sin(t) + planets[3]->x;
	moon_y = cos(t) + planets[3]->y;

	glColor3d(0.7, 0.7, 0.7);
	glPushMatrix();
	glTranslated(moon_x, moon_y, closeness);
	glRotated(60, 1, 0, 0);
	glRotated(80.0 * t, 0, 0, 1);
	glutSolidSphere(0.05, 20, 20);
	glPopMatrix();
	//ksiezyce Jowisza
	
	ganymede_x = -sin(t+3)*1.3 + planets[5]->x;
	ganymede_y = cos(t+2)*1.3 + planets[5]->y;
	glColor3d(0.7, 0.7, 0.7);
	glPushMatrix();
	glTranslated(ganymede_x, ganymede_y, closeness);
	glRotated(60, 1, 0, 0);
	glRotated(20.0 * t, 0, 0, 1);
	glutSolidSphere(0.10, 20, 20);
	glPopMatrix();


	europa_x = -sin(t+7)*1.1 + planets[5]->x;
	europa_y = cos(t+6.5)*1.1 + planets[5]->y;
	glColor3d(0.9, 0.45, 0.0);
	glPushMatrix();
	glTranslated(europa_x, europa_y, closeness);
	glRotated(60, 1, 0, 0);
	glRotated(30.0 * t, 0, 0, 1);
	glutSolidSphere(0.12, 20, 20);
	glPopMatrix();
	

	io_x = -sin(t+4)*1.7 + planets[5]->x;
	io_y = cos(t+4)*1.7 + planets[5]->y;
	glColor3d(0.9, 0.9, 0.2);
	glPushMatrix();
	glTranslated(io_x, io_y, closeness);
	glRotated(60, 1, 0, 0);
	glRotated(50.0 * t, 0, 0, 1);
	glutSolidSphere(0.2, 20, 20);
	glPopMatrix();


	callisto_x = -sin(t) + planets[5]->x ;
	callisto_y = cos(t) + planets[5]->y ;
	glColor3d(0.7, 0.7, 0.7);
	glPushMatrix();
	glTranslated(callisto_x, callisto_y, closeness);
	glRotated(60, 1, 0, 0);
	glRotated(50.0 * t, 0, 0, 1);
	glutSolidSphere(0.22, 20, 20);
	glPopMatrix();
	glutSwapBuffers();
}

static void key(unsigned char key, int x, int y)
{
	switch (key)
	{
	//zoom
	case 'q':
		exit(0);
		break;
	case '+':
		if (closeness < -4.0) 
		{
			closeness += 0.5;
		}
		break;
	case '-':
		closeness -= 0.5;
		break;
	//predkosc orbitowania
	case '0':
		k = 0.0;
		break;
	case '1':
		k += 0.01;
		break;
	case '2':
		k -= 0.01;
		break;
	//gladkosc planet
	case 't':
		trojkaty += 10;
		break;
	case 'y':
		if (trojkaty > 10) 
		{
			trojkaty -= 10;
		}
		break;
	}
	glutPostRedisplay();
}

static void idle(void)
{
	glutPostRedisplay();
}



int main(int argc, char* argv[])
{
	planets = new Planet * [9];
	Planet q("sun", 1.0, 0.8, 0.1, 0.0, 0.0, 1.5);   planets[0] = &q;
	Planet a("mercury", 0.5, 0.4, 0.4, 1.0, 2.0, 0.15);  planets[1] = &a;
	Planet s("venus", 0.6, 0.6, 0.2, 0.5, 3.0, 0.18);  planets[2] = &s;
	Planet d("earth", 0.0, 0.0, 0.7, 0.2, 4.0, 0.2);   planets[3] = &d;
	Planet f("mars", 1.0, 0.2, 0.0, 0.15, 5.5, 0.15); planets[4] = &f;
	Planet z("jupiter", 0.8, 0.6, 0.3, 0.12, 7.0, 0.5);  planets[5] = &z;
	Planet x("saturn", 0.9, 0.8, 0.3, 0.1, 10.0, 0.4); planets[6] = &x;
	Planet c("uranus", 0.4, 0.4, 1.0, 0.08, 13.0, 0.30); planets[7] = &c;
	Planet v("neptune", 0.0, 0.0, 0.5, 0.05, 17.0, 0.3); planets[8] = &v;
	Planet b("pluton", 0.1, 1.0, 1.5, 0.09, 25.0, 0.3); planets[9] = &b;
	

	glutInit(&argc, argv);
	glutInitWindowSize(1100, 600);
	glutInitWindowPosition(100, 20);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

	glutCreateWindow("TripleS");

	glutReshapeFunc(resize);
	glutDisplayFunc(display);
	glutKeyboardFunc(key);
	glutIdleFunc(idle);

	glClearColor(0, 0, 0, 0);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);



	glutMainLoop();

	return EXIT_SUCCESS;
}
