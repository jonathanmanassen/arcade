//
// sfml.hpp for PacMan in /home/meyrie_g/rendu/cpp_arcade/games/PacMan
// 
// Made by Gabin Meyrieux-Drevet
// Login   <meyrie_g@epitech.net>
// 
// Started on  Tue Mar 14 12:02:56 2017 Gabin Meyrieux-Drevet
// Last update Sun Apr  9 19:48:34 2017 Gabin Meyrieux-Drevet
//

#ifndef SFML_HPP_
# define SFML_HPP_

#include <vector>
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../../include/Interfaces.hpp"
#include "../../include/enums.hpp"

class	sfml : public IDisplay
{
  Igame	*game;
  sf::RenderWindow window;
  sf::Texture	_mapTex;
  sf::Sprite	_map;
  sf::Texture	_blockTex;
  sf::Sprite	_block;
  sf::Texture	_foodTex;
  sf::Sprite	_food;

  int	i = 0;
  int	direction = 1;
  float	coefx;
  float coefy;
  sf::Texture	_spriteTex;
  sf::Sprite	_gum;
  sf::Sprite	_superGum;
  std::vector<sf::Sprite>	_pacManMove;
  std::vector<sf::Sprite>	_pacManDeath;
  std::vector<std::vector<sf::Sprite>>	_ghosts;
  std::vector<sf::Sprite>	_scaredGhosts;
  std::vector<sf::Sprite>	_fruits;
  std::vector<sf::Sprite>	_deadGhosts;
  std::vector<sf::Sprite>	_interface;
  sf::Font	_font;
  sf::Text	_text;
  sf::SoundBuffer	_chompBuf;
  sf::SoundBuffer	_beginBuf;
  sf::SoundBuffer	_deathBuf;
  sf::SoundBuffer	_eFBuf;
  sf::SoundBuffer	_eGBuf;
  sf::SoundBuffer	_eEPBuf;
  sf::SoundBuffer	_iBuf;
  sf::SoundBuffer	_sBuf;
  sf::Sound	_chomp;
  sf::Sound	_begin;
  sf::Sound	_death;
  sf::Sound	_eF;
  sf::Sound	_eG;
  sf::Sound	_eEP;
  sf::Sound	_intermission;
  sf::Sound	_siren;
  int	standlib;
  int	standgame;
  std::string	gameName;
  std::string	libName;
  std::string	playerName;
  char	playername[3];
  int	step;
  std::chrono::time_point<std::chrono::system_clock> keytimeup;
  std::chrono::time_point<std::chrono::system_clock> keytimedown;
  std::chrono::time_point<std::chrono::system_clock> keytimereturn;
  std::vector<std::string>	_names;
  std::vector<int>		_highscores;
  
public:
  sfml();
  virtual ~sfml();
  virtual void  menu(std::vector<std::string>, std::vector<std::string>);
  virtual void	displayMenu(sf::RenderWindow & window, sf::Font font,
			    sf::Sprite sprite,
			    std::vector<std::string> tab,
			    std::vector<std::string> lib);
  virtual void	displayCursor(sf::RenderWindow & window, sf::Sprite cursor,
			      int tab, int lib);
  virtual int	get_key_menu(int tab, int lib);
  virtual std::string   getGameName();
  virtual std::string   getLibName();
  virtual std::string   getPlayerName();
  virtual int	init(Igame*);
  virtual void	displayGame();
  virtual int	get_key();
  virtual void	quit();
  virtual void	displayInter(int);

  void	print_score();
  void	loadPacManMove();
  void	loadGums();
  void	loadGhosts();
  void	loadScaredGhosts();
  void	loadDeadGhosts();
  void	loadPacmanDeath();
  void	loadInterface();
  void	loadFruits();
  int	loadSounds();
  //  void	displayFruits();
  void	displayInterface();
  void	displayGums();
  void	displayDeath();
  int	getGhostDir();
  void	getKey_Pacman();
  void	displayPacman();
  void	displayGhosts();
  void	lastSound();
  void	getHighscore(const char*);
  void	displayFruit();
  virtual int init_pacman(Igame*);
  virtual int	getKey();
  virtual void	displayGame_Pacman();
};

#endif /*!SFML_HPP*/
