//
// Pacman.cpp for PacMan in /home/meyrie_g/rendu/cpp_arcade/games/PacMan
// 
// Made by Gabin Meyrieux-Drevet
// Login   <meyrie_g@epitech.net>
// 
// Started on  Tue Mar 14 12:35:43 2017 Gabin Meyrieux-Drevet
// Last update Sun Apr  9 20:46:46 2017 Gabin Meyrieux-Drevet
//

#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <cmath>
#include <chrono>
#include "Pacman.hpp"

bool	Pacman::checkPColision(int x, int y, direction dir)
{
  if (dir == LEFT && _map[x - 1][y] != WALLP)
    return true;
  else if (dir == RIGHT && _map[x + 1][y] != WALLP)
    return true;
  else if (dir == UP && _map[x][y - 1] != WALLP)
    return true;
  else if (dir == DOWN && _map[x][y + 1] != WALLP && _map[x][y + 1] != DOOR)
    return true;
  return false;
}

bool	Pacman::checkColision(int x, int y, direction dir)
{
  if (dir == LEFT && _map[x - 1][y] != WALLP)
    return true;
  else if (dir == RIGHT && _map[x + 1][y] != WALLP)
    return true;
  else if (dir == UP && _map[x][y - 1] != WALLP)
    return true;
  else if (dir == DOWN && _map[x][y + 1] != WALLP)
    return true;
  return false;
}

void	Pacman::move(direction dir, float &x, float &y, float gear)
{
  if (dir == LEFT)
    {
      x -= gear;
      y = static_cast<int>(y);
    }
  else if (dir == RIGHT)
    {
      x += gear;
      y = static_cast<int>(y);
    }
  else if (dir == UP)
    {
      y -= gear;
      x = static_cast<int>(x);
    }
  else if (dir == DOWN)
    {
      y += gear;
      x = static_cast<int>(x);
    }
}

void	Pacman::checkWarp(direction dir, float &x, float &y)
{
  if (x < 1)
    x = 1;
  if (dir == LEFT &&
      static_cast<int>(x) == WARP1X &&
      static_cast<int>(y) == WARP1Y)
    x= WARP2X;
  else if (dir == RIGHT &&
	   static_cast<int>(x) == WARP2X &&
	   static_cast<int>(y) == WARP2Y)
    x = WARP1X;
}

int	Pacman::checkGhostPos()
{
  int	i = 0;
  float dx;
  float dy;

  while (i < 4)
    {
      dx = gPosX[i] - pPosX;
      dy = gPosY[i] - pPosY;
      if (dx < 0)
	dx *= -1;
      if (dy < 0)
	dy *= -1;
      if (dx <= 1 && dy <= 1)
	return i;
      i++;
    }
  return i;
}

void	Pacman::pRespawn()
{
  gPosX[0] = 14.0;
  gPosY[0] = 13.0;
  gPosX[1] = 13.0;
  gPosY[1] = 14.0;
  gPosX[2] = 14.0;
  gPosY[2] = 14.0;
  gPosX[3] = 16.0;
  gPosY[3] = 14.0;
  curDir = LEFT;
  lastDir = LEFT;
  pPosX = 14.5;
  pPosY = 23.0;
  for (int gId = 0; gId < 4; gId++)
    gPath[gId] = new Path();
  for (int i = 0; i < 4; i++)
    gCurDir[i] = DOWN;
  for (int i = 0; i < 4; i++)
    gLastDir[i] = DOWN;
  for (int i = 0; i < 4; i++)
    gStat[i] = NORMAL;
  pStat = NORMAL;
  _lib->displayInter(0);
  my_sleep(4);
}

void	Pacman::pacmanDeath()
{
  _life--;
  if (_life < 0)
    _gameover = 1;
  else
    pRespawn();
}

