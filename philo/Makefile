CC := gcc
SA := --fsanitize=thread
CFLAGS := -g3 -Wall -Wextra -Werror -pthread

EXEC := philo
SRCS := main.c validate_args.c init_data.c utils.c print.c create_threads.c forks.c handle_mutexes.c philo.c mutex.c
OBJS := $(SRCS:.c=.o)

INCS := 

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXEC)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(EXEC)

re: fclean all

.PHONY: all clean fclean re

valgrind: all
	valgrind --leak-check=full --show-leak-kinds=all ./$(EXEC) 5 5 5 5 5
