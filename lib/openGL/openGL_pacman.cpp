//
// openGL.cpp for Snake in /home/manass_j/rendu/cpp_arcade/games/Snake
// 
// Made by jonathan manassen
// Login   <jonathan.manassen@epitech.eu@epitech.net>
// 
// Started on  Fri Mar 24 13:58:58 2017 jonathan manassen
// Last update Sun Apr  9 20:47:28 2017 Gabin Meyrieux-Drevet
//

#include <unistd.h>

#include <iostream>
#include "openGL.hpp"

#define MAP_SIZE_X 31
#define MAP_SIZE_Y 29

void		openGL::drawCube(double x, double y, double height)
{
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, materialColor);
  glPushMatrix();
  glBegin(GL_TRIANGLES);

  glNormal3f(0.0f, -1.0f, 0.0f);
  glVertex3f(x, y - 1.0f, height - 1.0f);
  glVertex3f(x, y -1.0f, height);
  glVertex3f(x - 1.0f, y - 1.0f, height);
  glVertex3f(x, y - 1.0f, height - 1.0f);
  glVertex3f(x - 1.0f, y - 1.0f, height);
  glVertex3f(x - 1.0f, y - 1.0f, height - 1.0f);

  glNormal3f(0.0f, 1.0f, 0.0f);
  glVertex3f(x, y, height - 1.0f);
  glVertex3f(x - 1.0f, y, height - 1.0f);
  glVertex3f(x - 1.0f, y, height);
  glVertex3f(x, y, height - 1.0f);
  glVertex3f(x - 1.0f, y, height);
  glVertex3f(x, y, height);

  glNormal3f(x, 0.0f, 0.0f);
  glVertex3f(x, y - 1.0f, height - 1.0f);
  glVertex3f(x, y, height - 1.0f);
  glVertex3f(x, y, height);
  glVertex3f(x, y - 1.0f, height - 1.0f);
  glVertex3f(x, y, height);
  glVertex3f(x, y - 1.0f, height);

  glNormal3f(0.0f, 0.0f, 1.f);
  glVertex3f(x, y - 1.0f, height);
  glVertex3f(x, y, height);
  glVertex3f(x - 1.0f, y, height);
  glVertex3f(x, y - 1.0f, height);
  glVertex3f(x - 1.0f, y, height);
  glVertex3f(x - 1.0f, y - 1.0f, height);

  glNormal3f(-1.0f, 0.0f, 0.0f);
  glVertex3f(x - 1.0f, y - 1.0f, height);
  glVertex3f(x - 1.0f, y, height);
  glVertex3f(x - 1.0f, y, height - 1.0f);
  glVertex3f(x - 1.0f, y - 1.0f, height);
  glVertex3f(x - 1.0f, y, height - 1.0f);
  glVertex3f(x - 1.0f, y - 1.0f, height - 1.0f);

  glNormal3f(0.0f, 0.0f, -1.0f);
  glVertex3f(x, y, height - 1.0f);
  glVertex3f(x, y - 1.0f, height - 1.0f);
  glVertex3f(x - 1.0f, y - 1.0f, height - 1.0f);
  glVertex3f(x, y, height - 1.0f);
  glVertex3f(x - 1.0f, y - 1.0f, height - 1.0f);
  glVertex3f(x - 1.0f, y, height - 1.0f);
  glEnd();
  glPopMatrix();
}


int	openGL::getKey()
{
  SDL_Event	event;

  while (SDL_PollEvent(&event))
    {
      if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE)
	{
	  SDL_Quit();
	  return (-1);
	}
      if (event.type == SDL_KEYDOWN)
	{
	  if (event.key.keysym.sym == SDLK_RIGHT)
	    game->setDir(RIGHT);
	  else if (event.key.keysym.sym == SDLK_LEFT)
	    game->setDir(LEFT);
	  else if (event.key.keysym.sym == SDLK_DOWN)
	    game->setDir(DOWN);
	  else if (event.key.keysym.sym == SDLK_UP)
	    game->setDir(UP);
	  else if (event.key.keysym.sym == SDLK_k)
	    view = 1;
	  else if (event.key.keysym.sym == SDLK_l)
	    view = 0;
	  else if (event.key.keysym.sym == SDLK_WORLD_73)
	    return ('2');
	  else if (event.key.keysym.sym == SDLK_QUOTEDBL)
	    return ('3');
	  else if (event.key.keysym.sym == SDLK_QUOTE)
	    return ('4');
	  else if (event.key.keysym.sym == SDLK_LEFTPAREN)
	    return ('5');
	  else if (event.key.keysym.sym == SDLK_UNDERSCORE)
	    return ('8');
	  else if (event.key.keysym.sym == SDLK_WORLD_71)
	    return ('9');
	}
    }
  return (0);
}

