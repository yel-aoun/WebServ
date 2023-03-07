

NAME = Webserv

SRC = parsing/main.cpp parsing/webserv.cpp parsing/location.cpp parsing/server.cpp

CXX = c++

CPPFLAGS = -std=c++98 #-Wall -Wextra -Werror -std=c++98

OBJ = $(SRC:.cpp=.o)

all :$(NAME)

$(NAME) : $(OBJ)
	$(CXX) $(CPPFLAGS) $(SRC) -o $(NAME)

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re