//
// openGL.cpp for Snake in /home/manass_j/rendu/cpp_arcade/games/Snake
// 
// Made by jonathan manassen
// Login   <jonathan.manassen@epitech.eu@epitech.net>
// 
// Started on  Fri Mar 24 13:58:58 2017 jonathan manassen
// Last update Sun Apr  9 18:00:14 2017 Christophe Mei
//

#include <unistd.h>

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
#include "openGL.hpp"

double angleZ = 0;
SDL_Surface *gamescreen = NULL;
SDL_Surface *libscreen = NULL;
SDL_Surface *playerscreen = NULL;
SDL_Surface* surftmp = NULL;
SDL_Surface* surfgame = NULL;
SDL_Surface* surflib = NULL;
SDL_Surface* surfplayer = NULL;
SDL_Surface *background = NULL;
TTF_Font *font;
TTF_Font *font2;
SDL_Color textColor = { 255, 255, 255 };
GLuint texturegame;
GLuint texturelib;
GLuint textureplayer;
bool	loop = 1;

void	clean_up()
{
  glDeleteTextures(1,&texturegame);
  glDeleteTextures(1,&texturelib);
  glDeleteTextures(1,&textureplayer);
  SDL_FreeSurface(background);
  SDL_FreeSurface(surftmp);
  TTF_CloseFont(font);
  TTF_CloseFont(font2);
  TTF_Quit();
  SDL_Quit();
}

int	openGL::get_key_menu(int tab, int lib)
{
  SDL_Event	event;

  if (loop == 1 || (SDL_PollEvent(&event) && (event.type == SDL_QUIT ||
					      event.type == SDL_KEYDOWN)))
    {
      if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE)
	{
	  clean_up();
	  return (-1);
	}
      if (event.type == SDL_KEYDOWN)
	{
	  if (event.key.keysym.sym == SDLK_DOWN)
	    {
	      if (step == 0)
		{
		  standgame += 1;
		  if (standgame > tab - 1)
		    standgame = 0;
		}
	      else if (step == 1)
		{
		  standlib += 1;
		  if (standlib > lib - 1)
		    standlib = 0;
		}
	      else
		{
		  playername[step - 2] += 1;
		  if (playername[step - 2] > 35)
		    playername[step - 2] = 0;
		}
	    }
	  else if (event.key.keysym.sym == SDLK_UP)
	    {
	      if (step == 0)
		{
		  standgame -= 1;
		  if (standgame < 0)
		    standgame = tab - 1;
		}
	      else if (step == 1)
		{
		  standlib -= 1;
		  if (standlib < 0)
		    standlib = lib - 1;
		}
	      else
		{
		  playername[step - 2] -= 1;
		  if (playername[step - 2] < 0)
		    playername[step - 2] = 35;
		}
	    }
	  else if (event.key.keysym.sym == SDLK_RETURN)
	    {
	      if (step == 0)
		{
		  step += 1;
		  standlib = 0;
		}
	      else if (step == 4)
		return (1);
	      else if (step >= 0)
		step += 1;
	    }
	}
      return (0);
    }
  else
    return (2);
}