void	openGL::drawSphere(double x, double y, double radius)
{
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, materialColor);
  glTranslated(x - 0.5, y - 0.5, 0);
  GLUquadric *quad = gluNewQuadric();
  gluQuadricDrawStyle(quad, GLU_FILL);
  gluSphere(quad, radius, 20, 20);
  gluDeleteQuadric(quad);
}

void	openGL::drawCylinder(double x, double y, double rad, double h)
{
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, materialColor);
  glTranslated(x - 0.5, y - 0.5, 0);
  GLUquadric *quad = gluNewQuadric();
  gluQuadricDrawStyle(quad, GLU_FILL);
  gluCylinder(quad, rad, 0, h, 20, 1);
  gluDeleteQuadric(quad);
}


void	openGL::applyCol(double r, double g, double b, double a)
{
  materialColor[0] = r / 255;
  materialColor[1] = g / 255;
  materialColor[2] = b / 255;
  materialColor[3] = a / 255;
}

void	openGL::setColor(int col)
{
  if (col == 0)
    applyCol(255, 255, 0, 0);
  if (col == 1)
    applyCol(255, 0, 0, 0);
  if (col == 2)
    applyCol(255, 20, 147, 0);
  if (col == 3)
    applyCol(0, 255, 255, 0);
  if (col == 4)
    applyCol(255, 165, 0, 0);
  if (col == 5)
    applyCol(255, 255, 255, 0);
  if (col == 6)
    applyCol(0, 0, 255, 0);
  if (col == 7)
    applyCol(40, 40, 255, 0);
  if (col == 8)
    applyCol(0, 0, 0, 0);

}

void	openGL::getColor(int gId)
{
  if (game->getGStat(gId) == SCARED && game->timeDiff(2) == 2)
    {
      if (pi == 0)
	setColor(7);
      else
	setColor(5);
    }
  else if (game->getGStat(gId) == SCARED)
    setColor(7);
  else if (game->getGStat(gId) == DEAD)
    setColor(5);
  else if (gId == 0)
    setColor(1);
  else if (gId == 1)
    setColor(2);
  else if (gId == 2)
    setColor(3);
  else if (gId == 3)
    setColor(4);
}

int	openGL::displayGhosts(int i, int j)
{
  int	idx = 0;
  double	tmp = MAP_SIZE_Y - (i * MAP_SIZE_X + j) / MAP_SIZE_X - 1;
  for (int gId = 0; gId < 4; gId++)
    {
      if (j == (int)game->getGPosX(gId)
	  && i == (int)game->getGPosY(gId) && gId == 0)
	{
	  idx = 1;
	  getColor(gId);
	  drawCylinder(j, tmp, 0.5, 1);
	  return idx;
	}
      else if (j == (int)game->getGPosX(gId)
	       && i == (int)game->getGPosY(gId) && gId == 1)
	{
	  getColor(gId);
	  idx = 1;
	  drawCylinder(j , tmp, 0.5, 1);
	  return idx;
	}
      else if (j == (int)game->getGPosX(gId)
	       && i == (int)game->getGPosY(gId) && gId == 2)
	{
	  getColor(gId);
	  idx = 1;
	  drawCylinder(j, tmp, 0.5, 1);
	  return idx;
	}
      else if (j == (int)game->getGPosX(gId)
	       && i == (int)game->getGPosY(gId) && gId == 3)
	{
	  getColor(gId);
	  idx = 1;
	  drawCylinder(j, tmp, 0.5, 1);
	  return idx;
	}
    }
  return idx;
}

