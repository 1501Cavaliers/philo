NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread
MY_SOURCES = main.c \
		utils.c \
		parsing.c \
		init.c \

MY_OBJECTS = $(MY_SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(MY_OBJECTS)
	$(CC) $(CFLAGS) -o $(NAME) $(MY_OBJECTS)

# $(MY_OBJECTS)/%.o: $(MY_SOURCES)/%.c
# 	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(MY_OBJECTS)

fclean: clean
	rm -rf $(NAME)

re: fclean all