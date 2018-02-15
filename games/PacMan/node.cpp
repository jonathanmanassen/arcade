//
// node.cpp for arcade in /home/meyrie_g/rendu/cpp_arcade/games/PacMan
// 
// Made by Gabin Meyrieux-Drevet
// Login   <meyrie_g@epitech.net>
// 
// Started on  Tue Apr  4 13:05:45 2017 Gabin Meyrieux-Drevet
// Last update Sun Apr  9 18:40:28 2017 Gabin Meyrieux-Drevet
//

#include <cmath>
#include <list>
#include <stdlib.h>
#include "Pacman.hpp"

#define	LEN 244

Node	*start;
Node	*goal;
std::vector<Node*>openList;
std::vector<Node*>closeList;

int	Path::getFrontX()
{
  return x.back();
}

int	Path::getFrontY()
{
  return y.back();
}

void	Path::delFront()
{
  x.pop_back();
  y.pop_back();
}

void	Path::appendStep(int px, int py)
{
  x.push_back(px);
  y.push_back(py);
}
int	Path::isEmpty()
{
  return x.size();
}

void	Pacman::my_sleep(float s)
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

float Pacman::getCosts(int x, int y, int tx, int ty)
{
  float dx = tx - x;
  float dy = ty - y;
  
  float result = sqrt(dx * dx + dy * dy);
  
  return result;
}

float Node::getCosts(int x, int y, int tx, int ty)
{
  float dx = tx - x;
  float dy = ty - y;
  
  float result = sqrt(dx * dx + dy * dy);
  
  return result;
}

Node	*Pacman::getInOL()
{
  Node	*tmp = new Node(1);
  int	save = 0;
  int	i = 0;
  for (Node *n : openList)
    {
      if (tmp->getFree() != 0)
	{
	  tmp = n;
	  save = i;
	}
      else if (tmp->compareTo(n) > 0)
	{
	  tmp = n;
	  save = i;
	}
      i++;
    }
  openList.erase(openList.begin()+save);
  return tmp;
}

Path *Pacman::findPath(int sx, int sy, int tx, int ty)
{
  start = new Node(sx, sy);
  goal = new Node(tx, ty);
  start->setCost(0.0);
  start->setRestCosts();
  start->setParent(NULL);
  start->setDepth(0);
  start->setFree(0);
  openList.push_back(start);
  goal->setParent(NULL);
  int maxDepth = 0;
  Node *current;
  while (openList.size() != 0)
    {
      current = getInOL();
      closeList.push_back(current);
      if ((current->getX() != 0 && current->getX() < 28) &&
	  (current->getY() != 0 && current->getY() < 30))
	addAdjsToOpenList(getAdjacent(current), current);
      if ((current->getX() == tx) && (current->getY() == ty))
	{
	  return calcPath(current);
	}
    }
  return NULL;
}

Path *Pacman::calcPath(Node  *current)
{
  Path *path = new Path;
  Node *target = current->getParent();
  while (target != start)
    {
      path->appendStep(target->getX(), target->getY());
      target = target->getParent();
    }
  path->appendStep(start->getX(), start->getY());
  openList.clear();
  closeList.clear();
  delete goal;
  delete start;
  return path;
}

Node	*Pacman::nodeInOpenList(Node *tmp)
{
  for (Node *n : openList)
    {
      if (*tmp == *n)
	return n;
    }
  return NULL;
}

Node	*Pacman::nodeInCloseList(Node *tmp)
{
  for (Node *n : closeList)
    {
      if (*tmp == *n)
	return n;
    }
  return NULL;
}

bool	Pacman::isInCloseList(Node *tmp)
{
  for (Node *n : closeList)
    {
      if (*tmp == *n)
	return true;
    }
  return false;
}

bool	Pacman::isInOpenList(Node *tmp)
{
  for (Node *n : openList)
    {
      if (*tmp == *n)
	return true;
    }
  return false;
}

void	Pacman::rmInOL(Node *tmp)
{
  int	i = 0;
  for (Node *n : openList)
    {
      if (*tmp == *n)
	openList.erase(openList.begin() + i);
      i++;
    }
}

void	Pacman::rmInCL(Node *tmp)
{
  int	i = 0;
  for (Node *n : closeList)
    {
      if (*tmp == *n)
	closeList.erase(closeList.begin() + i);
      i++;
    }
}

