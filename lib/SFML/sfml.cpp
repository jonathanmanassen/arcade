//
// sfml.cpp for Snake in /home/manass_j/rendu/cpp_arcade/games/Snake
// 
// Made by jonathan manassen
// Login   <jonathan.manassen@epitech.eu@epitech.net>
// 
// Started on  Fri Mar 24 13:58:58 2017 jonathan manassen
// Last update Sun Apr  9 19:54:46 2017 jonathan manassen
//

#include <iostream>
#include <vector>
#include <string>
#include "sfml.hpp"

# define MAP_SIZE_X 46
# define MAP_SIZE_Y 14

extern "C"
{
  IDisplay	*create()
  {
    return (new sfml);
  }
}

void	sfml::quit()
{
  window.close();
  game->setGameover(1);
}

void	sfml::print_score()
{
  _text.setString("HighScore: " + std::to_string(game->getHighscore()));
  _text.setPosition(sf::Vector2f(10, 250));
  window.draw(_text);
  _text.setString("Score: " + std::to_string(game->getScore()));
  _text.setPosition(sf::Vector2f(500, 250));
  window.draw(_text);
}

void	sfml::displayGame()
{
  float	coefx = (_map.getGlobalBounds().width - (_map.getGlobalBounds().width * 0.02)) / MAP_SIZE_X;
  float coefy = _map.getGlobalBounds().height / MAP_SIZE_Y - 0.6;
  float diffY = _map.getGlobalBounds().height * 0.04;

  window.clear();
  window.draw(_map);
  print_score();
  for (int i = 0; i < MAP_SIZE_Y; i++)
    {
      for (int j = 0; j < MAP_SIZE_X; j++)
	{
	  if (game->getMap()[i][j] == SNAKE)
	    {
	      _block.setPosition(sf::Vector2f(j * coefx, i * coefy - diffY));
	      window.draw(_block);
	    }
	  else if (game->getMap()[i][j] == FOOD)
	    {
	      _food.setPosition(sf::Vector2f(j * coefx, i * coefy - diffY));
	      window.draw(_food);
	    }
	}
    }
  window.display();
}

int	sfml::get_key()
{
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
      window.close();
      return (-1);
    }
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && game->can_change_key(LEFT) == 1)
    game->setDir(LEFT);
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && game->can_change_key(RIGHT) == 1)
    game->setDir(RIGHT);
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && game->can_change_key(UP) == 1)
    game->setDir(UP);
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && game->can_change_key(DOWN) == 1)
    game->setDir(DOWN);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
    return ('2');
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
    return ('3');
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
    return ('4');
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
    return ('5');
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num8))
    return ('8');
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num9))
    return ('9');
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    game->setBoost(2);
  else
    game->setBoost(1);
  return (0);
}

int	sfml::init(Igame *_game)
{
  game = _game;
  window.create(sf::VideoMode(1920, 1080), game->getGameName());
  if (!_mapTex.loadFromFile(game->getMapTex()))
    return (-1);
  _map.setTexture(_mapTex);
  _map.scale(sf::Vector2f(2.0f, 1.0f));
  if (!_blockTex.loadFromFile(game->getBlockTex()))
    return (-1);
  _block.setTexture(_blockTex);
  if (!_foodTex.loadFromFile(game->getFoodTex()))
    return (-1);
  _food.setTexture(_foodTex);
  if (!_font.loadFromFile("8-Bit Madness.ttf"))
    return (-1);
  _text.setFont(_font);
  _text.setCharacterSize(50);
  _text.setColor(sf::Color::Black);
  _text.setStyle(sf::Text::Regular);
  return (0);
}

sfml::sfml(){}

sfml::~sfml()
{
  window.close();
}
