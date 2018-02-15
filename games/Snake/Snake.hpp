//
// Snake.hpp for Snake in /home/manass_j/rendu/cpp_arcade/games/Snake
// 
// Made by jonathan manassen
// Login   <jonathan.manassen@epitech.eu@epitech.net>
// 
// Started on  Fri Mar 24 14:27:42 2017 jonathan manassen
// Last update Sun Apr  9 20:50:21 2017 Gabin Meyrieux-Drevet
//

#ifndef SNAKE_HPP
# define SNAKE_HPP

#include <iostream>
#include <string>
#include "../../include/Interfaces.hpp"
#include "../../include/enums.hpp"

# define MAP_SIZE_X 46
# define MAP_SIZE_Y 14

class	Snake : public Igame
{
public:
  IDisplay	*_lib;
  mapInfo	**_map;
  int		**pos;
  std::string	playerName = "";
  std::string	gameName = "Snake";
  std::string	mapTex = "./games/Snake/snake.jpg";
  std::string	blockTex = "./games/Snake/block.jpg";
  std::string	foodTex = "./games/Snake/food.jpg";
  direction	dir = LEFT;
  int		_score = 0;
  int		_highscore[5];
  std::string	_names[5];
  int		newHighscore = 0;
  int		_combo = 0;
  int		_credit = 1;
  int		_gameover = 0;
  int		boost = 1;
  Snake(IDisplay*);
  virtual ~Snake() {}
  virtual int	Play();
  void	loadMap();
  void	update();
  void	move(int, int);
  int	check_food();
  void	place_food();
  void	genHighscore();
  void	loadHighscore();
  void	restart_game();
  virtual mapInfo	**getMap();
  virtual direction	getDir();
  virtual void	setDir(direction);
  virtual std::string	getGameName();
  virtual std::string	getMapTex();
  virtual std::string	getBlockTex();
  virtual std::string	getFoodTex();
  virtual void		setGameover(int);
  virtual int		can_change_key(const direction&);
  virtual void		setPlayerName(std::string);
  virtual IDisplay	*getLib();
  virtual void		setLib(IDisplay*);
  virtual void		setBoost(int);

  virtual mapInfoP	**getMapP() {}
  virtual int		getHighscore();
  virtual int		getScore();
  virtual int		getLife() {}
  virtual int		getCredits() {}
  virtual float		getPPosX() {}
  virtual float		getPPosY() {}
  virtual float		getGPosX(int) {}
  virtual float		getGPosY(int) {}
  virtual int		getGLastDir(int) {}
  virtual int		getGStat(int) {}
  virtual int		getGameover();
  virtual std::string	getSpriteTex() {}
  virtual void		updatePPos() {}
  virtual void		updateGPos() {}
  virtual void		moveG() {}
  virtual int		timeDiff(int) {}
  virtual void		my_sleep(float);
  virtual int	lastEat(){}
  virtual std::string	getChomp(){}
  virtual std::string	getBegin(){}
  virtual std::string	getDeath(){}
  virtual std::string	getEF(){}
  virtual std::string	getEG(){}
  virtual std::string	getEEP(){}
  virtual std::string	getIntermission(){}
  virtual std::string	getSiren(){}
  virtual int		getPLastDir() {}
  virtual int		getLvl() {}
};

#endif /*!SNAKE_HPP*/
