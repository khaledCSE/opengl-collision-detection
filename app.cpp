#include <GL/glut.h>
#include "app.h"

void Application::initGraphics()
{
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

void Application::display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void Application::resize(int width, int height)
{
  GLfloat nRange = 100.0f;

  if (height == 0)
    height = 1;

  GLfloat aspectRatio = (GLfloat)width / (GLfloat)height;

  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  if (width <= height)
  {
    glOrtho(-nRange, nRange, nRange / aspectRatio, -nRange / aspectRatio, -nRange * 2.0f, nRange * 2.0f);
  }
  else
  {
    glOrtho(-nRange * aspectRatio, nRange * aspectRatio, nRange, -nRange, -nRange * 2.0f, nRange * 2.0f);
  }

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}