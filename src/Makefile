CX = gcc
CXFLAGS = -Wall -Werror -Wextra -I includes -g3 -std=c99
STATIC_FLAG = -static

LIBFT_DIR = libs/libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_SRCS = $(wildcard $(LIBFT_DIR)/*.c)

SRCS = src/main.c \
		src/utils/parser.c \
		src/core/graph.c \
		src/core/solver.c \
		libs/gnl/get_next_line.c \
        $(LIBFT_SRCS)

OBJDIR = objs
OBJS = $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

NAME = ds_finder

NO = 001
REDIN = < tmp/instances/heuristic_$(NO).gr
REDOUT = > out/heuristic_$(NO).sol

all: $(NAME)

$(NAME): $(OBJS)
	$(CX) $(CXFLAGS) $(STATIC_FLAG) $(OBJS) -o $(NAME)

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CX) $(CXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)
	rm -f $(NAME).tgz
	rm -f $(NAME).c

re: fclean all

test: all
	./$(NAME) $(REDIN) $(REDOUT)

leaks: all
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME) $(REDIN) $(REDOUT)
	./$(NAME) $(REDIN) $(REDOUT)

solution: re fclean
	tar -czf $(NAME).tgz Makefile includes libs $(SRCS)

unify: re
	$(CX) $(CXFLAGS) -E src/main.c -o $(NAME).c

.PHONY: all clean fclean re