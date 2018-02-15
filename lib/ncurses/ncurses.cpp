//
// ncurses.cpp for Snake in /home/manass_j/rendu/cpp_arcade/games/Snake
// 
// Made by jonathan manassen
// Login   <jonathan.manassen@epitech.eu@epitech.net>
// 
// Started on  Fri Mar 24 13:58:58 2017 jonathan manassen
// Last update Sun Apr  9 19:28:28 2017 jonathan manassen
//

#include <iostream>
#include "ncurses.hpp"

# define MAP_SIZE_X 46
# define MAP_SIZE_Y 14

extern "C"
{
  IDisplay	*create()
  {
    return (new ncurses);
  }
}

void	change_colors()
{
  init_pair(0, 0, 0);
  init_pair(1, 3, 0);
  init_pair(2, 3, 0);
  init_pair(3, 4, 4);
  init_pair(4, 7, 0);
  init_pair(5, 5, 0);
  init_pair(6, 3, 3);
  init_pair(7, 1, 1);
  init_pair(8, 2, 2);
  init_pair(9, 6, 6);
  init_pair(10, 5, 5);
  init_pair(11, 4, 4);
  init_pair(12, 7, 7);
  init_pair(13, 7, 0);
}

void	ncurses::quit()
{
  endwin();
  game->setGameover(1);
}

void	ncurses::window_too_small(int x, int y)
{
  int	row;
  int	col;

  while ((col < x || row < y) && game->getGameover() == 0)
    {
      getmaxyx(stdscr, row, col);
      move(0, 0);
      attrset(COLOR_PAIR(13));
      if (col >= 38 && row >= 2)
	{
	  printw("window too small");
	  move(1, 0);
	  printw("press esc to quit or resize your window");
	}
      if (getch() == 27)
	quit();
    }
}

void	ncurses::displayGame()
{
  clear();
  getmaxyx(stdscr, row, col);
  if (row < (MAP_SIZE_Y + 5) || col < (MAP_SIZE_X * 2))
    window_too_small(MAP_SIZE_X * 2, MAP_SIZE_Y + 5);
  getmaxyx(stdscr, row, col);
  move(row / 2 - MAP_SIZE_Y / 2 - 2, col / 2 - 20);
  attrset(COLOR_PAIR(13));
  printw("HighScore: %d\tScore: %d",
	 game->getHighscore(), game->getScore());
  for (int i = 0; i < MAP_SIZE_Y; i++)
    {
      for (int j = 0; (j < MAP_SIZE_X * 2); j++)
	{
	  move((row / 2 - MAP_SIZE_Y / 2 + i), (col / 2 - MAP_SIZE_X + j));
	  attrset(COLOR_PAIR(6));
	  if (game->getMap()[i][j / 2] == EMPTY)
	    attrset(COLOR_PAIR(9));
	  printw("%c", ' ');
	}
    }
  refresh();
}

int	ncurses::get_key()
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
  else if (c == KEY_RIGHT && game->can_change_key(RIGHT) == 1)
    game->setDir(RIGHT);
  else if (c == KEY_LEFT && game->can_change_key(LEFT) == 1)
    game->setDir(LEFT);
  else if (c == KEY_DOWN && game->can_change_key(DOWN) == 1)
    game->setDir(DOWN);
  else if (c == KEY_UP && game->can_change_key(UP) == 1)
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
  if (c == ' ')
    game->setBoost(2);
  else
    game->setBoost(1);
  return (0);
}

int	ncurses::init(Igame *_game)
{
  game = _game;
  return (0);
}

ncurses::ncurses()
{
  initscr();
  curs_set(0);
  clear();
  noecho();
  keypad(stdscr, TRUE);
  getmaxyx(stdscr, row, col);
  start_color();
  change_colors();
}

ncurses::~ncurses()
{
  endwin();
}
