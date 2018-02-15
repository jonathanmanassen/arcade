//
// dlloader.hpp for arcade in /home/manass_j/rendu/cpp_arcade/src
// 
// Made by jonathan manassen
// Login   <jonathan.manassen@epitech.eu@epitech.net>
// 
// Started on  Sun Apr  9 09:14:57 2017 jonathan manassen
// Last update Sun Apr  9 13:40:33 2017 jonathan manassen
//

#ifndef DLLOADER_HPP_
# define DLLOADER_HPP_

#include <iostream>
#include <vector>
#include <string>
#include "Interfaces.hpp"

typedef IDisplay *(*openFct)();
typedef Igame *(*openFctg)(IDisplay*);

class	dlloader
{
public:
  void		*handle;
  void		*handle1;
  void		*handle2;
  openFct	openF;
  openFct	openFl;
  openFctg	openFg;
  IDisplay	*display;
  Igame		*game;
  std::vector<std::string>	gamelist;
  std::vector<std::string>	liblist;
  std::string	gameName;
  std::string	libName;
  std::string	playerName;

  int		launchMenu(const char*);
  int		loadLib();
  int		loadGame();
  void		launch_previous_lib();
  void		launch_next_lib();
  void		launch_previous_game();
  void		launch_next_game();
  std::string	getLibName();
  std::string	getGameName();
  IDisplay	*getDisplay();
  void		*getHandle();
  void		*getHandle1();
  void		*getHandle2();
  Igame		*getGame();
};

std::vector<std::string>	getAllSO(const char*);

#endif /* DLLOADER_HPP_ */
