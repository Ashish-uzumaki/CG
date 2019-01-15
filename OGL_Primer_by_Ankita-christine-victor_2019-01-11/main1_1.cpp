#include <bits/stdc++.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace std;

#define cout(a) cout<<a<<endl

#define clamp(x, lower, upper) (min(upper, max(x, lower)))

// IDs
float scale = 1.0, x = 0.0, y = 0.0;
const int numPoints = 50000;

GLfloat points[3 * numPoints];

void createSierpinskiGasket()
{
	GLfloat vertices[] = {
		-1.0f, -1.0f, 0.0f,
		 0.0f,  1.0f, 0.0f,
		 1.0f, -1.0f, 0.0f
	};

	points[0] = 0.25f; points[1] = 0.50f; points[2] = 0.0f;

	for(int i = 3; i < numPoints * 3; i += 3)
	{
		int j = rand() % 3;
		points[i] = (points[i - 3] + vertices[j * 3]) / 2.0;
		points[i + 1] = (points[i - 2] + vertices[j * 3 + 1]) / 2.0;
		points[i + 2] = (points[i - 1] + vertices[j * 3 + 2]) / 2.0;
	}
}

void drawSierpinskiGasket()
{
	glLoadIdentity();//load identity matrix

    glTranslatef(x, y, 0);//move forward 4 units
    glScalef(scale, scale, scale);

	glBegin(GL_POINTS);

	for(int i = 0; i < numPoints; i += 3)
	{
		GLfloat r = clamp(points[i], 0.0f, 1.0f);
		GLfloat g = clamp(points[i + 1], 0.0f, 1.0f);
		glColor4f(r, g, 0.5f, 1.0f);
		glVertex3f(points[i], points[i + 1], points[i + 2]);
	}

    glEnd();
}

void drawTriangle()
{
	glLoadIdentity();//load identity matrix

    glTranslatef(x, y, 0);//move forward 4 units
    glScalef(scale, scale, scale);

		glBegin(GL_TRIANGLES);

		glColor4f(0.0f, 0.0f, 0.5f, 1.0f);
    glVertex3f(-1.0f, -1.0f, 0.0f);
    glColor4f(1.0f, 0.0f, 0.5f, 1.0f);
    glVertex3f(1.0f, -1.0f, 0.0f);
    glColor4f(0.0f, 1.0f, 0.5f, 1.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);

    glEnd();
}

void handleKeys(GLFWwindow* window, int key, int code, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key == GLFW_KEY_EQUAL && action == GLFW_PRESS)
	{
		scale += 0.05;
	}

	if (key == GLFW_KEY_MINUS && action == GLFW_PRESS)
	{
		scale -= 0.05;
	}

	if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
	{
		x -= 0.05;
	}

	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
	{
		x += 0.05;
	}

	if (key == GLFW_KEY_UP && action == GLFW_PRESS)
	{
		y += 0.05;
	}

	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
	{
		y -= 0.05;
	}
}


int main(void)
{
	const GLint WIDTH = 800, HEIGHT = 600;

	// Initializing GLFW
	if(!glfwInit())
	{
		cout("GLFW initialization failed.");
		glfwTerminate();
		return 1;
	}

	// Setup GLFW window properties
	// OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 1);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

	GLFWwindow* mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "Test Window", NULL, NULL);
	if(!mainWindow)
	{
		cout("GLFW window creation failed.");
		glfwTerminate();
		return 1;
	}

	// Get buffer size information
	int bufferWidth, bufferHeight;
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	// Set context for GLEW to use
	glfwMakeContextCurrent(mainWindow);

	// Allow modern extension features
	glewExperimental = GL_TRUE;

	if(glewInit() != GLEW_OK)
	{
		cout("GLEW initialization failed.");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	// Setup viewport size
	glViewport(0, 0, bufferWidth, bufferHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// glOrtho()
	createSierpinskiGasket();

	// Loop until window is closed
	while(!glfwWindowShouldClose(mainWindow))
	{
		// Get and handle user input
		glfwPollEvents();
		glfwSetKeyCallback(mainWindow, handleKeys);

		// Clear window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		// Clear colour buffer before next frame
		glClear(GL_COLOR_BUFFER_BIT);

		drawTriangle();
		drawSierpinskiGasket();

		glfwSwapBuffers(mainWindow);
	}

	return 0;
}
