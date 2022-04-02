#define MATH_3D_IMPLEMENTATION
#define MATH_3D_HEADER
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h> //GLUT - OpenGL Utility Library
#include <glm/glm.hpp>		//#include "math_3d.h" - vector

GLuint VBO;

void RenderSceneCB()
{
	glClear(GL_COLOR_BUFFER_BIT); //clearing the frame buffer using the color specified above
	
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//glDrawArrays(GL_POINTS, 0, 1);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDisableVertexAttribArray(0);

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


	//initialize GLEW and check for errors
	GLenum res = glewInit();
	if (res != GLEW_OK)
	{
		fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
		return 1;
	}

	//glm::vec3 Vertices[1];
	//Vertices[0] = glm::vec3(0.0f, 0.0f, 0.0f);

	glm::vec3 Vertices[3];
	Vertices[0] = glm::vec3(-1.0f, -1.0f, 0.0f);
	Vertices[1] = glm::vec3(1.0f, -1.0f, 0.0f);
	Vertices[2] = glm::vec3(0.0f, 1.0f, 0.0f);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

	glutMainLoop(); //transferring conrol to GLUT, it's waiting for events in the window

	return 0;
}