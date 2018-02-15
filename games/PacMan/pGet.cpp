//
// pGet.cpp for arcade in /home/meyrie_g/rendu/cpp_arcade/games/PacMan
// 
// Made by Gabin Meyrieux-Drevet
// Login   <meyrie_g@epitech.net>
// 
// Started on  Tue Apr  4 12:27:15 2017 Gabin Meyrieux-Drevet
// Last update Sun Apr  9 19:51:50 2017 Gabin Meyrieux-Drevet
//

#include "Pacman.hpp"

extern "C"
{
  Pacman	*create(IDisplay *lib)
  {
    return (new Pacman(lib));
  }
}

int		Pacman::getLvl()
{
  return _lvl;
}

std::string	Pacman::getChomp()
{
  return chomp;
}

std::string	Pacman::getBegin()
{
  return begin;
}

std::string	Pacman::getDeath()
{
  return death;
}

std::string	Pacman::getEF()
{
  return eF;
}

std::string	Pacman::getEG()
{
  return eG;
}

std::string	Pacman::getEEP()
{
  return eEP;
}

int		Pacman::lastEat()
{
  return _lastEat;
}

std::string	Pacman::getIntermission()
{
  return intermission;
}

mapInfoP	**Pacman::getMapP()
{
  return _map;
}

int		Pacman::getTimer()
{
  return _timer;
}

int		Pacman::getHighscore()
{
  return _highscore[0];
}

int		Pacman::getScore()
{
  return _score;
}

int		Pacman::getLife()
{
  return _life;
}

int		Pacman::getCredits()
{
  return _credit;
}

float		Pacman::getPPosX()
{
  return pPosX;
}

float		Pacman::getPPosY()
{
  return pPosY;
}

float		Pacman::getGPosX(int gId)
{
  return gPosX[gId];
}

float		Pacman::getGPosY(int gId)
{
  return gPosY[gId];
}

int		Pacman::getGLastDir(int gId)
{
  return gLastDir[gId];
}

int		Pacman::getGStat(int gId)
{
  return gStat[gId];
}

int		Pacman::getGameover()
{
  return _gameover;
}

std::string	Pacman::getGameName()
{
  return gameName;
}

std::string	Pacman::getMapTex()
{
  return mapTex;
}

std::string	Pacman::getSpriteTex()
{
  return spriteTex;
}

void	Pacman::setGameover(int g)
{
  _gameover = g;
}

void	Pacman::setPlayerName(std::string name)
{
  playerName = name;
}

IDisplay	*Pacman::getLib()
{
  return (_lib);
}

void	Pacman::setLib(IDisplay *lib)
{
  _lib = lib;
}
