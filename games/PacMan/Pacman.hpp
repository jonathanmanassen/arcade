//
// PacMan.hpp for PACmAN in /home/meyrie_g/rendu/cpp_arcade/games/PacMan
// 
// Made by Gabin Meyrieux-Drevet
// Login   <meyrie_g@epitech.net>
// 
// Started on  Thu Mar 16 14:14:27 2017 Gabin Meyrieux-Drevet
// Last update Sun Apr  9 20:51:36 2017 Gabin Meyrieux-Drevet
//

#ifndef PACMAN_HPP
# define PACMAN_HPP

#include <iostream>
#include <string>
#include <list>
#include "../../include/Interfaces.hpp"

# define MAP_SIZE_X 30
# define MAP_SIZE_Y 32
# define MOVE 0.45
# define WARP1X 1
# define WARP1Y 14
# define WARP2X 27
# define WARP2Y 14
# define MIDDLEX 15
# define MIDDLEY 15

class	Node
{
  int	free = 0;
  int x;
  int y;
  float cost;
  Node *parent;
  float restCost;
  int depth;
public:
  Node(){}
  Node(int, int);
  Node(int _free) : free(_free){}
  ~Node();
  float	getCosts(int,int,int,int);
  int	getX() const;
  void	setX(int);
  int	getY() const;
  void	setY(int);
  float	getCost() const;
  void	setCost(float);
  float	getRestCost() const;
  void	setRestCost(float);
  int	getDepth() const;
  void	setDepth(int);
  void	setCosts();
  void	setRestCosts();
  int	setParent(Node *);
  Node	*getParent();
  int	compareTo(Node *);
  Node	&operator=(Node const &);
  bool	operator==(Node const &);
  bool	operator!=(Node const &);
  Node	&operator=(Node *);
  bool	operator==(Node *);
  bool	operator!=(Node *);
  int	getFree() const {return free;}
  void	setFree(int f) {free = f;}
};

class	Path
{

  std::vector<int>	x;
  std::vector<int>	y;
public:
  int	getFrontX();
  int	getFrontY();
  void	delFront();
  void	appendStep(int px, int py);
  int	isEmpty();
};

class	Pacman : public Igame
{
  IDisplay	*_lib;
  std::string	playerName = "";
  std::string	gameName = "Pacman";
  std::string	mapTex = "./games/PacMan/PacManTexture.png";
  std::string	spriteTex = "./games/PacMan/PacManSprite.png";
  std::string	chomp = "./games/PacMan/Sounds/pacman_chomp.wav";
  std::string	begin = "./games/PacMan/Sounds/pacman_beginning.wav";
  std::string	death = "./games/PacMan/Sounds/pacman_death.wav";
  std::string	eF = "./games/PacMan/Sounds/pacman_eatfruit.wav";
  std::string	eG = "./games/PacMan/Sounds/pacman_eatghost.wav";
  std::string	eEP = "./games/PacMan/Sounds/pacman_extrapac.wav";
  std::string	intermission = "./games/PacMan/Sounds/pacman_intermission.wav";
  std::string	siren = "./games/PacMan/Sounds/pacman_siren.wav";
  int		tmpx;
  int		tmpy;
  int		_score = 0;
  int		_highscore[5];
  std::string	_names[5];
  int		newHighscore;
  int		_combo = 0;
  int		_gPoints[4] = {200, 400, 800, 1600};
  int		_fPoints[8] = {100, 300, 500, 700, 1000, 2000, 3000, 5000};
  mapInfoP	**_map;
  direction     lastDir = LEFT;
  direction	curDir = LEFT;
  float		pPosX = 14.5;
  float		pPosY = 23.0;
  float		gPosX[4] = {14.0, 13.0, 14.0, 15.0};
  float		gPosY[4] = {13.0, 14.0, 14.0, 14.0};
  direction	gCurDir[4] = {DOWN, DOWN, DOWN, DOWN};
  direction	gLastDir[4] = {DOWN, DOWN, DOWN, DOWN};
  Stat		pStat = NORMAL;
  Stat		gStat[4] = {NORMAL, NORMAL, NORMAL, NORMAL};
  int		_credit = 2;
  int		_life = 3;
  int		_gameover = 0;
  int		count = 0;
  int		_timer;
  int		_gTimer;
  Path		*gPath[4];
  int		_exit = 0;
  std::chrono::time_point<std::chrono::system_clock> _tSpBegin;
  std::chrono::time_point<std::chrono::system_clock> _tgBegin;
  std::chrono::time_point<std::chrono::system_clock> _tfBegin;
  std::chrono::time_point<std::chrono::system_clock> _tNow;
  int		_lastEat;
  int		_lvl = 0;
public:
  Pacman(IDisplay*);
  virtual ~Pacman();
  virtual int	lastEat();
  virtual std::string	getChomp();
  virtual std::string	getBegin();
  virtual std::string	getDeath();
  virtual std::string	getEF();
  virtual std::string	getEG();
  virtual std::string	getEEP();
  virtual std::string	getIntermission();
  virtual std::string	getSiren(){return siren;}
  float	getCosts(int,int,int,int);
  void	getRandPos(int);
  void	swpanFruit();
  direction	getPathDir(int, int, int);
  int	timeDiff(int i);
  void	loadMap();
  bool	checkColision(int, int, direction);
  bool	checkPColision(int, int, direction);
  void	setDir(direction);
  void	setGDir(direction, int);
  void	updatePPos();
  void	updateGPos();
  void	moveG();
  virtual int	Play();
  void	move(direction, float&, float&, float);
  void	checkWarp(direction, float&, float&);
  void	eat();
  void	loadHighscore();
  int	checkGhostPos();
  int	checkRespawn(float,float);
  void	genHighscore();
  void	pacmanDeath();
  int	checkWin();
  void	reset();
  void	pRespawn();
  void	getGObjectif(int gId);
  int	pLook(int);
  int	pLook2(int,int,int,int,int,int,int);
  void	gPredicPPos(int, int);

  void	rmInCL(Node*);
  void	rmInOL(Node*);
  Node	*getInOL();
  bool	isInCloseList(Node*);
  Node	*nodeInCloseList(Node*);
  bool	isInOpenList(Node*);
  Node	*nodeInOpenList(Node*);
  std::list<Node*>	getAdjacent(Node*);
  Path	*findPath(int,int,int,int);
  void  addAdjsToOpenList(std::list<Node*>, Node*);
  Path	*calcPath(Node*);

  mapInfoP	**getMapP();
  int		getLvl();
  void		spawnFruit();
  int		getHighscore();
  int		getScore();
  int		getLife();
  int		getCredits();
  float		getPPosX();
  float		getPPosY();
  int		getPLastDir() {return lastDir;}
  float		getGPosX(int gId);
  float		getGPosY(int gId);
  int		getGLastDir(int gId);
  int		getGStat(int gId);
  int		getGameover();
  int		getTimer();
  std::string	getGameName();
  std::string	getMapTex();
  std::string	getSpriteTex();
  virtual void	setGameover(int);
  virtual void	setPlayerName(std::string);
  virtual IDisplay	*getLib();
  virtual void		setLib(IDisplay*);
  
  virtual mapInfo	**getMap() {}
  virtual direction	getDir() {}
  virtual std::string	getBlockTex() {}
  virtual std::string	getFoodTex() {}
  virtual int		can_change_key(const direction&) {}
  virtual void		my_sleep(float);
  virtual void		setBoost(int) {}
};

#endif /*!PACMAN_HPP*/
