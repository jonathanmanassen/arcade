//
// Play.cpp<PacMan> for Pacman in /home/manass_j/rendu/cpp_arcade/games/PacMan
// 
// Made by jonathan manassen
// Login   <jonathan.manassen@epitech.eu@epitech.net>
// 
// Started on  Wed Apr  5 10:47:57 2017 jonathan manassen
// Last update Thu Apr  6 12:01:20 2017 jonathan manassen
//

#include "../../include/Protocol.hpp"
#include "Pacman.hpp"

void			Where_am_I(Pacman game)
{
  arcade::WhereAmI	*w;

  w = new arcade::WhereAmI[sizeof(arcade::WhereAmI) + sizeof(arcade::Position)];
  w->type = arcade::CommandType::WHERE_AM_I;
  w->length = 1;
  w->position[0].x = (uint16_t)game.getPPosX();
  w->position[0].y = (uint16_t)game.getPPosY();
  std::cout.write((char*)w, sizeof(arcade::WhereAmI) + sizeof(arcade::Position));
}

void			Get_map(Pacman game, arcade::CommandType cmd)
{
  arcade::GetMap	*map;

  map = new arcade::GetMap[sizeof(arcade::GetMap) + (MAP_SIZE_X * MAP_SIZE_Y * sizeof(arcade::TileType))];
  map->type = arcade::CommandType::GET_MAP;
  map->width = (uint16_t)MAP_SIZE_X;
  map->height = (uint16_t)MAP_SIZE_Y;
  for (int i = 0; i < MAP_SIZE_X; i++)
    {
      for (int j = 0; j < MAP_SIZE_Y; j++)
	{
	  if (game.getMapP()[i][j] == SUPERGUM)
	    map->tile[i * MAP_SIZE_X + j] = arcade::TileType::POWERUP;
	  else if (game.getMapP()[i][j] == WALLP || game.getMapP()[i][j] == DOOR)
	    map->tile[i * MAP_SIZE_X + j] = arcade::TileType::BLOCK;
	  else
	    map->tile[i * MAP_SIZE_X + j] = arcade::TileType::EMPTY;
	}
    }
  std::cout.write((char*)map, sizeof(arcade::GetMap) + (MAP_SIZE_X * MAP_SIZE_Y) * sizeof(arcade::TileType));
}

extern "C"
{
  void			Play(void)
  {
    Pacman		game(NULL);
    arcade::CommandType	cmd;

    while (game.getGameover() == 0)
      {
	direction	key;
	std::cin.read((char*)&cmd, sizeof(cmd));
	if (cmd == arcade::CommandType::WHERE_AM_I)
	  Where_am_I(game);
	else if (cmd == arcade::CommandType::GET_MAP)
	  Get_map(game, cmd);
	else if (cmd == arcade::CommandType::GO_UP)
	  key = UP;
	else if (cmd == arcade::CommandType::GO_DOWN)
	  key = DOWN;
	else if (cmd == arcade::CommandType::GO_LEFT)
	  key = LEFT;
	else if (cmd == arcade::CommandType::GO_RIGHT)
	  key = RIGHT;
	else if (cmd == arcade::CommandType::PLAY)
	  {
	    if (game.checkWin() == 0)
	      game.reset();
	    game.moveG();
	    game.updatePPos();
	    game.updateGPos();
	  }
	if (cmd == arcade::CommandType::GO_UP || cmd == arcade::CommandType::GO_DOWN ||
	    cmd == arcade::CommandType::GO_LEFT || cmd == arcade::CommandType::GO_RIGHT)
	  game.setDir(key);
      }
  }
}
