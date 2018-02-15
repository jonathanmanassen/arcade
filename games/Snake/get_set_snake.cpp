//
// get_set.cpp for Snake in /home/manass_j/rendu/cpp_arcade/games/Snake
// 
// Made by jonathan manassen
// Login   <jonathan.manassen@epitech.eu@epitech.net>
// 
// Started on  Sat Mar 25 13:09:55 2017 jonathan manassen
// Last update Sun Apr  9 19:27:03 2017 jonathan manassen
//

#include "Snake.hpp"

mapInfo	**Snake::getMap()
{
  return (_map);
}

direction	Snake::getDir()
{
  return (dir);
}

void	Snake::setDir(direction _dir)
{
  dir = _dir;
}

std::string	Snake::getGameName()
{
  return (gameName);
}

std::string	Snake::getMapTex()
{
  return (mapTex);
}

std::string	Snake::getBlockTex()
{
  return (blockTex);
}

std::string	Snake::getFoodTex()
{
  return (foodTex);
}

int	Snake::getScore()
{
  return (_score);
}

int	Snake::getHighscore()
{
  return (_highscore[0]);
}

int	Snake::getGameover()
{
  return (_gameover);
}

void	Snake::setGameover(int g)
{
  _gameover = g;
}

void	Snake::setPlayerName(std::string name)
{
  playerName = name;
}

IDisplay	*Snake::getLib()
{
  return (_lib);
}

void	Snake::setLib(IDisplay *lib)
{
  _lib = lib;
}

void	Snake::setBoost(int i)
{
  boost = i;
}
