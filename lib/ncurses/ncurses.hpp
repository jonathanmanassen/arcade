//
// ncurses.hpp for PacMan in /home/meyrie_g/rendu/cpp_arcade/games/PacMan
// 
// Made by Gabin Meyrieux-Drevet
// Login   <meyrie_g@epitech.net>
// 
// Started on  Tue Mar 14 12:02:56 2017 Gabin Meyrieux-Drevet
// Last update Sun Apr  9 14:43:36 2017 jonathan manassen
//

#ifndef NCURSES_HPP_
# define NCURSES_HPP_

#include <vector>
#include <string>
#include <ncurses/curses.h>
#include "../../include/Interfaces.hpp"

class	ncurses : public IDisplay
{
  Igame	*game;
  int	row;
  int	col;
  int	c;
  int	stand;
  int	line;
  int	i;
  int	step;
  std::string	gameName;
  std::string	libName;
  std::string	playerName;
  char	standplayer[3];
  int	standlib;
  int	linelib;
  int	pi = 0;
  int	pj = 0;
  std::vector<std::string>	_names;
  std::vector<int>		_highscores;

public:
  ncurses();
  virtual ~ncurses();
  
  virtual void	menu(std::vector<std::string> tab,
			     std::vector<std::string> lib);
  virtual std::string	getGameName();
  virtual std::string	getLibName();
  virtual std::string	getPlayerName();
  void		affprintw(std::vector<std::string> tab,
				  std::vector<std::string> lib);
  int		navend();
  void		navupdown(std::vector<std::string> tab,
				  std::vector<std::string> lib);
  void		getHighscore(const char*);  
  virtual int	init(Igame*);
  virtual void	displayGame();
  virtual int	get_key();
  virtual void	quit();
  void	window_too_small(int, int);
  
  virtual int	init_pacman(Igame*);
  virtual int	getKey();
  virtual void	displayGame_Pacman();
  virtual void	displayDeath();
  virtual void	displayInter(int);
  void	getColor(int);
  int	displayGhosts(int, int);
};

#endif /*!NCURSES_HPP*/
