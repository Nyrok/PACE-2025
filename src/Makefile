CX = gcc
CXFLAGS = -Wall -Werror -Wextra -I includes -g3 -std=c99
SRCS = src/main.c \
	   src/utils/parser.c \
	   src/struct/graph.c \
	   libs/gnl/get_next_line.c \

OBJDIR = objs
OBJS = $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

LIBFT_DIR = libs/libft
LIBFT = $(LIBFT_DIR)/libft.a

NAME = ds_finder

SIZE = 20
OUT = > out/bremen_subgraph_$(SIZE).sol

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
	rm -f $(LIBFT)

re: fclean all

test: all
	./$(NAME) < testset/bremen_subgraph_$(SIZE).gr > out/bremen_subgraph_$(SIZE).sol

leaks: all
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME) < testset/bremen_subgraph_$(SIZE).gr > out/bremen_subgraph_$(SIZE).sol

.PHONY: all clean fclean re