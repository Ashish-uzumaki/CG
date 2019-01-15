#ifndef SHADER_H
#define SHADER_H
#include<bits/stdc++.h>
using namespace std;
#include <GL/glew.h>
class Shader{
public:
  Shader(const string& fileName);
  void Bind();
  virtual ~Shader();
private:
  static const unsigned int NUM_SHADERS = 2;//gluint fragment shader or vertex shader
  Shader(const Shader& other){}
  Shader& operator=(const Shader& other){}

  string LoadShader(const std::string& fileName);
  void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
  // GLuint CreateShader(const std::string& text,GLenum shaderType);
  GLuint CreateShader(const std::string& text, GLenum type);

  GLuint m_program;//my shader program
  GLuint m_shaders[NUM_SHADERS];
};
#endif //SHADER_H
