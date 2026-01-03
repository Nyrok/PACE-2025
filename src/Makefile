CX = gcc
CXFLAGS = -Wall -Werror -Wextra -I includes -O3 -std=c99 -flto

LIBFT_DIR = libs/libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_SRCS = $(wildcard $(LIBFT_DIR)/*.c)

SRCS = core/main.c \
		core/utils/parser.c \
		core/utils/time.c \
		core/utils/logger.c \
		core/struct/graph.c \
		core/struct/covers.c \
		core/solvers/solver.c \
		core/solvers/sorter.c \
		core/solvers/optimizer.c \
		core/solvers/greedy.c \
		core/solvers/periphery_greedy.c \
		core/solvers/prune.c \
		core/solvers/swap.c \
        $(LIBFT_SRCS)

OBJDIR = objs
OBJS = $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

NAME = ds_finder

NO = 001
REDIN = < tmp/instances/heuristic_$(NO).gr
REDOUT = > out/heuristic_$(NO).sol

all: $(NAME)

$(NAME): $(OBJS)
	$(CX) $(CXFLAGS) $(OBJS) -o $(NAME)

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

binary_solution: re
	tar -czf $(NAME).tgz $(NAME)

source_solution: all fclean
	tar -czf $(NAME).tgz Makefile includes libs $(SRCS)

unify: re
	$(CX) $(CXFLAGS) -E core/main.c -o $(NAME).c

.PHONY: all clean fclean re
