NAME_B = philo_bonus

SRCS_B = main_bonus.c ft_atoi_bonus.c utils_bonus.c init_bonus.c utils2_bonus.c

OBJS_B = $(SRCS_B:.c=.o)

CC = cc -Wall -Wextra -Werror

RM = rm -f

%.o : %.c philo_bonus.h 
	$(CC) -c $< -o $(<:.c=.o)

$(NAME_B) : $(OBJS_B)
	$(CC) -pthread $(OBJS_B) -o $(NAME_B)

bonus : $(NAME_B)

all : bonus

clean : 
	$(RM) $(OBJS_B)

fclean : clean
	$(RM) $(NAME_B)

re : fclean bonus

.PHONY : clean