void	Draw()
{
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity( );
  gluLookAt(3,4,1.3,0,0,0,0,0,1);
  glRotated(angleZ,0,0,1);

  glBindTexture(GL_TEXTURE_2D,texturegame);
  glEnable(GL_TEXTURE_2D);
  glBegin(GL_QUADS);
  glColor3ub(255,255,255); //face rouge
  glTexCoord2f(0.0, 0.0);
  glVertex3d(1,1,1);
  glTexCoord2f(0.0, 1.0);
  glVertex3d(1,1,-1);
  glTexCoord2f(1.0, 1.0);
  glVertex3d(-1,1,-1);
  glTexCoord2f(1.0, 0.0);
  glVertex3d(-1,1,1);
  glEnd();
  glDisable(GL_TEXTURE_2D);

  glBegin(GL_QUADS);
  glColor3ub(0,255,0); //face verte
  glVertex3d(1,-1,1);
  glVertex3d(1,-1,-1);
  glVertex3d(1,1,-1);
  glVertex3d(1,1,1);
  glEnd();

  
  glBindTexture(GL_TEXTURE_2D,textureplayer);
  glEnable(GL_TEXTURE_2D);
  glBegin(GL_QUADS);
  glColor3ub(0,0,255); //face bleue
  glTexCoord2f(0.0, 0.0);
  glVertex3d(-1,-1,1);
  glTexCoord2f(0.0, 1.0);
  glVertex3d(-1,-1,-1);
  glTexCoord2f(1.0, 1.0);
  glVertex3d(1,-1,-1);
  glTexCoord2f(1.0, 0.0);
  glVertex3d(1,-1,1);
  glEnd();

  glBindTexture(GL_TEXTURE_2D,texturelib);
  glEnable(GL_TEXTURE_2D);
  glBegin(GL_QUADS);
  glColor3ub(255,255,0); //face jaune
  glTexCoord2f(0.0, 0.0);
  glVertex3d(-1,1,1);
  glTexCoord2f(0.0, 1.0);
  glVertex3d(-1,1,-1);
  glTexCoord2f(1.0, 1.0);
  glVertex3d(-1,-1,-1);
  glTexCoord2f(1.0, 0.0);
  glVertex3d(-1,-1,1);
  glEnd();
  glDisable(GL_TEXTURE_2D);

  glBegin(GL_QUADS);
  glColor3ub(0,255,255); //face cyan
  glVertex3d(1,1,-1);
  glVertex3d(1,-1,-1);
  glVertex3d(-1,-1,-1);
  glVertex3d(-1,1,-1);
  glColor3ub(255,0,255); //face magenta
  glVertex3d(1,-1,1);
  glVertex3d(1,1,1);
  glVertex3d(-1,1,1);
  glVertex3d(-1,-1,1);
  glEnd();  
  glFlush();
  SDL_GL_SwapBuffers();
}

char	playerChar(char c)
{
  const char    *str = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

  return (str[c]);
}

void apply_surface(int x, int y, SDL_Surface* source,
		   SDL_Surface* destination, SDL_Rect* clip = NULL)
{
  SDL_Rect offset;
  offset.x = x;
  offset.y = y;
  SDL_BlitSurface(source, clip, destination, &offset);
}

SDL_Surface *load_image( std::string filename )
{
  SDL_Surface* loadedImage = NULL;
  SDL_Surface* optimizedImage = NULL;
  loadedImage = IMG_Load( filename.c_str() );
  if( loadedImage != NULL )
    {
      optimizedImage = SDL_DisplayFormat( loadedImage );
      SDL_FreeSurface( loadedImage );
      if( optimizedImage != NULL )
	{
	  SDL_SetColorKey( optimizedImage, SDL_RLEACCEL | SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, 0, 0xFF, 0xFF ) );
	}      
    }
  return optimizedImage;
}

SDL_Surface	*text(std::string str)
{
  return (TTF_RenderText_Solid(font, str.c_str(), textColor));
}

SDL_Surface	*text2(std::string str)
{
  return (TTF_RenderText_Solid(font2, str.c_str(), textColor));
}

SDL_Surface	*openGL::surfGame(std::vector<std::string> tab)
{
  SDL_Surface	*list = SDL_CreateRGBSurface(0, 1000, 1000, 32, 0, 0, 0, 0);
  int		i;

  apply_surface(0, 0, background, list);
  apply_surface(30, 30, text("Selectionnez votre jeu :"), list);
  i = 0;
  for (std::string tmp : tab)
    {
      SDL_Surface	*txt;
      if (standgame == i && step == 0)
	{
	  txt = text(">>");
	  apply_surface(40, 130 + 70 * i, txt, list);
	  SDL_FreeSurface(txt);
	}
      txt = text(tmp);
      apply_surface(130, 130 + 70 * i, txt, list);
      SDL_FreeSurface(txt);
      i = i + 1;
    }
  return (list);
}

