##
## Makefile for Arcade in /home/meyrie_g/rendu/cpp_arcade
## 
## Made by Gabin Meyrieux-Drevet
## Login   <meyrie_g@epitech.net>
## 
## Started on  Mon Mar 13 14:29:31 2017 Gabin Meyrieux-Drevet
## Last update Sun Apr  9 17:57:47 2017 Christophe Mei
##

SRC	= src/gsdlloader.cpp\
	src/dlloader.cpp\
	src/core.cpp

SRCPACMAN	= games/PacMan/Pacman.cpp\
		games/PacMan/Play.cpp\
		games/PacMan/pGet.cpp\
		games/PacMan/node.cpp

SRCSNAKE	= games/Snake/get_set_snake.cpp\
		games/Snake/Snake.cpp\
		games/Snake/Play.cpp

SRCSFML		= lib/SFML/menu.cpp\
		lib/SFML/sfml_pacman.cpp\
		lib/SFML/sfml.cpp

SRCNCURSES	= lib/ncurses/menu.cpp\
		lib/ncurses/ncurses.cpp\
		lib/ncurses/ncurses_pacman.cpp

SRCOPENGL	= lib/openGL/menu.cpp\
		lib/openGL/openGL.cpp\
		lib/openGL/score.cpp\
		lib/openGL/openGL_pacman.cpp\

NAMEPACMAN	= ./games/lib_arcade_pacman.so

NAMESNAKE	= ./games/lib_arcade_snake.so

NAMESFML	= ./lib/lib_arcade_sfml.so

NAMENCURSES	= ./lib/lib_arcade_ncurses.so

NAMEOPENGL	= ./lib/lib_arcade_opengl.so

NAME	= arcade

CC	= g++

RM	= rm -f

OBJ		= $(SRC:.cpp=.o)

OBJPACMAN	= $(SRCPACMAN:.cpp=.o)

OBJSNAKE	= $(SRCSNAKE:.cpp=.o)

OBJSFML		= $(SRCSFML:.cpp=.o)

OBJNCURSES	= $(SRCNCURSES:.cpp=.o)

OBJOPENGL	= $(SRCOPENGL:.cpp=.o)

INCLUDE	= -I/SFML-2.4.2/include

LIBSFML	= -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

LIBNCURSES	= -lncurses

LIBOPENGL	= -lGL -lGLU -lSDL -lSDL_ttf -lSDL_image

LIBDL	= -ldl

CPPFLAGS	+= -fpic

all : $(NAMESNAKE) $(NAMEPACMAN) $(NAME)

lib : $(NAMESFML) $(NAMENCURSES) $(NAMEOPENGL)

$(NAMEPACMAN) : $(OBJPACMAN)
	$(CC) -shared -o $(NAMEPACMAN) $(OBJPACMAN) $(LIB)

$(NAMESNAKE) : $(OBJSNAKE)
	$(CC) -shared -o $(NAMESNAKE) $(OBJSNAKE)

$(NAMESFML) : $(OBJSFML)
	$(CC) -shared -o $(NAMESFML) $(OBJSFML) $(LIBSFML)

$(NAMENCURSES) : $(OBJNCURSES)
	$(CC) -shared -o $(NAMENCURSES) $(OBJNCURSES) $(LIBNCURSES)

$(NAMEOPENGL) : $(OBJOPENGL)
	$(CC) -shared -o $(NAMEOPENGL) $(OBJOPENGL) $(LIBOPENGL)

$(NAME) : $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LIBDL)

clean :
	$(RM) $(OBJ)
	$(RM) $(OBJPACMAN)
	$(RM) $(OBJSNAKE)
	$(RM) $(OBJSFML)
	$(RM) $(OBJNCURSES)
	$(RM) $(OBJOPENGL)

fclean : clean
	$(RM) $(NAME)
	$(RM) $(NAMEPACMAN)
	$(RM) $(NAMESNAKE)
	$(RM) $(NAMESFML)
	$(RM) $(NAMENCURSES)
	$(RM) $(NAMEOPENGL)

re : fclean all

.PHONY : all clean fclean re
