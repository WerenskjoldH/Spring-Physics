#define _CRT_SECURE_NO_WARNINGS

// Every _1_ second(s) we calculate fps
#define TIME_CHUNK 1

#include <ctime>
#include <iostream>
#include <GL\glut.h>

#include "stdio.h"
#include "stdlib.h"

#include "solver.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT WINDOW_WIDTH
/// Main Program Variables ///

char *window_title;

float window_width = WINDOW_WIDTH;
float window_height = WINDOW_HEIGHT;

// Paused at start
int simPause = 1;
int drawCells = 1;

rn::vector3f mousePos;

Solver* solver;

/// FPS Counter Variables ///
std::clock_t last_time = clock();
unsigned int frames_rendered = 0;


void init()
{
	solver = new Solver();
	solver->initialize();

	// Initial Setup
	for(int x = 0; x < NUMBER_OF_SEGMENTS; x++)
		solver->addParticle(rn::vector3f((solver->worldSize_width/2.f), 0.9 - x * REST_LENGTH));

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, solver->worldSize_width, 0.0, solver->worldSize_height);

	window_title = (char*)malloc(sizeof(char) * 50);

	glutIgnoreKeyRepeat(false);

	std::cout << "Simulation is paused - Press 'space' to unpause" << std::endl;
}

void render()
{

	// Set state values for particles
	glColor3f(0, 0, 0);
	glPointSize(10.f);

	for (int x = 0; x < solver->numParticles; x++)
	{
		// Draw
		glBegin(GL_POINTS);
		glVertex2d(solver->particles[x]->position.x, solver->particles[x]->position.y);
		glEnd();
	}

}

void display()
{
	glViewport(0, 0, window_width, window_height);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glEnable(GL_POINT_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);

	glClearColor(1.0f, 1.0f, 1.0f, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0f, 0.0f, 1.0f);


	if (simPause == 0)
		solver->update();


	render();

	glutSwapBuffers();


	if ((clock() - last_time) / CLOCKS_PER_SEC >= TIME_CHUNK)
	{
		memset(window_title, 0, 50);
		sprintf(window_title, "SPH Solver - Hunter Werenskjold - FPS: %d", frames_rendered / TIME_CHUNK);
		glutSetWindowTitle(window_title);

		frames_rendered = 0;
		last_time = clock();
	}
	frames_rendered++;

}

// Redisplays the window's normal plane
void idle()
{
	glutPostRedisplay();
}

// Prevents reshaping of the window
void reshape(int width, int height) {
	glutReshapeWindow(window_width, window_height);
}

// Processes keyboard inputs
void process_keyboard(unsigned char key, int x, int y)
{
	if (key == ' ')
	{
		simPause = 1 - simPause;

		if (simPause)
			std::cout << "PAUSED" << std::endl;
		else
			std::cout << "UNPAUSED" << std::endl;
	}

	if(key == 'x')
		solver->addParticle(rn::vector3f((mousePos.x / window_width) * solver->worldSize_width, (((-1 * mousePos.y + window_height) / window_height)) * solver->worldSize_height));

}

// Processes passive mouse movements
void process_mouse_movement(int x, int y)
{
	mousePos.x = x;
	mousePos.y = y;
}

// Processes mouse inputs
void process_mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		Particle* p = solver->particles[solver->numParticles-1];
		p->acceleration += (p->position - rn::vector3f((mousePos.x / window_width) * solver->worldSize_width, (((-1 * mousePos.y + window_height) / window_height)) * solver->worldSize_height)).unit() * -100.f;
	}

	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		solver->cleanup();
	}

}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(window_width, window_height);
	glutCreateWindow("SPH Solver - Hunter Werenskjold - FPS: ");

	init();
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutKeyboardFunc(process_keyboard);
	glutPassiveMotionFunc(process_mouse_movement);
	glutMouseFunc(process_mouse);
	glutMainLoop();

	return 0;
}
