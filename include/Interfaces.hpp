//
// Igame.hpp for Pacman in /home/manass_j/rendu/cpp_arcade
// 
// Made by jonathan manassen
// Login   <jonathan.manassen@epitech.eu@epitech.net>
// 
// Started on  Thu Mar 23 11:24:38 2017 jonathan manassen
// Last update Sun Apr  9 20:49:44 2017 Gabin Meyrieux-Drevet
//

#ifndef IGAME_HPP_
# define IGAME_HPP_

#include <vector>
#include <chrono>
#include "enums.hpp"

class	IDisplay;

class	Igame
{
public:
  virtual ~Igame() {}
  virtual int	Play() = 0;
  virtual void	loadMap() = 0;
  virtual mapInfo	**getMap() = 0;
  virtual direction	getDir() = 0;
  virtual void	setDir(direction) = 0;
  virtual std::string	getGameName() = 0;
  virtual std::string	getMapTex() = 0;
  virtual std::string	getBlockTex() = 0;
  virtual std::string	getFoodTex() = 0;
  virtual int		can_change_key(const direction&) = 0;
  virtual void		setGameover(int) = 0;
  virtual void		setPlayerName(std::string) = 0;
  virtual IDisplay	*getLib() = 0;
  virtual void		setLib(IDisplay*) = 0;
  virtual void		setBoost(int i) = 0;

  virtual mapInfoP	**getMapP() = 0;
  virtual int		getHighscore() = 0;
  virtual int		getScore() = 0;
  virtual int		getLife() = 0;
  virtual int		getCredits() = 0;
  virtual float		getPPosX() = 0;
  virtual float		getPPosY() = 0;
  virtual float		getGPosX(int gId) = 0;
  virtual float		getGPosY(int gId) = 0;
  virtual int		getGLastDir(int gId) = 0;
  virtual int		getGStat(int gId) = 0;
  virtual int		getGameover() = 0;
  virtual std::string	getSpriteTex() = 0;
  virtual int	lastEat() = 0;
  virtual std::string	getChomp() = 0;
  virtual std::string	getBegin() = 0;
  virtual std::string	getDeath() = 0;
  virtual std::string	getEF() = 0;
  virtual std::string	getEG() = 0;
  virtual std::string	getEEP() = 0;
  virtual std::string	getIntermission() = 0;
  virtual std::string	getSiren() = 0;
  virtual void		updatePPos() = 0;
  virtual void		updateGPos() = 0;
  virtual void		moveG() = 0;
  virtual int		timeDiff(int) = 0;
  virtual void		my_sleep(float) = 0;
  virtual int		getPLastDir() = 0;
  virtual int		getLvl() = 0;
};

class	IDisplay
{
public:
  virtual ~IDisplay() {}
  virtual void  menu(std::vector<std::string>,
		     std::vector<std::string>) = 0;
  virtual std::string   getGameName() = 0;
  virtual std::string   getLibName() = 0;
  virtual std::string	getPlayerName() = 0;
  virtual void	displayGame() = 0;
  virtual int	get_key() = 0;
  virtual int	init(Igame*) = 0;
  virtual void	quit() = 0;
  virtual int	init_pacman(Igame*) = 0;
  virtual int	getKey() = 0;
  virtual void	displayGame_Pacman() = 0;
  virtual void	displayDeath() = 0;
  virtual void	displayInter(int) = 0;
};

void	my_sleep(float);

#endif /* IGAME_HPP */
