//
// openGL.cpp for Snake in /home/manass_j/rendu/cpp_arcade/games/Snake
// 
// Made by jonathan manassen
// Login   <jonathan.manassen@epitech.eu@epitech.net>
// 
// Started on  Fri Mar 24 13:58:58 2017 jonathan manassen
// Last update Sun Apr  9 19:55:09 2017 jonathan manassen
//

#include <iostream>
#include "openGL.hpp"

# define MAP_SIZE_X 46
# define MAP_SIZE_Y 14

extern "C"
{
  IDisplay	*create()
  {
    return (new openGL);
  }
}

void	openGL::quit()
{
  game->setGameover(1);
  SDL_Quit();
}

void	drawFloor(int width, int height)
{
  GLfloat	materialColor[] = {0.35f, 0.23f, 0.13f, 1.f};

  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, materialColor);
  glPushMatrix();
  glBegin(GL_TRIANGLES);
  glNormal3f(0.0f, 0.0f, 1.f);
  glVertex3f(-1, height + 1, -1);
  glVertex3f(-1, 1, -1);
  glVertex3f(-1 + width, 1, -1);
  glVertex3f(-1, height + 1, -1);
  glVertex3f(-1 + width, 1, -1);
  glVertex3f(-1 + width, height + 1, -1);
  glEnd();
  glPopMatrix();
}

void	openGL::displayGame()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(((MAP_SIZE_X - 1) / 2), (-MAP_SIZE_Y / 3), (MAP_SIZE_Y - 5), ((MAP_SIZE_X - 1) / 2), MAP_SIZE_Y + 30, -MAP_SIZE_Y - 10, 0, 1, 1);
  drawFloor(MAP_SIZE_X, MAP_SIZE_Y - 1);
  applyCol(51, 51, 255, 255);
  for (int i = 0; i < MAP_SIZE_Y; i++)
    {
      for (int j = 0; j < MAP_SIZE_X; j++)
	{
	  glLoadIdentity();
	  gluLookAt(((MAP_SIZE_X - 1) / 2), (-MAP_SIZE_Y / 3), MAP_SIZE_Y - 5, ((MAP_SIZE_X - 1) / 2), MAP_SIZE_Y + 30, -MAP_SIZE_Y - 10, 0, 1, 1);
	  if (game->getMap()[i][j] == SNAKE || game->getMap()[i][j] == FOOD)
	    drawCube(j, MAP_SIZE_Y - (i * MAP_SIZE_X + j) / MAP_SIZE_X, 0.25);
	}
    }
  printScore(MAP_SIZE_X, MAP_SIZE_Y, 0);
  glFlush();
  SDL_GL_SwapBuffers();
}

int	openGL::get_key()
{
  SDL_Event	event;

  while (SDL_PollEvent(&event))
    {
      game->setBoost(1);
      if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE)
	{
	  SDL_Quit();
	  return (-1);
	}
      else if (event.type == SDL_KEYDOWN)
	{
	  if (event.key.keysym.sym == SDLK_RIGHT && game->can_change_key(RIGHT) == 1)
	    game->setDir(RIGHT);
	  else if (event.key.keysym.sym == SDLK_LEFT && game->can_change_key(LEFT) == 1)
	    game->setDir(LEFT);
	  else if (event.key.keysym.sym == SDLK_DOWN && game->can_change_key(DOWN) == 1)
	    game->setDir(DOWN);
	  else if (event.key.keysym.sym == SDLK_UP && game->can_change_key(UP) == 1)
	    game->setDir(UP);
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
	  if (event.key.keysym.sym == SDLK_SPACE)
	    game->setBoost(2);
	  else
	    game->setBoost(1);
	}
    }
  return (0);
}

int	openGL::init(Igame *_game)
{
  game = _game;
  SDL_Init(SDL_INIT_VIDEO);
  SDL_SetVideoMode(1200, 365, 32, SDL_OPENGL);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  gluPerspective(70,(double)1200.0/365.0,1,1000);
  SDL_WM_SetCaption(game->getGameName().c_str() ,NULL);
  return (0);
}

openGL::openGL()
{
}

openGL::~openGL()
{
  SDL_Quit();
}
