NAME= philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=thread

SRCS = philo.c philo_routine.c monitor_routine.c utils.c utils1.c simulation.c
OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c ./philo.h
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
