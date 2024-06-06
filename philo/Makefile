CC := cc
CFLAGS = -Wall -Wextra -Werror $(DEBUG_FLAGS)
DEBUG_FLAGS =
ifeq ($(DEBUG), 1)
	DEBUG_FLAGS = -g -DDEBUG=1
	export DEBUG
endif

NAME := philo

SRC := philo.c start.c libft.c

OBJ := $(SRC:.c=.o)
DEP := $(SRC:.c=.d)

C_GRAY := \033[1;30m
C_ORANGE := \033[0;33m
C_RED := \033[0;31m
C_CYAN := \033[0;36m
NC := \033[0m

PREFIX := $(C_ORANGE)<$(NAME)>$(NC)

all: $(NAME)

debug: fclean debug_cflags $(NAME)

debug_cflags:
	@$(eval DEBUG_FLAGS = -g -DDEBUG=1)
	@$(eval export DEBUG=1)

$(NAME): $(OBJ)
	@printf "$(PREFIX) CREATING $(C_CYAN)$@$(NC)\n"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

-include $(DEP)

%.o: %.c
	@printf "$(PREFIX) $(C_GRAY)COMPILING $(C_CYAN)$@$(NC)\n"
	@$(CC) $(CFLAGS) -MMD -c $< -o $@

clean:
	@printf "$(PREFIX) $(C_RED)REMOVING OBJECT FILES$(NC)\n"
	@rm -f $(OBJ) $(DEP)

fclean: clean
	@printf "$(PREFIX) $(C_RED)REMOVING ARCHIVE$(NC)\n"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
