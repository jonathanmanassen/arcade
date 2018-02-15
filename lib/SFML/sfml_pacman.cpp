//
// sfml_pacman.cpp for sfml in /home/manass_j/rendu/cpp_arcade
// 
// Made by jonathan manassen
// Login   <jonathan.manassen@epitech.eu@epitech.net>
// 
// Started on  Sat Mar 25 23:05:58 2017 jonathan manassen
// Last update Sun Apr  9 20:15:10 2017 Gabin Meyrieux-Drevet
//

#include <unistd.h>
#include <iostream>
#include <stdio.h>
#include "sfml.hpp"

void	my_sleep(float s)
{
  std::chrono::time_point<std::chrono::system_clock> _Begin = std::chrono::system_clock::now();
  std::chrono::time_point<std::chrono::system_clock> _Now = std::chrono::system_clock::now();
  std::chrono::duration<double> elaps = _Now-_Begin;
  while (elaps.count() < s)
    {
      _Now = std::chrono::system_clock::now();
      elaps = _Now - _Begin;
    }
}

void	sfml::loadPacManMove()
{
  sf::Sprite	tmp;
  int	x = 13;
  int	y = 16;
  int	inc = 20;
  tmp.setTexture(_spriteTex);
  tmp.setTextureRect(sf::IntRect(x + (inc * 2),y,13,13));
  tmp.scale(sf::Vector2f(3.5f, 3.5f));
  _pacManMove.push_back(tmp);
  for (int i = 0; i < 4; i++)
    {
      for (int i = 0; i < 2; i++)
	{
	  tmp.setTextureRect(sf::IntRect(x,y,13,13));
	  _pacManMove.push_back(tmp);
	  x += inc;
	}
      x = 14;
      y += inc;
    }
}

void	sfml::loadGums()
{
  int	x = 13;
  int	y = 195;
  int	inc = 8;
  _gum.setTexture(_spriteTex);
  _gum.setTextureRect(sf::IntRect(x, y, inc, inc));
  _superGum.setTexture(_spriteTex);
  _superGum.setTextureRect(sf::IntRect(x, y, inc, inc));
  _superGum.scale(sf::Vector2f(3.5f, 3.5f));
}

void	sfml::loadGhosts()
{
  std::vector<sf::Sprite>	g;
  sf::Sprite	tmp;
  int	x = 14;
  int	y = 96;
  int	inc = 20;
  tmp.setTexture(_spriteTex);
  tmp.scale(sf::Vector2f(3.5f, 3.5f));
  for (int i = 0; i < 4; i++)
    {
      for (int j = 0; j < 8; j++)
	{
	  tmp.setTextureRect(sf::IntRect(x,y,14,14));
	  g.push_back(tmp);
	  x += inc;
	}
      x = 14;
      y += 20;
      _ghosts.push_back(g);
      g.clear();
    }
}

void	sfml::loadPacmanDeath()
{
  sf::Sprite	tmp;
  int	x = 13;
  int	y = 258;
  int	inc = 20;
  tmp.setTexture(_spriteTex);
  tmp.scale(sf::Vector2f(3.5f, 3.5f));
  for (int i = 0; i < 11; i++)
    {
      tmp.setTextureRect(sf::IntRect(x,y,15,13));
      _pacManDeath.push_back(tmp);
      x += inc;
    }
}

void	sfml::loadScaredGhosts()
{
  sf::Sprite	tmp;
  int	x = 14;
  int	y = 176;
  int	inc = 20;
  tmp.setTexture(_spriteTex);
  tmp.scale(sf::Vector2f(3.5f, 3.5f));
  for (int i = 0; i < 4; i++)
    {
      tmp.setTextureRect(sf::IntRect(x,y,15,14));
      _scaredGhosts.push_back(tmp);
      x += inc;
    }
}

void	sfml::loadDeadGhosts()
{
  sf::Sprite	tmp;
  int	x = 14;
  int	y = 216;
  int	inc = 20;
  tmp.setTexture(_spriteTex);
  tmp.scale(sf::Vector2f(3.5f, 3.5f));
  for (int i = 0; i < 4; i++)
    {
      tmp.setTextureRect(sf::IntRect(x,y,15,14));
      _deadGhosts.push_back(tmp);
      x += inc;
    }
}

void	sfml::loadFruits()
{
  sf::Sprite	tmp;
  int	x = 177;
  int	y = 175;
  int	incy = 20;
  int	incx = 46;
  tmp.setTexture(_spriteTex);
  tmp.scale(sf::Vector2f(3.5f, 3.5f));
  tmp.setPosition(sf::Vector2f((14.5 - 1) * coefx, 17 * coefy + coefy / 4));
  for (int i = 0; i < 4; i++)
    {
      tmp.setTextureRect(sf::IntRect(x,y,20,14));
      _fruits.push_back(tmp);
      y += incy;
    }
  y = 175;
  x += incx;
  for (int i = 0; i < 4; i++)
    {
      tmp.setTextureRect(sf::IntRect(x,y,15,14));
      _fruits.push_back(tmp);
      y += incy;
    }
}

