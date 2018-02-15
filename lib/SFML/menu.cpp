//
// menu.cpp for sfml in /home/manass_j/rendu/cpp_arcade/lib/SFML
// 
// Made by jonathan manassen
// Login   <jonathan.manassen@epitech.eu@epitech.net>
// 
// Started on  Fri Apr  7 14:32:40 2017 jonathan manassen
// Last update Sat Apr  8 21:49:37 2017 jonathan manassen
//

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include "sfml.hpp"

int	sfml::get_key_menu(int tab, int lib)
{
  std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
  std::chrono::duration<double> keyup = now - keytimeup;
  std::chrono::duration<double> keydown = now - keytimedown;
  std::chrono::duration<double> keyreturn = now - keytimereturn;

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
      window.close();
      return (-1);
    }
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && keyup.count() > 0.15)
    {
      keytimeup = std::chrono::system_clock::now();
      if (step == 0)
	{
	  standgame -= 1;
	  if (standgame < 0)
	    standgame = tab - 1;
	}
      else if (step == 1)
	{
	  standlib -= 1;
	  if (standlib < 0)
	    standlib = lib - 1;
	}
      else
	{
	  playername[step - 2] -= 1;
	  if (playername[step - 2] < 0)
	    playername[step - 2] = 35;
	}
    }
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) &&
	   keydown.count() > 0.15)
    {
      keytimedown = std::chrono::system_clock::now();
      if (step == 0)
	{
	  standgame += 1;
	  if (standgame > tab - 1)
	    standgame = 0;
	}
      else if (step == 1)
	{
	  standlib += 1;
	  if (standlib > lib - 1)
	    standlib = 0;
	}
      else
	{
	  playername[step - 2] += 1;
	  if (playername[step - 2] > 35)
	    playername[step - 2] = 0;
	}
    }
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) &&
	   keyreturn.count() > 0.3)
    {
      keytimereturn = std::chrono::system_clock::now();
      if (step == 0)
	{
	  step += 1;
	  standlib = 0;
	}
      else if (step == 4)
	return (1);
      else if (step >= 0)
	step += 1;
    }
  return (0);
}

char		getplayerChar(char c)
{
  const char	*str = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

  return (str[c]);
}

std::string	playerChar(char c)
{
  const char	*str = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
  std::string	s;

  s = str[c];
  return (s);
}

void	sfml::displayMenu(sf::RenderWindow & window, sf::Font font,
			  sf::Sprite sprite,
			  std::vector<std::string> tab,
			  std::vector<std::string> lib)
{
  sf::Text	text;
  int	i;

  text.setFont(font);
  text.setString("Selectionnez votre jeu :");
  text.setCharacterSize(34);
  text.setColor(sf::Color::Cyan);
  text.setStyle(sf::Text::Regular);
  text.setPosition(70, 30);
  window.draw(text);
  text.setString("Selectionnez votre lib graphique :");
  text.setPosition(670, 30);
  window.draw(text);
  text.setString("Quel est votre nom, Boukensha ?");
  text.setPosition(400, 520);
  window.draw(text);
  i = 0;
  for (std::string tmp : tab)
    {
      text.setString(tmp.c_str());
      text.setPosition(120, 100 + 50 * i);
      i = i + 1;
      window.draw(text);
    }
  i = 0;
  for (std::string tmp : lib)
    {
      text.setString(tmp.c_str());
      text.setPosition(720, 100 + 50 * i);
      i = i + 1;
      window.draw(text);
    }
  if (step > 1)
    {
      sprite.setPosition(574 + 50 * (step - 2), 596);
      sprite.setColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));
      window.draw(sprite);
    }
  text.setCharacterSize(70);
  text.setString((playername[0] == -1) ? "A" : playerChar(playername[0]).c_str());
  text.setPosition(570, 580);
  window.draw(text);
  text.setString((playername[1] == -1) ? "A" : playerChar(playername[1]).c_str());
  text.setPosition(620, 580);
  window.draw(text);
  text.setString((playername[2] == -1) ? "A" : playerChar(playername[2]).c_str());
  text.setPosition(670, 580);
  window.draw(text);
  text.setCharacterSize(34);
  text.setString("Snake");
  text.setPosition(1300, 30);
  window.draw(text);
  text.setString("Pacman");
  text.setPosition(1600, 30);
  window.draw(text);
  i = 0;
  for (std::string names : _names)
    {
      if (names.size() > 0)
	text.setString(names.c_str());
      text.setPosition(1600, 100 + 50 * (i - 5));
      if (i < 5)
	text.setPosition(1300, 100 + 50 * i);
      i++;
      window.draw(text);
    }
  i = 0;
  for (int highscore : _highscores)
    {
      if (highscore > 0)
	text.setString(std::to_string(highscore));
      text.setPosition(1700, 100 + 50 * (i - 5));
      if (i < 5)
	text.setPosition(1400, 100 + 50 * i);
      i++;
      window.draw(text);
    }
  window.display();
}

void	sfml::displayCursor(sf::RenderWindow & window, sf::Sprite cursor,
			    int tab, int lib)
{
  cursor.setPosition(100, 118 + 50 * standgame);
  if (step == 0)
    cursor.setColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));
  window.draw(cursor);
  if (step >= 1)
    {
      cursor.setPosition(700, 118 + 50 * standlib);
      if (step == 1)
	cursor.setColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));
      window.draw(cursor);
    }
  window.display();
}


void	sfml::getHighscore(const char *str)
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

void	sfml::menu(std::vector<std::string> tab, std::vector<std::string> lib)
{
  sf::RenderWindow	window;
  sf::Font		font;
  sf::Sprite		sprite;
  sf::Sprite		sprite2;
  sf::Sprite		sprite3;
  sf::Texture		tex;
  sf::Texture		tex2;
  sf::Texture		tex3;
  int			i;

  if (!font.loadFromFile("8-Bit Madness.ttf"))
    return;
  if (!tex.loadFromFile("lib/arcademenu.png"))
    return;
  if (!tex2.loadFromFile("lib/arrow.png"))
    return;
  if (!tex3.loadFromFile("lib/arrowplayername.png"))
    return;
  window.create(sf::VideoMode(1920, 1080), "Arcade");
  sprite.setTexture(tex);
  sprite2.setTexture(tex2);
  sprite3.setTexture(tex3);
  standgame = 0;
  standlib = -1;
  step = 0;
  playername[0] = -1;
  playername[1] = -1;
  playername[2] = -1;
  getHighscore("./games/Snake/Highscore");
  getHighscore("./games/PacMan/Highscore");
  while (window.isOpen())
    {
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
	  window.close();
	  return;
	}
      sf::Event event;
      while (window.pollEvent(event))
	{
	  if (event.type == sf::Event::Closed)
	    {
	      window.close();
	      return;
	    }
	}
      window.clear();
      sprite.setColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));
      window.draw(sprite);
      displayMenu(window, font, sprite3, tab, lib);
      displayCursor(window, sprite2, tab.size(), lib.size());
      if ((i = get_key_menu(tab.size(), lib.size())) == 1)
	{
	  gameName = tab.at(standgame);
	  libName = lib.at(standlib);
	  for (int i = 0; i < 3; i++)
	    {
	      if (playername[i] == -1)
		playerName.append("A");
	      else
		playerName.append(1, getplayerChar(playername[i]));
	    }
	  window.close();
	  return;
	}
      else if (i == -1)
	return;
    }
}

std::string	sfml::getGameName()
{
  return (gameName);
}

std::string	sfml::getLibName()
{
  return (libName);
}

std::string	sfml::getPlayerName()
{
  return (playerName);
}
