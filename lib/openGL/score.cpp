//
// score.cpp for score in /home/mei_c/rendu/CPP/cpp_arcade
// 
// Made by Christophe Mei
// Login   <mei_c@epitech.net>
// 
// Started on  Sun Apr  9 16:10:52 2017 Christophe Mei
// Last update Sun Apr  9 18:23:55 2017 Christophe Mei
//

#include <unistd.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
#include "openGL.hpp"

SDL_Surface	*surftmp_score = NULL;
SDL_Surface	*tmp = NULL;
SDL_Surface	*surf = NULL;
TTF_Font	*font_score;
GLuint		texture;
SDL_Color	color = {255,255,0};

void	clean_up_score()
{
  glDeleteTextures(1,&texture);
  SDL_FreeSurface(tmp);
  TTF_CloseFont(font_score);
  TTF_Quit();
  SDL_Quit();
}

void apply_surface_score(int x, int y, SDL_Surface* source,
			 SDL_Surface* destination, SDL_Rect* clip = NULL)
{
  SDL_Rect offset;
  offset.x = x;
  offset.y = y;
  SDL_BlitSurface(source, clip, destination, &offset);
}

SDL_Surface	*text_score(std::string str)
{
  return (TTF_RenderText_Solid(font_score, str.c_str(), color));
}

void	openGL::Draw_score(int width, int height)
{
  glBindTexture(GL_TEXTURE_2D,texture);
  glEnable(GL_TEXTURE_2D);
  glBegin(GL_QUADS);
  //  glColor3ub(0,0,0);

  applyCol(255,255,255,0);
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, materialColor);
  
  glVertex3f(-0.5, height - 10, -0.9);
  glTexCoord2f(1.0, 0.0);
  glVertex3f(-30 + width, height - 10, -0.9);
  glTexCoord2f(1.0, 1.0);
  glVertex3f(-30 + width, 1, -0.9);
  glTexCoord2f(0.0, 1.0);
  glVertex3f(-0.5, 1, -0.9);
  glTexCoord2f(0.0, 0.0);

  glEnd();
  glDisable(GL_TEXTURE_2D);
}


void	openGL::Draw_score2(int width, int height)
{
  glBindTexture(GL_TEXTURE_2D,texture);
  glEnable(GL_TEXTURE_2D);
  glBegin(GL_QUADS);
  //  glColor3ub(0,0,0);

  applyCol(255,255,255,0);
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, materialColor);
  
  glVertex3f(30, height - 15, -0.9);
  glTexCoord2f(1.0, 0.0);
  glVertex3f(60 + width, height - 15, -0.9);
  glTexCoord2f(1.0, 1.0);
  glVertex3f(60 + width, 1, -0.9);
  glTexCoord2f(0.0, 1.0);
  glVertex3f(30, 1, -0.9);
  glTexCoord2f(0.0, 0.0);

  glEnd();
  glDisable(GL_TEXTURE_2D);
}

SDL_Surface	*openGL::surfScore()
{
  SDL_Surface	*list = SDL_CreateRGBSurface(0, 700, 300, 32, 0, 0, 0, 0);
  SDL_Surface	*txt;

  txt = text_score("Highscore :");
  apply_surface_score(10, 10, txt , list);
  SDL_FreeSurface(txt);
  txt = text_score(std::to_string(game->getHighscore()));
  apply_surface_score(70, 80, txt , list);
  SDL_FreeSurface(txt);
  txt = text_score("Score :");
  apply_surface_score(10, 150, txt, list);
  SDL_FreeSurface(txt);
  txt = text_score(std::to_string(game->getScore()));
  apply_surface_score(70, 220, txt, list);
  SDL_FreeSurface(txt);
  return (list);
}

void	openGL::printScore(int width, int height, int g)
{
  if( TTF_Init() == -1 )
    return;
  font_score = TTF_OpenFont( "ressource/8-Bit Madness.ttf", 100);
  if( font_score == NULL )
    return;  
  surftmp_score = SDL_LoadBMP("ressource/texture.bmp");
  if (surftmp_score == NULL)
    return;
  tmp = openGL::surfScore();
  if(tmp == NULL)
    return;
  surf = SDL_ConvertSurface(tmp, surftmp_score->format, 0);
  if (surf == NULL)
    return;
  SDL_FreeSurface(tmp);
  glGenTextures(1,&texture);
  glBindTexture(GL_TEXTURE_2D,texture);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surf->w,surf->h, 0,
	       GL_RGB,GL_UNSIGNED_BYTE,surf->pixels);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
  SDL_FreeSurface(surf);
  if (g == 0)
    Draw_score(width, height);
  else
    Draw_score2(width, height);
}
