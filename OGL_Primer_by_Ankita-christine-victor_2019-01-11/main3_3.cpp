#include <bits/stdc++.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

#define cout(a) cout<<a<<endl

// IDs
GLuint VAO, VBO, VAO2, VBO2, shaderID, uniformModel;
float scale = 1.0, x = 0.0, y = 0.0;
const int numPoints = 50000;
const char* vShader = "shader.vert";
const char* fShader = "shader.frag";

void createSierpinskiGasket()
{
	GLfloat points[3 * numPoints];
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

	glGenVertexArrays(1, &VAO2);
	glBindVertexArray(VAO2);

	glGenBuffers(1, &VBO2);
	glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void createTriangle()
{
	GLfloat vertices[] = {
		-1.0f, -1.0f, 0.0f,
		 1.0f, -1.0f, 0.0f,
		 0.0f,  1.0f, 0.0f
	};

	glGenVertexArrays(1, &VAO);
	// Subsequent code will be associated with this VAO
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	// GL_ARRAY_BUFFER = Vertex data
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// GL_STATIC_DRAW = Not going to change the data (transforms are OK)
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Location, number, type, normalize, stride, offset
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	// Enable location 0
	glEnableVertexAttribArray(0);

	// Unbinding
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void addShader(const char* shaderIDCode, GLenum shaderIDType)
{
	GLuint theShader = glCreateShader(shaderIDType);

	const GLchar* theCode[1];
	theCode[0] = shaderIDCode;

	GLint codeLength[1];
	codeLength[0] = strlen(shaderIDCode);

	glShaderSource(theShader, 1, theCode, codeLength);
	glCompileShader(theShader);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(theShader, sizeof(eLog), NULL, eLog);
		printf("Error compiling the %d shaderID: '%s'\n", shaderIDType, eLog);
		return;
	}

	glAttachShader(shaderID, theShader);
}

void compileShader(const char* vertexCode, const char* fragmentCode)
{
	// Creating shaderID program
	shaderID = glCreateProgram();

	if(!shaderID)
	{
		cout("Error creating shaderID.");
		return;
	}

	addShader(vertexCode, GL_VERTEX_SHADER);
	addShader(fragmentCode, GL_FRAGMENT_SHADER);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glLinkProgram(shaderID);
	glGetProgramiv(shaderID, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
		printf("Error linking program: '%s'\n", eLog);
		return;
	}

	glValidateProgram(shaderID);
	glGetProgramiv(shaderID, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
		printf("Error validating program: '%s'\n", eLog);
		return;
	}

}

string readFile(const char* fileLocation)
{
	string content;
	ifstream fileStream(fileLocation, ios::in);

	if (!fileStream.is_open()) {
		printf("Failed to read %s! File doesn't exist.", fileLocation);
		return "";
	}

	string line = "";
	while (!fileStream.eof())
	{
		getline(fileStream, line);
		content.append(line + "\n");
	}

	fileStream.close();
	return content;
}

void createShader(const char* vertexLocation, const char* fragmentLocation)
{
	string vertexString = readFile(vertexLocation);
	string fragmentString = readFile(fragmentLocation);
	const char* vertexCode = vertexString.c_str();
	const char* fragmentCode = fragmentString.c_str();

	compileShader(vertexCode, fragmentCode);
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
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Not backwards compatible
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// Allow forward compatibility
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

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

	createTriangle();
	createShader(vShader, fShader);
	createSierpinskiGasket();

	uniformModel = glGetUniformLocation(shaderID, "model");

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

		glUseProgram(shaderID);

		glm::mat4 model = glm::mat4();
		model = glm::translate(model, glm::vec3(x, y, 0));
		//model = glm::rotate(model, rotX * toRadians, glm::vec3(1, 0, 0));
		//model = glm::rotate(model, rotY * toRadians, glm::vec3(0, 1, 0));
		//model = glm::rotate(model, rotZ * toRadians, glm::vec3(0, 0, 1));
		model = glm::scale(model, glm::vec3(scale, scale, scale));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		/*glBindVertexArray(VAO2);
		glDrawArrays(GL_POINTS, 0, numPoints);
		glBindVertexArray(0);*/

		glUseProgram(0);

		glfwSwapBuffers(mainWindow);
	}

	return 0;
}