void	Pacman::eat()
{
  int gId = checkGhostPos();
  if (_map[static_cast<int>(pPosX)][static_cast<int>(pPosY)] == GUM)
    {
      _map[static_cast<int>(pPosX)][static_cast<int>(pPosY)] = EMPTYP;
      _score += 10;
      _lastEat = 1;
    }
  else if (_map[static_cast<int>(pPosX)][static_cast<int>(pPosY)] == SUPERGUM)
    {
      _map[static_cast<int>(pPosX)][static_cast<int>(pPosY)] = EMPTYP;
      _score += 50;
      _combo = 0;
      pStat = HUNGRY;
      for (int gId = 0; gId < 4; gId++)
	if (gStat[gId] != DEAD)
	  gStat[gId] = SCARED;
      _tSpBegin = std::chrono::system_clock::now();;
      _lastEat = 2;
    }
  else if (_map[static_cast<int>(pPosX)][static_cast<int>(pPosY)] == FRUIT)
    {
      _map[static_cast<int>(pPosX)][static_cast<int>(pPosY)] = EMPTYP;
      _score += _fPoints[_lvl];
      _lastEat = 4;
    }
  if (gId < 4)
    {
      if (gStat[gId] == NORMAL)
	{
	  pStat = DEAD;
	  _lib->displayDeath();
	  pacmanDeath();
	}
      else if (gStat[gId] == SCARED && pStat == HUNGRY)
	{
	  gPath[gId] = findPath(gPosX[gId], gPosY[gId], 14, 14);
	  gStat[gId] = DEAD;
	  _combo++;
	  if (_combo == 4)
	    _combo = 0;
	  _score += _gPoints[_combo];
	  _lastEat = 3;
	}
    }
  if (_score > _highscore[0])
    {
      if (newHighscore == 0)
	{
	  for (int i = 4; i > 0; i--)
	    {
	      _highscore[i] = _highscore[i - 1];
	      _names[i] = _names[i - 1];
	    }
	}
      newHighscore = 1;
      _highscore[0] = _score;
      _names[0] = playerName;
    }
}

int	Pacman::timeDiff(int i)
{
  _tNow = std::chrono::system_clock::now();
  std::chrono::duration<double> elaps;
  if (i == 0)
    elaps = _tNow - _tgBegin;
  else
    {
      elaps = _tNow - _tSpBegin;
      if (i == 2 && elaps.count() > 7 && elaps.count() < 10)
	return 2;
    }
  if (elaps.count() > 10)
    return 0;
  return 1;
}

void	Pacman::updatePPos()
{
  static	int countEat;
  if (_lastEat == 0)
    countEat += 1;
  else
    countEat = 0;
  if (countEat == 5)
    _lastEat = 6;
  else
    _lastEat = 0;
  if (pStat == HUNGRY && timeDiff(1) == 0)
    {
      pStat = NORMAL;
      for (int gId = 0; gId < 4; gId++)
	if (gStat[gId] != DEAD)
	  gStat[gId] = NORMAL;
    }
  checkWarp(curDir, pPosX, pPosY);
  checkWarp(lastDir, pPosX, pPosY);
  if (checkPColision(static_cast<int>(pPosX), static_cast<int>(pPosY), curDir))
    {
      lastDir = curDir;
      move(curDir, pPosX, pPosY, MOVE);
    }
  else if (checkPColision(static_cast<int>(pPosX), static_cast<int>(pPosY), lastDir))
    move(lastDir, pPosX, pPosY, MOVE);
  else
    {
      pPosX = static_cast<int>(pPosX);
      pPosY= static_cast<int>(pPosY);
    }
  eat();
  if (pStat == DEAD)
    pacmanDeath();
}

direction	Pacman::getPathDir(int x, int y, int gId)
{
  direction dir = DOWN;
  if (gPath[gId]->isEmpty() != 0)
    {
      if (gStat[gId] == DEAD)
	{
	  gPosX[gId] = gPath[gId]->getFrontX();
	  gPosY[gId] = gPath[gId]->getFrontY();
	  gPath[gId]->delFront();
	}
      else
	{
	  if (x == gPath[gId]->getFrontX() &&
	      y != gPath[gId]->getFrontY())
	    return ((y > gPath[gId]->getFrontY()) ? UP : DOWN);
	  else if (x != gPath[gId]->getFrontX() &&
		   y == gPath[gId]->getFrontY())
	    return ((x > gPath[gId]->getFrontX()) ? LEFT : RIGHT);
	  else if (x == gPath[gId]->getFrontX() &&
		   y == gPath[gId]->getFrontY())
	    {
	      gPath[gId]->delFront();
	      return getPathDir(x, y, gId);
	    }
	}
    }
  return dir;
}

