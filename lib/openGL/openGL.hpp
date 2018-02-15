//
// openGL.hpp for PacMan in /home/meyrie_g/rendu/cpp_arcade/games/PacMan
// 
// Made by Gabin Meyrieux-Drevet
// Login   <meyrie_g@epitech.net>
// 
// Started on  Tue Mar 14 12:02:56 2017 Gabin Meyrieux-Drevet
// Last update Sun Apr  9 18:15:28 2017 Christophe Mei
//

#ifndef OPENGL_HPP_
# define OPENGL_HPP_

#include <vector>
#include <iostream>
#include <string>
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "../../include/Interfaces.hpp"
#include "../../include/enums.hpp"

class	openGL : public IDisplay
{
  Igame	*game;
  GLfloat	materialColor[4] = {0.2f, 0.2f, 1.0f, 1.0f};
  int	pi = 0;
  int	pj = 0;
  int	view = 0;

  int	standgame;
  int	standlib;
  char	playername[3];
  std::string	gameName = "";
  std::string	libName = "";
  std::string	playerName = "";
  int	step;
  std::vector<std::string>	_names;
  std::vector<int>		_highscores;
  
public:
  openGL();
  virtual ~openGL();
  float	getDirX();
  float	getDirY();
  void	drawCube(double, double, double);
  void	getColor(int);
  void	drawSphere(double, double, double);
  void	drawSG(double, double, double);
  void	drawCylinder(double, double, double, double);
  virtual void	menu(std::vector<std::string>, std::vector<std::string>);
  virtual SDL_Surface	*surfGame(std::vector<std::string>);
  virtual SDL_Surface	*surfLib(std::vector<std::string>);
  virtual SDL_Surface	*surfPlayer();
  virtual SDL_Surface	*surfScore();
  virtual std::string	getGameName();
  virtual std::string	getLibName();
  virtual std::string	getPlayerName();
  void	getHighscore(const char*);
  void	printScore(int, int, int);
  void	Draw_score(int, int);
  void	Draw_score2(int, int);
  virtual int	get_key_menu(int, int);
  virtual int	init(Igame*);
  virtual void	displayGame();
  virtual int	get_key();
  virtual void	quit();
  void	setColor(int);
  void	applyCol(double, double, double, double);

  virtual int	init_pacman(Igame*);
  virtual int	getKey();
  virtual void	displayGame_Pacman();
  int	displayGhosts(int, int);
  virtual void	displayDeath() {}
  virtual void	displayInter(int) {};
};

#endif /*!OPENGL_HPP*/
