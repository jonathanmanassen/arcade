//
// ncurses_pacman.cpp for arcade in /home/meyrie_g/rendu/cpp_arcade/games/PacMan
// 
// Made by Gabin Meyrieux-Drevet
// Login   <meyrie_g@epitech.net>
// 
// Started on  Wed Apr  5 12:06:22 2017 Gabin Meyrieux-Drevet
// Last update Sun Apr  9 20:38:38 2017 Gabin Meyrieux-Drevet
//

#include <iostream>
#include "ncurses.hpp"

# define MAP_SIZE_X 31
# define MAP_SIZE_Y 29

void	ncurses::displayDeath()
{
}

void	ncurses::displayInter(int i)
{
  displayGame_Pacman();
  move((row / 2) + 3, (col / 2) - 3);
  attrset(COLOR_PAIR(13));
  if (i == 0)
    printw("Ready!");
  else
    {
      move((row / 2) + 3, (col / 2) - 5);
      printw("Game Over");
    }
  refresh();
}

int	ncurses::getKey()
{
  int	c;

  nodelay(stdscr, TRUE);
  getmaxyx(stdscr, row, col);
  c = getch();
  if (c == 27)
    {
      endwin();
      return (-1);
    }
  else if (c == KEY_RIGHT)
    game->setDir(RIGHT);
  else if (c == KEY_LEFT)
    game->setDir(LEFT);
  else if (c == KEY_DOWN)
    game->setDir(DOWN);
  else if (c == KEY_UP)
    game->setDir(UP);
  else if (c == '2')
    return ('2');
  else if (c == '3' || c == '"')
    return ('3');
  else if (c == '4' || c == '\'')
    return ('4');
  else if (c == '5' || c == '(')
    return ('5');
  else if (c == '8' || c == '_')
    return ('8');
  else if (c == '9')
    return ('9');
  return (0);
}

void	ncurses::getColor(int gId)
{
  if (game->getGStat(gId) == SCARED && game->timeDiff(2) == 2)
    {
      if (pi == 0)
	attrset(COLOR_PAIR(11));
      else
	attrset(COLOR_PAIR(12));
    }
  else if (game->getGStat(gId) == SCARED)
    attrset(COLOR_PAIR(9));
  else if (game->getGStat(gId) == DEAD)
    attrset(COLOR_PAIR(12));
  else if (gId == 0)
    attrset(COLOR_PAIR(7));
  else if (gId == 1)
    attrset(COLOR_PAIR(8));
  else if (gId == 2)
    attrset(COLOR_PAIR(9));
  else if (gId == 3)
    attrset(COLOR_PAIR(10));
}

int	ncurses::displayGhosts(int i, int j)
{
  int	idx = 0;
  for (int gId = 0; gId < 4; gId++)
    {
      if (j == (int)game->getGPosX(gId)
	  && i == (int)game->getGPosY(gId) && gId == 0)
	{
	  idx = 1;
	  getColor(gId);
	  printw(" ");
	}
      else if (j == (int)game->getGPosX(gId)
	       && i == (int)game->getGPosY(gId) && gId == 1)
	{
	  idx = 1;
	  getColor(gId);
	  printw(" ");		}
      else if (j == (int)game->getGPosX(gId)
	       && i == (int)game->getGPosY(gId) && gId == 2)
	{
	  idx = 1;
	  getColor(gId);
	  printw(" ");
	}
      else if (j == (int)game->getGPosX(gId)
	       && i == (int)game->getGPosY(gId) && gId == 3)
	{
	  idx = 1;
	  getColor(gId);
	  printw(" ");
	}
    }
  return idx;
}

void	ncurses::displayGame_Pacman()
{
  int	idx;

  clear();
  getmaxyx(stdscr, row, col);
  if (row < MAP_SIZE_Y + 5 || col < MAP_SIZE_X * 2)
    window_too_small(MAP_SIZE_X * 2, MAP_SIZE_Y + 5);
  getmaxyx(stdscr, row, col);
  move((row / 2 - (MAP_SIZE_Y / 2) - 2), (col / 2 - MAP_SIZE_X / 3 - 20));
  attrset(COLOR_PAIR(13));
  printw("HighScore: %d\tScore: %d\tLife: %d\tCredits: %d",
	 game->getHighscore(), game->getScore(), game->getLife(), game->getCredits());
  for (int i = 0; i < MAP_SIZE_X; i++)
    {
      for (int j = 1; j < MAP_SIZE_Y; j++)
	{
	  idx = 0;
	  move((row / 2 - MAP_SIZE_Y / 2 + i), (col / 2 - MAP_SIZE_X / 2 + j));
	  if (displayGhosts(i, j) == 0)
	    {
	      attrset(COLOR_PAIR(game->getMapP()[j][i]));
	      if (j == static_cast<int>(game->getPPosX()) &&
		  i == static_cast<int>(game->getPPosY()))
		{
		  attrset(COLOR_PAIR(6));
		  printw("c");
		}
	      else if (game->getMapP()[j][i] == WALLP)
		printw("w");
	      else if (game->getMapP()[j][i] == DOOR)
		printw("-");
	      else if (game->getMapP()[j][i] == SUPERGUM)
		printw("o");
	      else if (game->getMapP()[j][i] == GUM)
		printw(".");
	      else if (game->getMapP()[j][i] == EMPTYP)
		printw(" ");
	      else if (game->getMapP()[j][i] == FRUIT)
		{
		  attrset(COLOR_PAIR(game->getLvl() + 1));
		  printw("f");
		}
	    }
	}
    }
  if (pj < 5)
    pj++;
  else
    pj = 0;
  if (pj == 5 && pi == 0)
    pi = 1;
  else if (pj == 5)
    pi = 0;
  refresh();
}

int	ncurses::init_pacman(Igame *_game)
{
  game = _game;
  return (0);
}
