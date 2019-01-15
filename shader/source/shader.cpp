#include<bits/stdc++.h>
#include<fstream>
#include "shader.h"
using namespace std;
Shader::Shader(const std::string& fileName){
  // cout<<glGetString(GL_SHADING_LANGUAGE_VERSION);
  m_program = glCreateProgram(); //creating my shader program
  m_shaders[0] = CreateShader(LoadShader(fileName + ".vs"), GL_VERTEX_SHADER);//0 mean vertex shader
  m_shaders[1] = CreateShader(LoadShader(fileName + ".fs"), GL_FRAGMENT_SHADER);//1 mean fragment shader

  for(unsigned int i=0;i<NUM_SHADERS;i++){
    glAttachShader(m_program, m_shaders[i]);
  }

  glBindAttribLocation(m_program,0,"position");

  glLinkProgram(m_program);//linking is crucial you cant link both vertex shader at once check twice GL_VERTEX or FRAGMENT shader
  CheckShaderError(m_program,GL_LINK_STATUS,true,"Error:Program linking failed");//program linking

  glValidateProgram(m_program);
  CheckShaderError(m_program,GL_VALIDATE_STATUS,true,"Error:Program validation failed");//program validation
}

Shader::~Shader(){
  for(unsigned int i=0;i<NUM_SHADERS;i++){
     glDetachShader(m_program, m_shaders[i]);
    glDeleteShader(m_shaders[i]);
  }
  glDeleteProgram(m_program);
}

void Shader::Bind(){
  glUseProgram(m_program);
}
GLuint Shader::CreateShader(const std::string& text,GLenum shaderType){
  GLuint shader = glCreateShader(shaderType);

  if(shader == 0){
    cerr<<"Error:Creating shader failed:"<<endl;
  }

  const GLchar* shaderSourceStrings[1];
  GLint shaderSourceLengths[1];

  shaderSourceStrings[0] = text.c_str();
  shaderSourceLengths[0] = text.length();

  glShaderSource(shader, 1 ,shaderSourceStrings,shaderSourceLengths);
  glCompileShader(shader);

  CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error:compiling shader!");
  return shader;
}
string Shader::LoadShader(const std::string& fileName)
{
    std::ifstream file;
    file.open((fileName).c_str());

    std::string output;
    std::string line;

    if(file.is_open())
    {
        while(file.good())
        {
            getline(file, line);
			      output.append(line + "\n");
        }
    }
    else
    {
		std::cerr << "Unable to load shader: " << fileName << std::endl;
    }

    return output;
}

void Shader::CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
{
    GLint success = 0;
    GLchar error[1024] = { 0 };

    if(isProgram)
        glGetProgramiv(shader, flag, &success);
    else
        glGetShaderiv(shader, flag, &success);

    if(success == GL_FALSE)
    {
        if(isProgram)
            glGetProgramInfoLog(shader, sizeof(error), NULL, error);
        else
            glGetShaderInfoLog(shader, sizeof(error), NULL, error);

        std::cerr << errorMessage << ": '" << error << "'" << std::endl;
    }
}
