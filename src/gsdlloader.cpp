//
// gsdl.cpp for arcade in /home/manass_j/rendu/cpp_arcade
// 
// Made by jonathan manassen
// Login   <jonathan.manassen@epitech.eu@epitech.net>
// 
// Started on  Sun Apr  9 13:13:01 2017 jonathan manassen
// Last update Sun Apr  9 13:13:10 2017 jonathan manassen
//

#include "../include/dlloader.hpp"

std::string	dlloader::getLibName()
{
  return libName;
}

std::string	dlloader::getGameName()
{
  return gameName;
}

IDisplay	*dlloader::getDisplay()
{
  return display;
}

void	*dlloader::getHandle()
{
  return handle;
}

void	*dlloader::getHandle1()
{
  return handle1;
}

void	*dlloader::getHandle2()
{
  return handle2;
}

Igame	*dlloader::getGame()
{
  return game;
}