float	openGL::getDirX()
{
  if (game->getPLastDir() == UP)
    return game->getPPosX();
  if (game->getPLastDir() == DOWN)
    return game->getPPosX();
  if (game->getPLastDir() == LEFT)
    return game->getPPosX() - 1;
  if (game->getPLastDir() == RIGHT)
    return game->getPPosX() + 1;
}

float	openGL::getDirY()
{
  if (game->getPLastDir() == UP)
    return (MAP_SIZE_Y - (static_cast<int>(game->getPPosY()) * MAP_SIZE_X + static_cast<int>(game->getPPosX())) / MAP_SIZE_X - 1) - 1;
  if (game->getPLastDir() == DOWN)
    return (MAP_SIZE_Y - (static_cast<int>(game->getPPosY()) * MAP_SIZE_X + static_cast<int>(game->getPPosX())) / MAP_SIZE_X - 1) + 1;
  if (game->getPLastDir() == LEFT)
    return (MAP_SIZE_Y - (static_cast<int>(game->getPPosY()) * MAP_SIZE_X + static_cast<int>(game->getPPosX())) / MAP_SIZE_X - 1);
  if (game->getPLastDir() == RIGHT)
    return (MAP_SIZE_Y - (static_cast<int>(game->getPPosY()) * MAP_SIZE_X + static_cast<int>(game->getPPosX())) / MAP_SIZE_X - 1);
}

void	openGL::displayGame_Pacman()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glColor3d(0.33, 0.33, 0.33);
  for (int i = 0; i < MAP_SIZE_X; i++)
    {
      for (int j = 0; j < MAP_SIZE_Y; j++)
	{
	  glLoadIdentity();
	    gluLookAt(MAP_SIZE_X / 2, -MAP_SIZE_Y / 6, MAP_SIZE_Y - 5, MAP_SIZE_X / 2, MAP_SIZE_Y + 10, -MAP_SIZE_Y - 20, 0, 1, 1);
	  if (displayGhosts(i, j) == 0)
	    {
	      if (static_cast<int>(game->getPPosX()) == j && static_cast<int>(game->getPPosY()) == i)
		{
		  setColor(0);
		  drawSphere(j, MAP_SIZE_Y - (i * MAP_SIZE_X + j) / MAP_SIZE_X - 1, 0.5);
		}
	      if (game->getMapP()[j][i] == WALLP)
		{
		  setColor(6);
		  drawCube(j, MAP_SIZE_Y - (i * MAP_SIZE_X + j) / MAP_SIZE_X - 1, 0.25);
		}
	      else if (game->getMapP()[j][i] == SUPERGUM)
		{
		  setColor(4);
		  drawSphere(j, MAP_SIZE_Y - (i * MAP_SIZE_X + j) / MAP_SIZE_X - 1, 0.4);
		}
	      else if (game->getMapP()[j][i] == GUM)
		{
		  setColor(0);
		  drawSphere(j, MAP_SIZE_Y - (i * MAP_SIZE_X + j) / MAP_SIZE_X - 1, 0.15);
		}
	      if (game->getMapP()[j][i] == DOOR)
		{
		  setColor(5);
		  drawCube(j, MAP_SIZE_Y - (i * MAP_SIZE_X + j) / MAP_SIZE_X - 1, 0.25);
		}
	      if (game->getMapP()[j][i] == FRUIT)
		{
		  setColor(game->getLvl());
		  drawSphere(j, MAP_SIZE_Y - (i * MAP_SIZE_X + j) / MAP_SIZE_X - 1, 0.5);
		}
	    }
	}
    }
  printScore(MAP_SIZE_X, MAP_SIZE_Y, 1);
  
  glFlush();
  SDL_GL_SwapBuffers();
  if (pj < 5)
    pj++;
  else
    pj = 0;
  if (pj == 5 && pi == 0)
    pi = 1;
  else if (pj == 5)
    pi = 0;
}

int	openGL::init_pacman(Igame* _game)
{
  game = _game;
  SDL_Init(SDL_INIT_VIDEO);
  SDL_SetVideoMode(1920, 1080, 32, SDL_OPENGL);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  gluPerspective(70,(double)1200.0/365.0,1,1000);
  SDL_WM_SetCaption(game->getGameName().c_str() ,NULL);
  return (0);
}
