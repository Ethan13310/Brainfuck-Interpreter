#
# Makefile for Brainfuck Interpreter
#

CXXFLAGS	=	-O2 -std=c++14

CPPFLAGS	=	-I ./include

SRC			=	src/BFParser.cpp	\
				src/Main.cpp

OBJ			=	$(SRC:.cpp=.o)

NAME		=	brainfck

$(NAME):	$(OBJ)
			$(CXX) $(OBJ) -o $(NAME)

all:		$(NAME)

clean:
			rm -f $(OBJ)

fclean:		clean
			rm -f $(NAME)

re:			fclean all
