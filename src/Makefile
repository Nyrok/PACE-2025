CX = cc
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

all: $(LIBFT) $(NAME)

$(NAME): $(OBJS)
	$(CX) $(OBJS) -L $(LIBFT_DIR) -lft -o $(NAME)
	
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

test:
	./$(NAME) < ../testset/bremen_subgraph_20.gr

.PHONY: all clean fclean re