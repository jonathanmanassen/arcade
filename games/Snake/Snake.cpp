//
// Snake.cpp for Snake in /home/manass_j/rendu/cpp_arcade/games/Snake
// 
// Made by jonathan manassen
// Login   <jonathan.manassen@epitech.eu@epitech.net>
// 
// Started on  Fri Mar 24 13:38:20 2017 jonathan manassen
// Last update Sun Apr  9 19:37:55 2017 jonathan manassen
//

#include <fstream>
#include <unistd.h>
#include "Snake.hpp"

extern "C"
{
  Snake	*create(IDisplay *lib)
  {
    return (new Snake(lib));
  }
}

void	Snake::my_sleep(float s)
{
  std::chrono::time_point<std::chrono::system_clock> _Begin = std::chrono::system_clock::now();
  std::chrono::time_point<std::chrono::system_clock> _Now = std::chrono::system_clock::now();
  std::chrono::duration<double> elaps = _Now-_Begin;
  while (elaps.count() < s)
    {
      _Now = std::chrono::system_clock::now();
      elaps = _Now - _Begin;
    }
}

int	Snake::can_change_key(const direction &dir)
{
  if (dir == UP && pos[0][0] - pos[1][0] == 1)
    return (0);
  else if (dir == DOWN && pos[0][0] - pos[1][0] == -1)
    return (0);
  else if (dir == LEFT && pos[0][1] - pos[1][1] == 1)
    return (0);
  else if (dir == RIGHT && pos[0][1] - pos[1][1] == -1)
    return (0);
  return (1);
}

void	Snake::loadMap()
{
  int	k = 0;
  _map = new mapInfo*[MAP_SIZE_Y];
  pos = new int*[MAP_SIZE_Y * MAP_SIZE_X + 1];
  for (int i = 0; i <= (MAP_SIZE_Y * MAP_SIZE_X); i++)
    pos[i] = new int[2];
  for (int i = 0; i < MAP_SIZE_Y; i++)
    _map[i] = new mapInfo[MAP_SIZE_X];
  for (int i = 0; i < MAP_SIZE_Y; i++)
    {
      for (int j = 0; j < MAP_SIZE_X; j++)
	{
	  if (i == 0 || j == 0 || i == (MAP_SIZE_Y - 1) || j == (MAP_SIZE_X - 1))
	    _map[i][j] = WALL;
	  else if (i == (MAP_SIZE_Y / 2) && j >= (MAP_SIZE_X / 2 - 2) &&
		   j <= (MAP_SIZE_X / 2 + 1))
	    {
	      _map[i][j] = SNAKE;
	      pos[k][0] = i;
	      pos[k][1] = j;
	      k++;
	    }
	  else
	    _map[i][j] = EMPTY;
	}
    }
  while (k <= (MAP_SIZE_X * MAP_SIZE_Y))
    {
      pos[k][0] = -1;
      pos[k][1] = -1;
      k++;
    }
}

void	Snake::move(int x, int y)
{
  int	i = 0;

  if (_map[pos[0][0] + y][pos[0][1] + x] != EMPTY &&
      _map[pos[0][0] + y][pos[0][1] + x] != FOOD)
    _gameover = 1;
  else
    {
      while (pos[i][0] != -1)
	i++;
      if (_map[pos[0][0] + y][pos[0][1] + x] == EMPTY)
	{
	  i--;
	  _map[pos[i][0]][pos[i][1]] = EMPTY;
	}
      while (i > 0)
	{
	  pos[i][0] = pos[i - 1][0];
	  pos[i][1] = pos[i - 1][1];
	  _map[pos[i][0]][pos[i][1]] = SNAKE;
	  i--;
	}
      pos[0][0] = pos[1][0] + y;
      pos[0][1] = pos[1][1] + x;
      _map[pos[i][0]][pos[i][1]] = SNAKE;
    }
}

int	Snake::check_food()
{
  for (int i = 0; i < MAP_SIZE_Y; i++)
    {
      for (int j = 0; j < MAP_SIZE_X; j++)
	{
	  if (_map[i][j] == FOOD)
	    return (1);
	}
    }
  return (0);
}


void		Snake::place_food()
{
  static int	s = 0;
  int		x;
  int		y;

  if (check_food() == 0)
    {
      if (s != 0)
	_score += 10;
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
      x = rand() % MAP_SIZE_X;
      y = rand() % MAP_SIZE_Y;
      while (_map[y][x] != EMPTY)
	{
	  x = rand() % MAP_SIZE_X;
	  y = rand() % MAP_SIZE_Y;
	}
      _map[y][x] = FOOD;
      s++;
    }
}

void	Snake::update()
{
  place_food();
  if (dir == UP)
    move(0, -1);
  else if (dir == DOWN)
    move(0, 1);
  else if (dir == RIGHT)
    move(1, 0);
  else
    move(-1, 0);
}

void	Snake::loadHighscore()
{
  std::ifstream file ("./games/Snake/Highscore");

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

void	Snake::genHighscore()
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
  file.open("./games/Snake/Highscore", std::ios::out);
  if (file.bad())
    return;
  for (int i = 0; i < 5; i++)
    file << _names[i] << " " << _highscore[i] << std::endl;
  file.close();
}

void	Snake::restart_game()
{
  for (int i = 0; i <= (MAP_SIZE_Y * MAP_SIZE_X); i++)
    delete pos[i];
  for (int i = 0; i < MAP_SIZE_Y; i++)
    delete _map[i];
  delete[] _map;
  delete[] pos;
  loadMap();
  place_food();
  _score = 0;
  _gameover = 0;
  dir = LEFT;
  newHighscore = 0;
}

int	Snake::Play()
{
  int	c;

  my_sleep(0.1);
  if (_lib->init(this) == -1)
    return (0);
  while (_gameover == 0)
    {
      c = _lib->get_key();
      if (c == '8')
	restart_game();
      else if (c >= '2' && c <= '9')
	return (c);
      else if (c == -1)
	break;
      update();
      _lib->displayGame();
      my_sleep(0.1 / boost);
    }
  _lib->quit();
  if (_score > _highscore[4])
    genHighscore();
  return (0);
}

Snake::Snake(IDisplay *lib) : _lib(lib)
{
  loadMap();
  loadHighscore();
}
