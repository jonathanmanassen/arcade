//
// Play.cpp for Snake in /home/manass_j/cpp_arcade/games/Snake
// 
// Made by jonathan manassen
// Login   <jonathan.manassen@epitech.eu@epitech.net>
// 
// Started on  Mon Apr  3 12:07:00 2017 jonathan manassen
// Last update Wed Apr  5 10:54:33 2017 jonathan manassen
//

#include "../../include/Protocol.hpp"
#include "Snake.hpp"

int	my_length(const Snake &game)
{
  int	i = 0;

  while (game.pos[i][0] != -1)
    i++;
  return (i);
}

void			Where_am_I(const Snake &game)
{
  arcade::WhereAmI	*w;

  w = new arcade::WhereAmI[sizeof(arcade::WhereAmI) + (my_length(game) * sizeof(arcade::Position))];
  w->type = arcade::CommandType::WHERE_AM_I;
  w->length = my_length(game);
  for (int i = 0; game.pos[i][0] != -1; i++)
    {
      w->position[i].x = (uint16_t)game.pos[i][1];
      w->position[i].y = (uint16_t)game.pos[i][0];
    }
  std::cout.write((char*)w, sizeof(arcade::WhereAmI) + my_length(game) * sizeof(arcade::Position));
}

void			Get_map(const Snake &game, arcade::CommandType cmd)
{
  arcade::GetMap	*map;

  map = new arcade::GetMap[sizeof(arcade::GetMap) + (MAP_SIZE_X * MAP_SIZE_Y * sizeof(arcade::TileType))];
  map->type = arcade::CommandType::GET_MAP;
  map->width = (uint16_t)MAP_SIZE_X;
  map->height = (uint16_t)MAP_SIZE_Y;
  for (int i = 0; i < MAP_SIZE_Y; i++)
    {
      for (int j = 0; j < MAP_SIZE_X; j++)
	{
	  if (game._map[i][j] == FOOD)
	    map->tile[i * MAP_SIZE_X + j] = arcade::TileType::POWERUP;
	  else if (game._map[i][j] == WALL)
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
    Snake		game(NULL);
    arcade::CommandType	cmd;

    game.place_food();
    while (game._gameover == 0)
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
	  game.update();
	if (cmd == arcade::CommandType::GO_UP || cmd == arcade::CommandType::GO_DOWN ||
	    cmd == arcade::CommandType::GO_LEFT || cmd == arcade::CommandType::GO_RIGHT)
	  if (game.can_change_key(key) == 1)
	    game.dir = key;
      }
  }
}
