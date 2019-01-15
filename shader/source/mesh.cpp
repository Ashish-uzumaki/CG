#include<bits/stdc++.h>
#include "mesh.h"

using namespace std;
Mesh::Mesh(Vertex* vertices, unsigned int numVertices ){
  m_drawCount = numVertices;

  glGenVertexArrays(1,&m_vertexArrayObject);
  glBindVertexArray(m_vertexArrayObject);

  //take the data and push it on gpu
  glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);
  glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);
  glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(vertices[0]), vertices, GL_STATIC_DRAW);

  //to tell our opengl which attribute (of my vertex example position or color) i want to read to draw
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,0);//to read each individual attribute(ithr attribute,size,type,normalization,skip_attrib)
  //now it has all the information to actually draw it
  glBindVertexArray(0);
}

Mesh::~Mesh(){
  glDeleteVertexArrays(1,&m_vertexArrayObject);
}
void Mesh::DrawSierpinski(Vertex* vertices,Vertex* points,unsigned int NUM_POINTS){
  points[0]=vertices[0];
  for(int i=1;i<NUM_POINTS;i++){
    int j=rand()%3;
    Vertex v,v1;
    v1=v.add(points[i-1],vertices[j]);
    points[i]=v1;
  }
}
void Mesh::Draw(){
  glBindVertexArray(m_vertexArrayObject);

  glDrawArrays(GL_POINTS, 0 ,m_drawCount);

  glBindVertexArray(0);
}
