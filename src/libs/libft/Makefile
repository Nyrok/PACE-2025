# Compiler
CX = cc

# Compiler flags
CXFLAGS = -Wall -Wextra -Werror -I ../../includes -g3

NAME =		libft.a
SRCS = ft_atoi.c \
		ft_atoll.c \
		ft_bzero.c \
		ft_calloc.c \
		ft_isalnum.c \
		ft_isalpha.c \
		ft_isascii.c \
		ft_isdigit.c \
		ft_isprint.c \
		ft_itoa.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_memset.c \
		ft_putchar_fd.c \
		ft_putnbr_fd.c \
		ft_putendl_fd.c \
		ft_putstr_fd.c \
		ft_split.c \
		ft_strchr.c \
		ft_strdup.c \
		ft_striteri.c \
		ft_strlcat.c \
		ft_strlcpy.c \
		ft_strlen.c \
		ft_strmapi.c \
		ft_strncmp.c \
		ft_strnstr.c \
		ft_strrchr.c \
		ft_strtrim.c \
		ft_substr.c \
		ft_tolower.c \
		ft_toupper.c \
		ft_strcmp.c \
		ft_strjoin.c \
		ft_isspace.c

OBJDIR = ../../objs/libs/libft
OBJS = $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

all:	${NAME}

${NAME}:	${OBJS}
	ar rcs ${NAME} ${OBJS}

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CX) $(CXFLAGS) -c $< -o $@

.c.o:
	${CX} ${CXFLAGS} -I ../includes -c $< -o $@

clean:
	rm -rf ${OBJDIR}

fclean:	clean
	rm -f ${NAME}

re:	fclean all

.PHONY:	all clean fclean re
