#include<bits/stdc++.h>
#include "display.h"
#include<GL/glew.h>
#include<SDL2/SDL.h>
using namespace std;
Display::Display(int width, int height, string title ){
//////Initializing the window ///////
  SDL_Init(SDL_INIT_EVERYTHING);

  SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

  //title to convert in c format,window in center,width,height,buffer
  m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
  m_glContext = SDL_GL_CreateContext(m_window);//to give the contol to our gpu from os

////// access to opengl library//////

  GLenum status = glewInit(); //search the operating system and evry single opengl function that our graphic card support
  if(status !=GLEW_OK){
    cerr<<"Glew failed to initialize!"<<endl;
  }

/////// now we have access to opengl library and its code //////
  m_isClosed = false;
}

Display::~Display(){
  SDL_GL_DeleteContext(m_glContext);
  SDL_DestroyWindow(m_window);
  SDL_Quit();
}

bool Display::IsClosed(){
  return m_isClosed;
}
void Display::Clear(float r,float g, float b, float a){
  glClearColor(r,g,b,a);
  glClear(GL_COLOR_BUFFER_BIT);
}
void Display::Update(){

  SDL_GL_SwapWindow(m_window);//toswap the windows such that it wont display the uncompleted screen

  SDL_Event e; //to handle even for os to make sure window is not crashing
  while(SDL_PollEvent(&e)){
    if(e.type == SDL_QUIT){
      m_isClosed = true;
    }
  }
}