void	sfml::loadInterface()
{
  sf::Sprite	tmp;

  tmp.setTexture(_spriteTex);
  tmp.scale(sf::Vector2f(3.5f, 3.5f));
  tmp.setTextureRect(sf::IntRect(93,175,15,14));
  _interface.push_back(tmp);
  _interface.push_back(tmp);
  _interface.push_back(tmp);
  tmp.setTextureRect(sf::IntRect(24,205,81,7));
  _interface.push_back(tmp);
  tmp.setTextureRect(sf::IntRect(214,15,46,7));
  _interface.push_back(tmp);
  _text.setFont(_font);
  _text.setCharacterSize(34);
  _text.setColor(sf::Color::Cyan);
  _text.setStyle(sf::Text::Regular);
}

int	sfml::loadSounds()
{
  if (!_chompBuf.loadFromFile(game->getChomp()))
    return (-1);
  _chomp.setBuffer(_chompBuf);
  if (!_beginBuf.loadFromFile(game->getBegin()))
    return (-1);
  _begin.setBuffer(_beginBuf);
  if (!_deathBuf.loadFromFile(game->getDeath()))
    return (-1);
  _death.setBuffer(_deathBuf);
  if (!_eFBuf.loadFromFile(game->getEF()))
    return (-1);
  _eF.setBuffer(_eFBuf);
  if (!_eGBuf.loadFromFile(game->getEG()))
    return (-1);
  _eG.setBuffer(_eGBuf);
  if (!_eEPBuf.loadFromFile(game->getEEP()))
    return (-1);
  _eEP.setBuffer(_eEPBuf);
  if (!_iBuf.loadFromFile(game->getIntermission()))
    return (-1);
  _intermission.setBuffer(_iBuf);
  if (!_sBuf.loadFromFile(game->getSiren()))
    return (-1);
  _siren.setBuffer(_sBuf);
  return (0);
}

void	sfml::displayGums()
{
  for (int i = 0; i < 32; i++)
    for(int j = 0; j < 30; j++)
      {
	if (game->getMapP()[j][i] == GUM)
	  {
	    _gum.setPosition(sf::Vector2f((j - 1) * coefx + coefx / 2, i * coefy + coefy / 2));
	    window.draw(_gum);
	  }
	else if (game->getMapP()[j][i] == SUPERGUM)
	  {
	    _superGum.setPosition(sf::Vector2f((j - 1) * coefx + coefx / 4, i * coefy + coefy / 4));
	    window.draw(_superGum);
	  }
      }
}

int	sfml::getKey()
{
  int	j;

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
      window.close();
      return (-1);
    }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    game->setDir(LEFT);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    game->setDir(RIGHT);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    game->setDir(UP);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    game->setDir(DOWN);
  if (game->getPLastDir() == LEFT)
    direction = 1;
  if (game->getPLastDir() == RIGHT)
    direction = 3;
  if (game->getPLastDir() == UP)
    direction = 5;
  if (game->getPLastDir() == DOWN)
    direction = 7;
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
  return (0);
}

void	sfml::displayPacman()
{
  if (i == 2)
    {
      _pacManMove[0].setPosition(sf::Vector2f((game->getPPosX() - 1) * coefx, game->getPPosY() * coefy));
      window.draw(_pacManMove[0]);
    }
  else
    {
      _pacManMove[direction + i].setPosition(sf::Vector2f((game->getPPosX() - 1) * coefx, game->getPPosY() * coefy));
      window.draw(_pacManMove[direction + i]);
    }
}

void	sfml::displayGhosts()
{
  static int tmp;
  int dir;
  int	itmp = i % 2;
  
  for (int gId = 0; gId < 4; gId++)
    {
      dir = game->getGLastDir(gId) * 2;
      if (game->getGStat(gId) == NORMAL)
	{
	  _ghosts[gId][dir + itmp].setPosition(sf::Vector2f((game->getGPosX(gId) - 1) * coefx, game->getGPosY(gId) * coefy));
	  window.draw(_ghosts[gId][dir + itmp]);
	}
      else if (game->getGStat(gId) == DEAD)
	{
	  _deadGhosts[(dir/2)].setPosition(sf::Vector2f((game->getGPosX(gId) - 1) * coefx, game->getGPosY(gId) * coefy));
	  window.draw(_deadGhosts[(dir/2)]);
	}
      else if (game->getGStat(gId) == SCARED && game->timeDiff(2) == 2)
	{
	  _scaredGhosts[tmp + itmp].setPosition(sf::Vector2f((game->getGPosX(gId) - 1) * coefx, game->getGPosY(gId) * coefy));
	  window.draw(_scaredGhosts[tmp + itmp]);
	}
      else if (game->getGStat(gId) == SCARED)
	{
	  _scaredGhosts[itmp].setPosition(sf::Vector2f((game->getGPosX(gId) - 1) * coefx, game->getGPosY(gId) * coefy));
	  window.draw(_scaredGhosts[itmp]);
	}
    }
  if (itmp == 1 && tmp == 0)
    tmp = 2;
  else if (itmp == 1 && tmp == 2)
    tmp = 0;
}