void	Pacman::setGDir(direction dir, int gId)
{
  if (gPosX[gId] < 1)
    gPosX[gId] = 1;
  if (checkColision(static_cast<int>(gPosX[gId]), static_cast<int>(gPosY[gId]), dir))
    gLastDir[gId] = gCurDir[gId];
  gCurDir[gId] = dir;
}

void	Pacman::moveG()
{
  for (int gId = 0; gId < 4; gId++)
    {
      setGDir(getPathDir(static_cast<int>(gPosX[gId]), static_cast<int>(gPosY[gId]), gId), gId);
      if (timeDiff(0) != 0)
	gId = 4;
    }
}

int	Pacman::checkRespawn(float x, float y)
{
  if (x >= 13.0 && x <= 16.0 && y >= 13.0 && y <= 15.0)
    return 0;
  return 1;
}

int	Pacman::pLook2(int x1, int x2, int x3, int y1, int y2, int y3, int i)
{
  int	pPosX = this->pPosX;
  int	pPosY = this->pPosY;
  if (_map[pPosX + x1][pPosY + y1] != WALLP)
    return ((i == 0) ? pPosX + x1: pPosY + y1);
  else if (_map[pPosX + x2][pPosY + y2] != WALLP)
    return ((i == 0) ? pPosX + x2: pPosY + y2);
  else
    return ((i == 0) ? pPosX + x3 : pPosY + y3);
}

int	Pacman::pLook(int i)
{
  int	x = 0;
  int	y = 0;
  if ((pPosX != WARP1X || pPosX != WARP2X) && pPosY == WARP1Y)
    {
      return ((i == 0) ? static_cast<int>(gPosX[0]) : static_cast<int>(gPosY[0]));
    }
  else
    {
      if (lastDir == UP)
	return pLook2(0, -1, 1, -1, 0, 0, i);
      if (lastDir == DOWN)
	return pLook2(0, -1, 1, 1, 0, 0, i);
      if (lastDir == LEFT)
	return pLook2(-1, 0, 0, 0, -1, 1, i);
      if (lastDir == RIGHT)
	return pLook2(1, 0, 0, 0, -1, 1, i);
    }
}

void	Pacman::getRandPos(int gId)
{
  int x = rand() % 28 + 1;
  int y = rand() % 30 + 1;
  while (_map[x][y] == WALLP || _map[x][y] == DOOR || _map[x][y] == WARP ||
	 (x == static_cast<int>(gPosX[gId]) && y == static_cast<int>(gPosY[gId])))
    {
      x = rand() % 28 + 1;
      y = rand() % 30 + 1;
    }
  tmpx = x;
  tmpy = y;
}

void	Pacman::gPredicPPos(int gId, int len)
{
  std::chrono::time_point<std::chrono::system_clock> begin;
  std::chrono::time_point<std::chrono::system_clock> now;

  begin = std::chrono::system_clock::now();
  std::chrono::duration<double> elaps;
  tmpx = pPosX + (rand() % len - len/2) + 1;
  if (tmpx >= 28)
    tmpx = 27;
  if (tmpx <= 2)
    tmpx = 1;
  tmpy = pPosY + (rand() % len - len/2) + 1;
  if (tmpy >= 31)
    tmpy = 30;
  if (tmpy <= 0)
    tmpy = 1;
  while ((_map[tmpx][tmpy] == WALLP || _map[tmpx][tmpy] == DOOR || _map[tmpx][tmpy] == WARP)
	 || (tmpx == static_cast<int>(gPosX[gId]) && tmpy == static_cast<int>(gPosY[gId])))
    {
      now = std::chrono::system_clock::now();
      elaps = now - begin;
      if (elaps.count() > 0.5)
	{
	  getRandPos(gId);
	  break;
	}
      tmpx = pPosX + (rand() % len - len/2) + 1;
      if (tmpx >= 28)
	tmpx = 27;
      if (tmpx <= 3)
	tmpx = 2;
      tmpy = pPosY + (rand() % len - len/2) + 1;
      if (tmpy >= 31)
	tmpy = 30;
      if (tmpy <= 1)
	tmpy = 2;
    }
  gPath[gId] = findPath(gPosX[gId], gPosY[gId], tmpx, tmpy);
}