void Pacman::addAdjsToOpenList(std::list<Node*> currentAdjs, Node *current)
{
  for (Node *currentAdj : currentAdjs)
    {
      float nextStepCost = current->getCost() +
	getCosts(current->getX(), current->getY(), currentAdj->getX(), currentAdj->getY());
      Node *tmp;
      if ((isInOpenList(currentAdj)))
	{
	  tmp = nodeInOpenList(currentAdj);
	  if ((nextStepCost < tmp->getCost()))
	    rmInOL(currentAdj);
	}
      if ((isInCloseList(currentAdj)))
	{
	  tmp = nodeInCloseList(currentAdj);
	  if ((nextStepCost < tmp->getCost()))
	    rmInCL(currentAdj);
	}

      if ((!isInOpenList(currentAdj)) && (!isInCloseList(currentAdj)))
	{
	  currentAdj->setCost(nextStepCost);
	  currentAdj->setParent(current);
	  currentAdj->setRestCosts();
	  openList.push_back(currentAdj);
	}
    }
}

std::list<Node*> Pacman::getAdjacent(Node *current)
{
  std::list<Node*> currentAdjs;
  if (checkColision(current->getX(), current->getY(), UP))
    currentAdjs.push_front(new Node(current->getX(), current->getY() - 1));
  if (checkColision(current->getX(), current->getY(), DOWN))
    currentAdjs.push_front(new Node(current->getX(), current->getY() + 1));
  if (checkColision(current->getX(), current->getY(), LEFT))
    currentAdjs.push_front(new Node(current->getX() - 1, current->getY()));
  if (checkColision(current->getX(), current->getY(), RIGHT))
    currentAdjs.push_front(new Node(current->getX() + 1, current->getY()));
  return currentAdjs;
}

int Node::getX() const
{
  return x;
}

void Node::setX(int x)
{
  this->x = x;
}
    
int Node::getY() const
{
  return y;
}
    
void Node::setY(int y)
{
  this->y = y;
}
    
float Node::getCost() const
{
  return cost;
}
    
void Node::setCost(float cost)
{
  this->cost = cost;
}
    
float Node::getRestCost() const
{
  return restCost;
}
    
void Node::setRestCost(float restCost)
{
  this->restCost = restCost;
}
    
int Node::getDepth() const
{
  return depth;
}


void Node::setDepth(int depth)
{
  this->depth = depth;
}

Node::Node(int x, int y)
{
  this->x = x;
  this->y = y;
}

Node::~Node(){}

void Node::setCosts() {
  cost = getCosts(x, y, start->x, start->y);
}
    
void Node::setRestCosts()
{
  restCost = getCosts(x, y, goal->x, goal->y);
}
    
int Node::setParent(Node *parent)
{
  depth += 1;
  this->parent = parent;
  
  return depth;
}

Node	*Node::getParent()
{
  return parent;
}

Node	&Node::operator=(Node const &n)
{
  this->x = n.x;
  this->y = n.y;
  this->cost = n.cost;
  this->restCost = n.restCost;
  this->depth = n.depth;
  this->parent = n.parent;
  this->free = n.free;
  return *this;
}

bool	Node::operator==(Node const &n)
{
  if (getX() == n.getX() && getY() == n.getY())
    return true;
  return false;
}

bool	Node::operator!=(Node const &n)
{
  if (getX() == n.getX() && getY() == n.getY())
    return false;
  return true;
}

Node	&Node::operator=(Node *n)
{
  this->x = n->x;
  this->y = n->y;
  this->cost = n->cost;
  this->restCost = n->restCost;
  this->depth = n->depth;
  this->parent = n->parent;
  this->free = n->free;
  return *this;
}

bool	Node::operator==(Node *n)
{
  if (getX() == n->getX() && getY() == n->getY())
    return true;
  return false;
}

bool	Node::operator!=(Node *n)
{
  if (getX() == n->getX() && getY() == n->getY())
    return false;
  return true;
}

    
int Node::compareTo(Node *other)
{
  float f = restCost + cost;
  float of = other->restCost + other->cost;
      
  if (f < of)
    return -1;
  if (f > of)
    return 1;
  return 0;
}
