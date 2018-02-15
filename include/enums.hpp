//
// enums.hpp for arcade in /home/manass_j/rendu/cpp_arcade
// 
// Made by jonathan manassen
// Login   <jonathan.manassen@epitech.eu@epitech.net>
// 
// Started on  Sat Mar 25 13:00:22 2017 jonathan manassen
// Last update Sun Apr  9 19:35:45 2017 Gabin Meyrieux-Drevet
//

#ifndef ENUMS_HPP_
# define ENUMS_HPP_

enum	direction
  {
    UP,
    DOWN,
    LEFT,
    RIGHT
  };
enum	mapInfo
  {
    EMPTY,
    FOOD,
    SNAKE,
    WALL
  };

enum	mapInfoP
  {
    EMPTYP,
    GUM,
    SUPERGUM,
    WALLP,
    DOOR,
    WARP,
    FRUIT,
  };

enum	Stat
  {
    NORMAL,
    SCARED,
    HUNGRY,
    DEAD
  };

#endif /* ENUMS_HPP_ */
