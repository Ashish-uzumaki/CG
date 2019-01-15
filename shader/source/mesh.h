#ifndef MESH_H
#define MESH_H
#include<bits/stdc++.h>
#include<glm/glm.hpp>
#include<GL/glew.h>
using namespace std;
class Vertex{
  public:
    Vertex(const glm::vec3& pos){
      this->pos = pos;
    }
    Vertex(){};
    Vertex add(Vertex pos1,Vertex pos2){
      Vertex pos3;
      for(int k=0;k<3;k++){
        pos3.pos[k]=(pos1.pos[k]+pos2.pos[k])/2.0;
      }
      return pos3;
    }
  protected:
  private:
    glm::vec3 pos;
};
class Mesh{

  public:
    Mesh(Vertex* vertices, unsigned int numVertices );
    Mesh(){};
    void Draw();
    void DrawSierpinski(Vertex* vertices,Vertex* points, unsigned int numVertices);
    virtual ~Mesh();

  private:
    // static const unsigned int NUM_BUFFERS = 4;
    Mesh(const Mesh& other){};
    void operator=(const Mesh& other){};
    enum{
      POSITION_VB,
      NUM_BUFFERS
    };
    //way of referring the mesh data on gpu
    GLuint m_vertexArrayObject;
    GLuint m_vertexArrayBuffers[NUM_BUFFERS];
    unsigned int m_drawCount;//how much of this big gigantic array we're going to create we want to draw
};
#endif //MESH_H
