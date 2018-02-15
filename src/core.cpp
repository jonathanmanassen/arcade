//
// core.cpp for core in /home/manass_j/rendu/cpp_arcade
// 
// Made by jonathan manassen
// Login   <jonathan.manassen@epitech.eu@epitech.net>
// 
// Started on  Wed Mar 22 21:11:13 2017 jonathan manassen
// Last update Sun Apr  9 14:17:38 2017 jonathan manassen
//

#include <dirent.h>
#include <string.h>
#include <iostream>
#include <dlfcn.h>
#include "../include/Interfaces.hpp"
#include "../include/enums.hpp"
#include "../include/dlloader.hpp"

int	isFileSO(std::string str)
{
  int	i;

  i = 0;
  while (str[i])
    i = i + 1;
  while (i > 0 && str[i] != '.')
    i = i - 1;
  if (i == 0)
    return (0);
  if (str[i] == '.' && str[i + 1] == 's' &&
      str[i + 2] == 'o' && str[i + 3] == 0)
    return (1);
  return (0);
}

std::vector<std::string>	getList(std::vector<std::string> tab)
{
  std::vector<std::string>	list;
  int	i;

  i = 0;
  for (std::string tmp : tab)
    if (isFileSO(tmp) == 1)
      list.push_back(tmp);
  return (list);
}

std::vector<std::string>	getAllSO(const char *path)
{
  DIR				*dirp;
  struct dirent			*d;
  std::vector<std::string>	tab;
  std::vector<std::string>	list;

  dirp = opendir(path);
  if (dirp == NULL)
    return (list);
  while ((d = readdir(dirp)) != NULL)
    if (d->d_name[0] != '.')
      tab.push_back(d->d_name);
  list = getList(tab);
  closedir(dirp);
  return (list);
}

int	start(const char *str)
{
  int		i;
  dlloader	dl;
  
  if (dl.launchMenu(str) == 84)
    return (84);
  if (dl.getLibName() != "")
    {
      if (dl.loadLib() == 84)
	return (84);
    }
  else
    {
      delete dl.getDisplay();
      dlclose(dl.getHandle());
      return (84);
    }
  if (dl.getGameName() != "")
    {
      if (dl.loadGame() == 84)
	return (84);
      while ((i = dl.getGame()->Play()) != 0)
	{
	  if (i == '2')
	    dl.launch_previous_lib();
	  else if (i == '3')
	    dl.launch_next_lib();
	  else if (i == '4')
	    dl.launch_previous_game();
	  else if (i == '5')
	    dl.launch_next_game();
	  else if (i == '9')
	    break;
	}
      delete dl.getGame();
      dlclose(dl.getHandle2());
    }
  delete dl.getDisplay();
  dlclose(dl.getHandle1());
  if (i == '9')
    start(dl.getLibName().c_str());
  return (0);
}

int		main(int argc, char **argv, char **env)
{  
  if (argc < 2)
    {
      std::cerr << "Usage: " << argv[0] << " namelib.so" << std::endl;
      return (84);
    }
  if (start(argv[1]) == 84)
    return (84);
  return (0);
}
