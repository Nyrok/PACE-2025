CX = gcc
CXFLAGS = -static -Wall -Werror -Wextra -I includes -g3 -std=c99
SRCS = src/main.c \
		src/utils/parser.c \
		src/core/graph.c \
		src/core/solver.c \
		libs/gnl/get_next_line.c \

OBJDIR = objs
OBJS = $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

LIBFT_DIR = libs/libft
LIBFT = $(LIBFT_DIR)/libft.a

NAME = ds_finder

NO = 001
REDIN = < tmp/instances/heuristic_$(NO).gr
REDOUT = > out/heuristic_$(NO).sol

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CX) $(CXFLAGS) $(OBJS) -L $(LIBFT_DIR) -lft -o $(NAME)
	
$(LIBFT):
	make -C $(LIBFT_DIR)

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CX) $(CXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)
	rm -f $(NAME).tgz
	rm -f $(LIBFT)

re: fclean all

test: all
	./$(NAME) $(REDIN) $(REDOUT)

leaks: all
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME) $(REDIN) $(REDOUT)
	./$(NAME) $(REDIN) $(REDOUT)

solution: re
	tar -czf $(NAME).tgz $(NAME)

.PHONY: all clean fclean re