NAME = PmergeMe
CC = c++
CFLAGZ = -Wall -Wextra -Werror -std=c++98 -Iinclude -g
SRCS = main.cpp PmergeMe.cpp

OBJS = $(SRCS:.cpp=.o)

%.o: %.cpp
	$(CC) $(CFLAGZ) -g -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(CC)	$(CFLAGZ)	-o	$(NAME)	$(OBJS) 

clean:
	rm -f $(OBJS) 

fclean: clean
	rm -f $(NAME)
	
re: fclean all