void	Pacman::getGObjectif(int gId)
{
  int	x;
  int	y;
  if (gPath[gId]->isEmpty() == 0)
    {
      if (gId == 0 && pLook(0) != static_cast<int>(gPosX[gId]) && pLook(1) != static_cast<int>(gPosY[gId]))
	gPath[gId] = findPath(gPosX[gId], gPosY[gId], pLook(0), pLook(1));
      else
	{
	  getRandPos(gId);
	  gPath[gId] = findPath(gPosX[gId], gPosY[gId], tmpx, tmpy);
	}
      if (gId == 1)
	gPredicPPos(gId, 10);
      if (gId == 2)
	gPredicPPos(gId, 20);
      if (gId == 3)
	{
	  getRandPos(gId);
	  gPath[gId] = findPath(gPosX[gId], gPosY[gId], tmpx, tmpy);
	}
    }
}

void	Pacman::updateGPos()
{
  for (int gId = 0; gId < 4; gId++)
    {
      getGObjectif(gId);
      checkWarp(gCurDir[gId], gPosX[gId], gPosY[gId]);
      checkWarp(gLastDir[gId], gPosX[gId], gPosY[gId]);
      if (checkColision(static_cast<int>(gPosX[gId]),
			static_cast<int>(gPosY[gId]),
			gCurDir[gId]))
	{
	  gLastDir[gId] = gCurDir[gId];
	  if (gStat[gId] != SCARED)
	    move(gCurDir[gId], gPosX[gId], gPosY[gId], MOVE);
	  else
	    move(gCurDir[gId], gPosX[gId], gPosY[gId], MOVE - 0.2);
	}
      else if (checkColision(static_cast<int>(gPosX[gId]),
			     static_cast<int>(gPosY[gId]),
	       	     gLastDir[gId]))
	{
	  if (gStat[gId] != SCARED)
	    move(gLastDir[gId], gPosX[gId], gPosY[gId], MOVE);
	  else
	    move(gLastDir[gId], gPosX[gId], gPosY[gId], MOVE - 0.2);
	}
      else
	{
	  gPosX[gId] = static_cast<int>(gPosX[gId]);
	  gPosY[gId] = static_cast<int>(gPosY[gId]);
	}
      if (checkRespawn(gPosX[gId], gPosY[gId]) == 0 && gStat[gId] == DEAD)
	gStat[gId] = NORMAL;
    }
}

void	Pacman::loadMap()
{
  try {
    _map = new mapInfoP*[MAP_SIZE_X];
    for (int i = 0; i < MAP_SIZE_X; i++)
      _map[i] = new mapInfoP[MAP_SIZE_Y];
    std::ifstream file ("./games/PacMan/Map");
    if (file.is_open())
      {
	char c;
	int x = 0;
	int y = 0;
	while (file.get(c) && y < MAP_SIZE_Y)
	  {
	    if (c == 'w')
	      _map[x][y] = WALLP;
	    else if (c == '.')
	      _map[x][y] = GUM;
	    else if (c == 'o')
	      _map[x][y] = SUPERGUM;
	    else if (c == ' ')
	      _map[x][y] = EMPTYP;
	    else if (c == 'z')
	      _map[x][y] = WARP;
	    else if (c == '-')
	      _map[x][y] = DOOR;
	    x++;
	    if (x == MAP_SIZE_X)
	      {
		x = 0;
		y++;
	      }
	  }
	file.close();
      }
    else
      throw std::exception();
  } catch (std::exception &e) {
    std::cerr << "arcade : Map file is missing" << std::endl;
    _exit = 1;
  }
}

void	Pacman::loadHighscore()
{
  std::ifstream file ("./games/PacMan/Highscore");

  if (file.is_open())
    {
      for (int i = 0; i < 5; i++)
	{
	  int		j = 0;
	  std::string	line;
	  getline(file, line);
	  while (j < line.size() && j < 3 && line[j] != ' ')
	    {
	      _names[i].append(1, line.c_str()[j]);
	      j++;
	    }
	  if (j != 3)
	    {
	      _highscore[i] = 0;
	      _names[i] = "";
	    }
	  else
	    {
	      line = line.substr(3, line.size() - 3);
	      _highscore[i] = std::atoi(line.c_str());
	    }
	}
      file.close();
    }
  else
    {
      for (int i = 0; i < 5; i++)
	{
	  _highscore[i] = 0;
	  _names[i] = "";
	}
    }
}

