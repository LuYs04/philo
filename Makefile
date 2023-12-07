NAME = philo

SRC =	philo.c			\
		philo_utils.c	\
		data_init.c		\
		philo_acting.c

OBJ = $(SRC:.c=.o)

RM = rm -rf

CC = cc

CFLAGS = -Wall -Wextra -Werror #-fsanitize=thread

all : $(NAME)

$(NAME) : $(OBJ)
		$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o : %.c
		$(CC) $(CFLAGS) -c $< -o $@

clean :
		$(RM) $(OBJ)

fclean : clean
		$(RM) $(NAME)

re : fclean all

.PHONY: re, all, fclean, clean