SDL_Surface	*openGL::surfLib(std::vector<std::string> tab)
{
  SDL_Surface	*list = SDL_CreateRGBSurface(0, 1000, 1000, 32, 0, 0, 0, 0);
  int		i;

  apply_surface(0, 0, background, list);
  apply_surface(30, 30, text("Selectionnez votre jeu :"), list);
  i = 0;
  for (std::string tmp : tab)
    {
      SDL_Surface	*txt;
      if (standlib == i && step == 1)
	{
	  txt = text(">>");
	  apply_surface(40, 130 + 70 * i, txt, list);
	  SDL_FreeSurface(txt);
	}
      txt = text(tmp);
      apply_surface(130, 130 + 70 * i, txt, list);
      SDL_FreeSurface(txt);
      i = i + 1;
    }
  return (list);
}

SDL_Surface	*openGL::surfPlayer()
{
  SDL_Surface	*list = SDL_CreateRGBSurface(0, 1000, 1000, 32, 0, 0, 0, 0);
  int		i;
  std::string	c;
  SDL_Surface	*txt;

  apply_surface(0, 0, background, list);
  apply_surface(30, 30, text("Quel est votre nom, Boukensha ?"), list);
  i = 0;
  while (i < 3)
    {
      if (i == step - 2)
	{
	  txt = text2("^");
	  apply_surface(250 + 200 * i, 100, txt, list);
	  SDL_FreeSurface(txt);
	  txt = text2("_");
	  apply_surface(250 + 200 * i, 250, txt, list);
	  SDL_FreeSurface(txt);
	}
      c = playerChar(playername[i]);
      txt = text2(c);
      apply_surface(250 + 200 * i, 200, txt, list);
      SDL_FreeSurface(txt);
      i = i + 1;
    }
  txt = text("Snake");
  apply_surface(100, 600, txt, list);
  SDL_FreeSurface(txt);
  txt = text("Pacman");
  apply_surface(600, 600, txt, list);
  SDL_FreeSurface(txt);
  i = 0;
  for (std::string tmp : _names)
    {
      txt = text(tmp);
      if (i < 5)
	apply_surface(100, 670 + i * 50, txt, list);
      else
	apply_surface(600, 670 + (i - 5) * 50, txt, list);
      SDL_FreeSurface(txt);
      i = i + 1;      
    }
  i = 0;
  for (int tmp : _highscores)
    {
      txt = text(std::to_string(tmp));
      if (i < 5)
	apply_surface(250, 670 + i * 50, txt, list);
      else
	apply_surface(750, 670 + (i - 5) * 50, txt, list);
      SDL_FreeSurface(txt);
      i = i + 1;      
    }
  return (list);
}

void	openGL::getHighscore(const char *str)
{
  std::ifstream file(str, std::ios::in);
  if (file.is_open())
    {
      for (int i = 0; i < 5; i++)
	{
	  int		j = 0;
	  std::string	line;
	  std::string	name;
	  int		highscore;
	  getline(file, line);
	  while (j < line.size() && j < 3 && line[j] != ' ')
	    {
	      name.append(1, line.c_str()[j]);
	      j++;
	    }
	  if (j != 3)
	    {
	      highscore = 0;
	      name = "";
	    }
	  else
	    {
	      line = line.substr(3, line.size() - 3);
	      highscore = std::atoi(line.c_str());
	    }
	  _highscores.push_back(highscore);
	  _names.push_back(name);
	}
      file.close();
    }
  else
    {
      for (int i = 0; i < 5; i++)
	{
	  _highscores.push_back(0);
	  _names.push_back("");
	}
    }
}

