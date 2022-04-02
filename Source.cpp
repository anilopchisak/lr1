#include <GL/freeglut.h> //GLUT - OpenGL Utility Library

void RenderSceneCB()
{
	glClear(GL_COLOR_BUFFER_BIT); //clearing the frame buffer using the color specified above
	glutSwapBuffers(); //swap the background buffer and the frame buffer
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv); //initialize glut

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); //glut setup

	glutInitWindowSize(1024, 768); //window parameters
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Tutorial 01"); //title of the window

	glutDisplayFunc(RenderSceneCB); //work in the window system

	glClearColor(1.0f, 0.0f, 1.0f, 0.0f); //setting the color

	glutMainLoop(); //transferring conrol to GLUT, it's waiting for events in the window

	return 0;
}



