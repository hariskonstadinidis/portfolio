NAME	:= philo
CFLAGS	:= -Wextra -Wall -Werror -g

HEADERS	:= -I ./include

SRCS	:=  src/philosophers.c src/initialize.c src/input_check.c src/utils.c src/free.c \
			src/simulation.c

GREEN = \033[1;32m
BLUE = \033[1;34m
RESET = \033[0m

OBJ_DIR	:= objects
OBJS 	:= $(patsubst src/%.c,$(OBJ_DIR)/%.o,$(SRCS))


all: $(NAME)

$(OBJ_DIR)/%.o : src/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@
	@printf "$(GREEN).$(RESET)"

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(HEADERS) -o $(NAME)

clean:
	@printf "$(BLUE)Cleaned Up$(RESET)\n"
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