Pacman::Pacman(IDisplay *lib) : _lib(lib)
{  
  loadMap();
  loadHighscore();
}

Pacman::~Pacman(){}

void	Pacman::setDir(direction dir)
{
  if (pPosX < 1)
    pPosX = 1;
  if (checkPColision(static_cast<int>(pPosX), static_cast<int>(pPosY), dir))
    lastDir = curDir;
  curDir = dir;
}

void	Pacman::genHighscore()
{
  std::ofstream file;

  for (int i = 0; i < 5; i++)
    {
      if (_score > _highscore[i] && newHighscore == 0)
	{
	  for (int j = 4; j > i; j--)
	    {
	      _highscore[j] = _highscore[j - 1];
	      _names[j] = _names[j - 1];
	    }
	  _highscore[i] = _score;
	  _names[i] = playerName;
	  break;
	}
    }
  file.open("./games/PacMan/Highscore", std::ios::out);
  if (file.bad())
    return;
  for (int i = 0; i < 5; i++)
    file << _names[i] << " " << _highscore[i] << std::endl;
  file.close();
}

int	Pacman::checkWin()
{
  for (int i = 0; i < 31; i++)
      for(int j = 0; j < 29; j++)
	if (getMapP()[j][i] == GUM || getMapP()[j][i] == SUPERGUM)
	  return 1;
  return 0;
}

void	Pacman::reset()
{
  for (int i = 0; i < MAP_SIZE_X; i++)
    delete _map[i];
  delete _map;
  loadMap();
  if (_lvl < 7)
    _lvl++;
  gPosX[0] = 14.0;
  gPosY[0] = 13.0;
  gPosX[1] = 13.0;
  gPosY[1] = 14.0;
  gPosX[2] = 14.0;
  gPosY[2] = 14.0;
  gPosX[3] = 16.0;
  gPosY[3] = 14.0;
  curDir = LEFT;
  lastDir = LEFT;
  pPosX = 14.5;
  pPosY = 23.0;
  for (int gId = 0; gId < 4; gId++)
    gPath[gId] = new Path();
  for (int i = 0; i < 4; i++)
    gCurDir[i] = DOWN;
  for (int i = 0; i < 4; i++)
    gLastDir[i] = DOWN;
  for (int i = 0; i < 4; i++)
    gStat[i] = NORMAL;
  pStat = NORMAL;
  _lib->displayInter(0);
  my_sleep(4);
  _tgBegin = std::chrono::system_clock::now();
  _tfBegin = std::chrono::system_clock::now();
}

void	Pacman::spawnFruit()
{
  std::chrono::time_point<std::chrono::system_clock> now;
  std::chrono::duration<double> elaps;

  now = std::chrono::system_clock::now();
  elaps = now - _tfBegin;
  if (elaps.count() > 10 && _map[14][17] != FRUIT)
    {
      _map[14][17] = FRUIT;
      _tfBegin = std::chrono::system_clock::now();
    }
}

int	Pacman::Play()
{
  int	c;

  if (_exit == 1)
    return (0);
  if (_lib->init_pacman(this) == -1)
    return (0);
  srand(time(NULL));
  for (int gId = 0; gId < 4; gId++)
    gPath[gId] = new Path();
  _lib->displayInter(0);
  my_sleep(4);
  _tgBegin = std::chrono::system_clock::now();
  _tfBegin = std::chrono::system_clock::now();
  while (getGameover() == 0)
    {
      c = _lib->getKey();
      if (c == '8')
	reset();
      else if (c >= '2' && c <= '9')
	return (c);
      else if (c == -1)
	break;
      if (checkWin() == 0)
	reset();
      spawnFruit();
      moveG();
      updatePPos();
      updateGPos();
      _lib->displayGame_Pacman();
      my_sleep(0.048);
    }
  if (c != -1)
    {
      _lib->displayInter(1);
      my_sleep(3);
    }
  _lib->quit();
  if (_score >_highscore[4])
    genHighscore();
  return (0);
}
