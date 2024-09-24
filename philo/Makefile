CC := gcc
SA := --fsanitize=thread
CFLAGS := -g3 -Wall -Wextra -Werror -pthread -fsanitize=thread
EXEC := philo
SRCS := main.c validate_args.c utils.c print_actions.c init_data.c threads.c forks.c actions.c mutex.c time.c philo_routine.c monitor_routine.c
OBJS := $(SRCS:.c=.o)

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