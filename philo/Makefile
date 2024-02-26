NAME = philo

SRCS = main.c ft_atoi.c utils.c init.c 

OBJS = $(SRCS:.c=.o)

CC = cc -Wall -Wextra -Werror

RM = rm -f

%.o : %.c philo.h 
	$(CC) -c $< -o $(<:.c=.o)

$(NAME) : $(OBJS)
	$(CC) -pthread $(OBJS) -o $(NAME)

all : $(NAME)

clean : 
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : clean