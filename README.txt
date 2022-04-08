OpenGL, a programming interface for writing applications using two–dimensional and three–dimensional computer graphics, 
does not have its own API (application programming interface) for creating and managing a window.

Code description:

1. #include <GL/glew.h>
OpenGL Extension Wrangler Library or GLEW – managing extensions in OpenGL. After initialization, 
it polls all extensions available on the platform, dynamically loading them and provides easy access 
through a single header file.


2. #include <GL/freeglut.h>
OpenGL utility library', or GLUT for short, is the simplest API for managing a window system, as well as 
event handling, input/output control and several other features.


3. #include <glm/glm.hpp>
It is a header only C++ mathematics library for graphics software based on the OpenGL Shading Language (GLSL) specifications. 
GLM provides classes and functions designed and implemented with the same naming conventions and functionalities than GLSL.
Provides extended capabilities: matrix transformations, quaternions, data packing, random numbers, noise, etc...


4. GLuint VBO;
VBO – vertex buffers, used to store vertices.
GLuint is a global variable for storing a pointer to a vertex buffer. 
(almost all OpenGL objects are accessible via a GLuint type variable.)


5. GLUT initialization.

	glutInit(&argc, argv); 
The first parameter is a pointer to the number of arguments on the command line, and the second is a pointer to 
an array of arguments. The values are taken from the main function of the program: int main(int argc, char **argv).


6. Setting the window parameters. These functions set the parameters of the window and create it.

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
Sets the information display mode for the window, i.e. sets parameters for the window such as: the color 
model used, the number of different buffers, etc.

	GLUT_DOUBLE
Output to the window is carried out using 2 buffers. The rendering will take place in the background buffer while 
another buffer is being displayed. It is used for animation to eliminate the flicker effect.

	GLUT_RGBA
Color buffer. 3 RGB color components are used to display graphical information.
(continuously used for the final rendering purpose (i.e. on screen))

	glutInitWindowSize(1024, 768); 
The first parameter width is the width of the window in pixels, the second height is the height of the window 
in pixels. I also note that if this command is omitted, GLUT will set the default window size itself, usually 300x300.

	glutInitWindowPosition(100, 100); 
You can set the position of the window being created relative to the upper-left corner of the screen. 


7. Creating a window.

	glutCreateWindow("Tutorial 01"); 
This command creates a window with a header that is specified as a parameter and returns the window handler as 
an int number. This handler is usually used for subsequent operations on this window, such as changing 
window parameters and closing the window.


8. Installation of functions responsible for drawing in the window and changing the shape of the window.
After the window into which graphical information will be displayed is prepared and created, it is necessary 
to associate with it procedures that will be responsible for displaying graphical information, monitor the size of 
the window, monitor keystrokes, etc. 

	glutDisplayFunc(RenderSceneCB); 
The function that is responsible for drawing. Called by the operating system to draw (redraw) the contents of the window. 
The only parameter of this function is a pointer to the function that will be responsible for drawing in the window (RenderSceneCB).


9. void RenderSceneCB() – here the scene is rendered and rendered

	a) glClear(GL_COLOR_BUFFER_BIT);
Clearing the screen with the color we defined above (i.e. clearing the frame buffer).

	b) glEnableVertexAttribArray(0);
Enable or disable a generic vertex attribute array. If enabled, the values in the generic vertex attribute array 
will be accessed and used for rendering when calls are made to vertex array commands such as glDrawArrays or glDrawElements.

	c) glBindBuffer(GL_ARRAY_BUFFER, VBO);
We bind the buffer, prepare it for rendering. 

	d) glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
This call tells the pipeline how to perceive the data inside the buffer. 
- The first parameter indicates the attribute index. 
- The second parameter is the number of components in the attribute (3 for X, Y and Z). 
- The third parameter is the data type for each component. 
- The next one is whether we want to normalize the attributes before using them in the pipeline. In our case, we want the data 
  to be transmitted not by name. 
- The fifth parameter (called "step") is the number of bytes between 2 instances of the attribute. Since we store only one 
  attribute (for example, the buffer stores only vertex coordinates) and the data is tightly packed, we pass a null value.
- The last parameter is useful in the case of the previous example. We need to specify the offset in the structure that our 
  pipeline will receive.

	e) glDrawArrays(GL_POINTS, 0, 1); and glDrawArrays(GL_TRIANGLES, 0, 3);
Function for rendering. The GPU combines the rendering parameters and what was drawn earlier and displays the result on the screen. 
The function is ordinal. The GPU bypasses the vertex buffer by passing through the vertices one by one and interprets them according 
to the type specified in the function call.
The first parameter is what is being drawn. The second parameter is the index of the first vertex to draw. The last parameter is the number 
of vertices to draw.

	f) glDisableVertexAttribArray(0);
Disabling each vertex attribute as soon as it is no longer necessary. 

	g) glutSwapBuffers();
The function asks GLUT to swap the background buffer and the frame buffer. In the next call, the render will occur in the current frame 
buffer, and the background buffer will be displayed.


6. glClearColor(0.0f,0.0f,1.0f,0.0f) 
Clearing the screen and then painting it purple.


7.	GLenum res = glewInit();
	if (res != GLEW_OK)
	{
		fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
		return 1;
	}

Initialize GLEW and check for errors.

8. Creating an array of vertices for a point and a triangle, respectively.

	glm::vec3 Vertices[1]; 
	Vertices[0] = glm::vec3(0.0f, 0.0f, 0.0f); //setting XYZ by zeros – a dot in the middle of the screen

	glm::vec3 Vertices[3]; 
	Vertices[0] = glm::vec3(-1.0f, -1.0f, 0.0f); // down left
	Vertices[1] = glm::vec3(1.0f, -1.0f, 0.0f); // down right
	Vertices[2] = glm::vec3(0.0f, 1.0f, 0.0f); // up


9. glGenBuffers(1, &VBO);
The glGen* functions are needed to generate objects of variable types. The first parameter determines the number of objects 
that we want to create, and the second is a reference to an array of GLuints type to store a pointer by which data will be stored.


10. glBindBuffer(GL_ARRAY_BUFFER, VBO);
We bind the pointer to the name of the target and then run the command on the target. These commands restrict changes to 
a value by pointer until another one is restricted instead, or the call takes 0 as a pointer. 
The GL_ARRAY_BUFFER parameter means that the buffer will store an array of vertices. You can specify another 
parameter GL_ELEMENT_ARRAY_BUFFER, it shows that the vertex indexes are stored in a different buffer.


11. glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
Filling the object with data. The call above takes the name of the target (the same as when binding), the size of the data 
in bytes, the address of the vertex array, and a flag that indicates the use of patterns for this data. Since we are not going 
to change the buffer values, we specify GL_STATIC_DRAW. 


12. Entering the main GLUT cycle.
	glutMainLoop();
To run our program is to enter the so—called main GLUT cycle. This cycle provides the relationship between the operating system 
and those functions that are responsible for the window, receive information from input/output devices.
