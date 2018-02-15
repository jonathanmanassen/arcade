//
// dlloader.cpp for arcade in /home/manass_j/rendu/cpp_arcade/src
// 
// Made by jonathan manassen
// Login   <jonathan.manassen@epitech.eu@epitech.net>
// 
// Started on  Sun Apr  9 09:28:46 2017 jonathan manassen
// Last update Sun Apr  9 18:01:34 2017 jonathan manassen
//

#include <string.h>
#include <iostream>
#include <dlfcn.h>
#include "../include/dlloader.hpp"

int	dlloader::launchMenu(const char *str)
{
  handle = dlopen(str, RTLD_GLOBAL | RTLD_NOW);
  if (handle == NULL)
    {
      std::cerr << dlerror() << std::endl;
      return (84);
    }
  openF = (openFct)dlsym(handle, "create");
  if (openF == NULL)
    {
      std::cerr << dlerror() << std::endl;
      return (84);
    }
  gamelist = getAllSO("games/");
  liblist = getAllSO("lib/");
  if (gamelist.size() == 0 || liblist.size() == 0)
    {
      std::cerr << "Graphical lib or game not found" << std::endl;
      delete display;
      dlclose(handle);
      return (84);
    }
  display = openF();
  display->menu(gamelist, liblist);
  gameName = display->getGameName();
  libName = display->getLibName();
  playerName = display->getPlayerName();
  delete display;
  dlclose(handle);
  if (gameName == "" || libName == "" || playerName == "")
    return (84);
  return (0);
}

int	dlloader::loadLib()
{
  handle1 = dlopen(libName.insert(0, "lib/").c_str(),
		   RTLD_GLOBAL | RTLD_NOW);
  if (handle1 == NULL)
    {
      std::cerr << dlerror() << std::endl;
      return (84);
    }
  openFl = (openFct)dlsym(handle1, "create");
  if (openFl == NULL)
    {
      std::cerr << dlerror() << std::endl;
      return (84);
    }
  display = openFl();
  return (0);
}

int	dlloader::loadGame()
{
  handle2 = dlopen(gameName.insert(0, "games/").c_str(),
		   RTLD_GLOBAL | RTLD_NOW);
  if (handle2 == NULL)
    {
      std::cerr << dlerror() << std::endl;
      return (84);
    }
  openFg = (openFctg)dlsym(handle2, "create");
  if (openFg == NULL)
    {
      std::cerr << dlerror() << std::endl;
      return (84);
    }
  game = openFg(display);
  game->setPlayerName(playerName);
  return (0);
}

void	dlloader::launch_previous_lib()
{
  int	i = 0;

  delete getGame()->getLib();
  dlclose(getHandle1());
  for (std::string lib : liblist)
    {
      if (lib.insert(0, "lib/").compare(libName) == 0)
	break;
      i++;
    }
  if (i == 0)
    libName = liblist.at(liblist.size() - 1);
  else
    libName = liblist.at(i - 1);
  loadLib();
  getGame()->setLib(getDisplay());
}

void	dlloader::launch_next_lib()
{
  int	i = 0;

  delete getGame()->getLib();
  dlclose(getHandle1());
  for (std::string lib : liblist)
    {
      if (lib.insert(0, "lib/").compare(libName) == 0)
	break;
      i++;
    }
  if ((i + 1) >= liblist.size())
    libName = liblist.at(0);
  else
    libName = liblist.at(i + 1);
  loadLib();
  getGame()->setLib(getDisplay());
}

void	dlloader::launch_previous_game()
{
  int	i = 0;

  delete display;
  dlclose(getHandle1());
  delete getGame();
  dlclose(getHandle2());
  for (std::string game : gamelist)
    {
      if (game.insert(0, "games/").compare(gameName) == 0)
	break;
      i++;
    }
  if (i == 0)
    gameName = gamelist.at(gamelist.size() - 1);
  else
    gameName = gamelist.at(i - 1);
  libName = libName.substr(4, libName.size() - 4);
  loadLib();
  loadGame();
}

void	dlloader::launch_next_game()
{
  int	i = 0;

  delete display;
  dlclose(getHandle1());
  delete getGame();
  dlclose(getHandle2());
  for (std::string game : gamelist)
    {
      if (game.insert(0, "games/").compare(gameName) == 0)
	break;
      i++;
    }
  if ((i + 1) >= gamelist.size())
    gameName = gamelist.at(0);
  else
    gameName = gamelist.at(i + 1);
  libName = libName.substr(4, libName.size() - 4);
  loadLib();
  loadGame();
}
