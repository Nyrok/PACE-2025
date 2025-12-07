CX = cc
CXFLAGS = -Wall -Werror -Wextra -I includes -g3 -std=c99
SRCS = main.c \
	   libs/get_next_line/get_next_line.c \
	   libs/get_next_line/get_next_line_utils.c

OBJDIR = objs
OBJS = $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

NAME = ds_finder

all: $(LIBFT) $(NAME)

$(NAME): $(OBJS)
	$(CX) $(OBJS) -o $(NAME)

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CX) $(CXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re