#include<iostream>
#include<GL/glew.h>
#include"display.h"
#include "mesh.h"
#include "shader.h"
using namespace std;
int main(){
  Display display(800,600,"hello");
  Vertex vertices[] = { Vertex(glm::vec3(-0.5,-0.5,0)),
                        Vertex(glm::vec3(0,0.5,0)),
                        Vertex(glm::vec3(0.5,-0.5,0)),};
////////////////////////uncomment to DrawSierpinski////////////////////////////////
  // Vertex points[50001];
  // Mesh mesh1;
  // mesh1.DrawSierpinski(vertices,points,5000);
  // Mesh mesh(points,sizeof(points)/sizeof(points[0]));
////////////////////////////////////////////////////////////////////////////////////
  Mesh mesh(vertices,sizeof(vertices)/sizeof(vertices[0]));
  Shader shader("basicShader");
  while(!display.IsClosed()){
    display.Clear(0.0f, 0.0f, 0.0f, 1.0f);
    shader.Bind();
    mesh.Draw();
    display.Update();
  }
  return 0;
}