void	openGL::menu(std::vector<std::string> tab, std::vector<std::string> lib)
{
  SDL_Init(SDL_INIT_VIDEO);
  atexit(SDL_Quit);
  SDL_WM_SetCaption("SDL GL Application", NULL);
  SDL_SetVideoMode(1920, 1000, 32, SDL_OPENGL);
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  gluPerspective(40,(double)1920/1080,1,1000);
  glEnable(GL_DEPTH_TEST);

  standgame = 0;
  standlib = -1;
  step = 0;
  playername[0] = 0;
  playername[1] = 0;
  playername[2] = 0;

  if( TTF_Init() == -1 )
    return;
  font = TTF_OpenFont( "ressource/8-Bit Madness.ttf", 70 );
  if( font == NULL )
    return;
  font2 = TTF_OpenFont( "ressource/8-Bit Madness.ttf", 300 );
  if( font == NULL )
    return;
  surftmp = SDL_LoadBMP("ressource/texture.bmp");
  if (surftmp == NULL)
    return;
  SDL_Surface* backgroundtmp = IMG_Load("ressource/background.png");
  if (backgroundtmp == NULL)
    return;
  background = SDL_ConvertSurface(backgroundtmp, surftmp->format, 0);
  if (background == NULL)
    return;
  SDL_FreeSurface(backgroundtmp);
  getHighscore("./games/Snake/Highscore");
  getHighscore("./games/PacMan/Highscore");

  Uint32 last_time = SDL_GetTicks();
  Uint32 current_time,ellapsed_time;
  Uint32 start_time;
  for (;;)
    {
      int key = openGL::get_key_menu(tab.size(), lib.size());
      if (key == -1)
	return;
      else if (key == 1)
	{
	  gameName = tab[standgame];
	  libName = lib[standlib];
	  for (int i = 0; i < 3; i++)
	    playerName.append(1, playerChar(playername[i]));
	  clean_up();
	  return;
	}
      else if (key != 2)
	{
	  start_time = SDL_GetTicks();
	  gamescreen = openGL::surfGame(tab);
	  libscreen = openGL::surfLib(lib);
	  playerscreen = openGL::surfPlayer();
	  if(gamescreen == NULL)
	    return;
	  surfgame = SDL_ConvertSurface(gamescreen, surftmp->format, 0);
	  if (surfgame == NULL)
	    return;
	  SDL_FreeSurface(gamescreen);
	  glGenTextures(1,&texturegame);
	  glBindTexture(GL_TEXTURE_2D,texturegame);
	  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surfgame->w,surfgame->h, 0,
		       GL_RGB,GL_UNSIGNED_BYTE,surfgame->pixels);
	  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	  SDL_FreeSurface(surfgame);

	  if(libscreen == NULL)
	    return;
	  surflib = SDL_ConvertSurface(libscreen, surftmp->format, 0);
	  if (surflib == NULL)
	    return;
	  SDL_FreeSurface(libscreen);
	  glGenTextures(1,&texturelib);
	  glBindTexture(GL_TEXTURE_2D,texturelib);
	  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surflib->w,surflib->h, 0,
		       GL_RGB,GL_UNSIGNED_BYTE,surflib->pixels);
	  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	  SDL_FreeSurface(surflib);

	  if(playerscreen == NULL)
	    return;
	  surfplayer = SDL_ConvertSurface(playerscreen, surftmp->format, 0);
	  if (surfplayer == NULL)
	    return;
	  SDL_FreeSurface(playerscreen);
	  glGenTextures(1,&textureplayer);
	  glBindTexture(GL_TEXTURE_2D,textureplayer);
	  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surfplayer->w,surfplayer->h,
		       0, GL_RGB,GL_UNSIGNED_BYTE,surfplayer->pixels);
	  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	  SDL_FreeSurface(surfplayer);
	  
	  current_time = SDL_GetTicks();
	  ellapsed_time = current_time - last_time;
	  last_time = current_time;

	  loop = 0;
	  if (angleZ != -60 && step == 0)
	    {
	      loop = 1;
	      angleZ -= 5;
	    }
	  else if (angleZ != -150 && step == 1)
	    {
	      loop = 1;
	      angleZ -= 5;
	    }
	  else if (angleZ != -240 && step == 2)
	    {
	      loop = 1;
	      angleZ -= 5;
	    }
	  Draw();
      
	  ellapsed_time = SDL_GetTicks() - start_time;
	  if (ellapsed_time < 10)
	    {
	      SDL_Delay(10 - ellapsed_time);
	    }
	}
    }
  return;
}

std::string	openGL::getGameName()
{
  return (gameName);
}

std::string	openGL::getLibName()
{
  return (libName);
}

std::string	openGL::getPlayerName()
{
  return (playerName);
}