void	sfml::displayDeath()
{
  _death.play();
  if (window.isOpen())
    {
      for (int idx = 0; idx < 11; idx++)
	{
	  window.draw(_map);
	  displayGums();
	  displayGhosts();
	  _pacManDeath[idx].setPosition(sf::Vector2f((game->getPPosX() - 1) * coefx, game->getPPosY() * coefy + coefy / 4));
	  window.draw(_pacManDeath[idx]);
	  window.display();
	  my_sleep(0.035);
	}
    }
}

void	sfml::displayInterface()
{
  int	inc = 29;
  for (int i = 0; i < game->getLife(); i++)
    {
      _interface[i].setPosition(sf::Vector2f((inc) * coefx, 3 * coefy + coefy / 4));
      window.draw(_interface[i]);
      inc += 2;
    }
  _text.setString("Lifes:");
  _text.setPosition(sf::Vector2f((29) * coefx, 2 * coefy + coefy / 4));
  window.draw(_text);
  _text.setString("HighScore: " + std::to_string(game->getHighscore()));
  _text.setPosition(sf::Vector2f((29) * coefx, 5 * coefy + coefy / 4));
  window.draw(_text);
    _text.setString("Score: " + std::to_string(game->getScore()));
  _text.setPosition(sf::Vector2f((29) * coefx, 6 * coefy + coefy / 4));
  window.draw(_text);
}

void	sfml::displayInter(int i)
{
  displayGame_Pacman();
  _chomp.pause();
  _siren.pause();
  if (i == 0)
    {
      _begin.play();
      _interface[4].setPosition(sf::Vector2f((12) * coefx, 17 * coefy + coefy / 4));
      window.draw(_interface[4]);
    }
  else
    {
      _interface[3].setPosition(sf::Vector2f((10) * coefx, 17 * coefy + coefy / 4));
      window.draw(_interface[3]);
    }
  window.display();
}

void	sfml::lastSound()
{
  static int	savedEat;
  static int	i;

  if (game->lastEat() == 6)
    {
      _chomp.pause();
      i = 0;
    }
  if (game->lastEat() == 1 && savedEat != 1 && i != 1)
    {
      _chomp.setLoop(true);
      _chomp.play();
      i = 1;
    }
  if (game->lastEat() == 2)
    {
      _chomp.pause();
      _siren.setLoop(true);
      _siren.play();
      i = 0;
    }
  if (game->lastEat() == 3)
    {
      _chomp.pause();
      _eG.play();
      i = 0;
    }
  if (game->lastEat() == 4)
    {
      _chomp.pause();
      _eF.play();
      i = 0;
    }
  if (game->timeDiff(1) == 0)
    _siren.pause();
  savedEat = game->lastEat();
}

void	sfml::displayFruit()
{
  for (int i = 0; i < 32; i++)
    for(int j = 0; j < 30; j++)
      {
	if (game->getMapP()[j][i] == FRUIT)
	  {
	    _fruits[game->getLvl()].setPosition(sf::Vector2f((j - 1) * coefx, i * coefy));
	    window.draw(_fruits[game->getLvl()]);
	  }
      }
}

void	sfml::displayGame_Pacman()
{
  coefx = _map.getGlobalBounds().width / 29 + 1;
  coefy = _map.getGlobalBounds().height / 31 - 0.3;
  if (window.isOpen())
    {
      lastSound();
      getKey();
      if (i != 0 && i % 2 == 0)
	i = 0;
      else
	i++;
      sf::Event event;
      while (window.pollEvent(event))
        {
	  if (event.type == sf::Event::Closed)
	    window.close();
        }
      window.clear();
      window.draw(_map);
      displayGums();
      displayFruit();
      displayPacman();
      displayGhosts();
      displayInterface();
      window.display();
    }
}

int	sfml::init_pacman(Igame *_game)
{
  game = _game;
  window.create(sf::VideoMode(1920, 1080), game->getGameName());
  if (!_mapTex.loadFromFile(game->getMapTex()))
    return (-1);
  _map.setTexture(_mapTex);
  _map.scale(sf::Vector2f(4, 4));
  if (!_spriteTex.loadFromFile(game->getSpriteTex()))
    return (-1);
  if (!_font.loadFromFile("8-Bit Madness.ttf"))
    return (-1);
  loadPacManMove();
  loadGums();
  loadGhosts();
  loadPacmanDeath();
  loadScaredGhosts();
  loadDeadGhosts();
  loadInterface();
  loadFruits();
  if (loadSounds() == -1)
    return (-1);
  return (0);
}
