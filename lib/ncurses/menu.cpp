//
// menu.cpp for ncurses in /home/manass_j/cpp_arcade/lib/ncurses
// 
// Made by jonathan manassen
// Login   <jonathan.manassen@epitech.eu@epitech.net>
// 
// Started on  Fri Apr  7 12:16:07 2017 jonathan manassen
// Last update Sat Apr  8 21:49:46 2017 jonathan manassen
//

#include <fstream>
#include <iostream>
#include "ncurses.hpp"

void    ncurses::navupdown(std::vector<std::string> tab, std::vector<std::string> lib)
{
  if (c == KEY_UP)
    {
      if (step == 0)
	{
	  line = line - 1;
	  if (line < 0)
	    line = tab.size() - 1;
	  stand = line;
	}
      else if (step == 1)
	{
	  linelib = linelib - 1;
	  if (linelib < 0)
	    linelib = lib.size() - 1;
	  standlib = linelib;
	}
      else if (step > 1)
	{
	  standplayer[step - 2] -= 1;
	  if (standplayer[step - 2] < 0)
	    standplayer[step - 2] = 35;
	}
    }
  if (c == KEY_DOWN)
    {
      if (step == 0)
	{
	  line = line + 1;
	  if (line > tab.size() - 1)
	    line = 0;
	  stand = line;
	}
      else if (step == 1)
	{
	  linelib = linelib + 1;
	  if (linelib > lib.size() - 1)
	    linelib = 0;
	  standlib = linelib;
	}
      else if (step > 1)
	{
	  standplayer[step - 2] += 1;
	  if (standplayer[step - 2] > 35)
	    standplayer[step - 2] = 0;
	}

    }
}

int	ncurses::navend()
{
  if (c == 27)
    {
      endwin();
      return (2);
    }
  if (c == '\n' || c == ' ')
    {
      if (step == 0)
	{
	  std::cout << "step 1" << std::endl;
	  step += 1;
	  standlib = 0;
	  linelib = 0;
	  return (0);
	}
      else if (step == 4)
	{
	  endwin();
	  return (1);
	}
      else if (step >= 0)
	{
	  step += 1;
	  standplayer[step - 2] = 0;
	  return (0);
	}
    }
  return (0);
}

char		playerChar(char c)
{
  const char	*str = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

  return (str[c]);
}

void    ncurses::affprintw(std::vector<std::string> tab,
			   std::vector<std::string> lib)
{
  int   i;
  int   line;
  int   col;

  i = 0;
  line = 0;
  col = 0;
  for (std::string tmp : tab)
    {
      move(line, col);
      (i == stand) ? attrset(A_REVERSE) : attrset(A_NORMAL);
      printw(tmp.c_str());
      line = line + 1;
      i = i + 1;
    }
  line = 0;
  i = 0;
  for (std::string tmp : lib)
    {
      move(line, col + 50);
      (i == standlib) ? attrset(A_REVERSE) : attrset(A_NORMAL);
      printw(tmp.c_str());
      line = line + 1;
      i = i + 1;
    }
  attrset(A_NORMAL);
  move(10, 0);
  printw("Player name :");
  move(12, 0);
  printw("   ^ ^ ^");
  move(13, 0);
  printw("   A A A");
  i = 0;
  while (i < 3 && standplayer[i] >= 0)
    {
      move(13, 3 + i * 2);
      attrset(A_REVERSE);
      printw("%c", playerChar(standplayer[i]));
      attrset(A_NORMAL);
      i = i + 1;
    }
  move(14, 0);
  printw("   v v v");
  move(16, 0);
  printw("Snake     Pacman");
  i = 0;
  for (std::string names : _names)
    {
      move(17 + i - 5, 10);
      if (i < 5)
	move(17 + i, 0);
      if (names.size() > 0)
	printw("%s", names.c_str());
      i++;
    }
  i = 0;
  for (int highscore : _highscores)
    {
      move(17 + i - 5, 15);
      if (i < 5)
	move(17 + i, 5);
      if (highscore > 0)
	printw("%d", highscore);
      i++;
    }
}

void	ncurses::getHighscore(const char *str)
{
  std::ifstream file(str, std::ios::in);
  
  if (file.is_open())
    {
      for (int i = 0; i < 5; i++)
	{
	  int		j = 0;
	  std::string	line;
	  std::string	name;
	  int		highscore;
	  getline(file, line);
	  while (j < line.size() && j < 3 && line[j] != ' ')
	    {
	      name.append(1, line.c_str()[j]);
	      j++;
	    }
	  if (j != 3)
	    {
	      highscore = 0;
	      name = "";
	    }
	  else
	    {
	      line = line.substr(3, line.size() - 3);
	      highscore = std::atoi(line.c_str());
	    }
	  _highscores.push_back(highscore);
	  _names.push_back(name);
	}
      file.close();
    }
  else
    {
      for (int i = 0; i < 5; i++)
	{
	  _highscores.push_back(0);
	  _names.push_back("");
	}
    }
}

void	ncurses::menu(std::vector<std::string> tab,
		      std::vector<std::string> lib)
{
  int           row;
  int           col;
  int		end;

  getmaxyx(stdscr, row, col);
  line = 0;
  col = 0;
  i = 0;
  stand = 0;
  standlib = -1;
  step = 0;
  standplayer[0] = -1;
  standplayer[1] = -1;
  standplayer[2] = -1;
  getHighscore("./games/Snake/Highscore");
  getHighscore("./games/PacMan/Highscore");
  while (1)
    {
      clear();
      affprintw(tab, lib);
      move(row - 1, col - 1);
      c = getch();
      navupdown(tab, lib);
      end = navend();
      if (end == 2)
	return;
      if (end == 1)
	{
	  gameName = tab.at(stand);
	  libName = lib.at(standlib);
	  for (int i = 0; i < 3; i++)
	    playerName.append(1, playerChar(standplayer[i]));
	  return;
	}
      refresh();
    }
}

std::string	ncurses::getGameName()
{
  return (gameName);
}

std::string	ncurses::getLibName()
{
  return (libName);
}

std::string	ncurses::getPlayerName()
{
  return (playerName);
}
