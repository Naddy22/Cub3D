NAME 	:= cub3D
CFLAGS	:= -Wextra -Werror -Wall

GITMLX	:= https://github.com/codam-coding-college/MLX42.git
LIBMLX 	:= ./lib/MLX42
LIBFT	:= ./lib/libft

# BREW	:= /Users/$(USER)/.brew
BREW	:= $(shell brew --prefix)#va chercher directement le bon brew
CMAKE	:= $(BREW)/opt/cmake
GLFW	:= "$(BREW)/opt/glfw/lib/"

HEADERS	:= -I./include -I$(LIBMLX)/include -I$(LIBFT)/include
LIBS	:= $(LIBMLX)/build/libmlx42.a $(LIBFT)/libft.a -lglfw -L$(GLFW)
SRCDIR	:= ./src
OBJDIR	:= ./obj

SRCS	:=	main.c \
			parsing.c \
			error.c \
			init.c \
			identifiers.c \
			color.c \
			free.c \
			utils.c \
			mlx.c \

# -- COLORS -- #
BLACK=\033[0;30m# Black
RED=\033[0;31m# Red
GREEN=\033[0;32m# GREEN
YELLOW=\033[0;33m# YELLOW
BLUE=\033[0;34m# BLUE
PURPLE=\033[0;35m# PURPLE
CYAN=\033[0;36m# CYAN
WHITE=\033[0m# WHITE

BOLD=\033[1m

OBJS	:= $(addprefix $(OBJDIR)/, ${SRCS:.c=.o})

all: $(NAME)


$(LIBMLX):
	@git clone $(GITMLX) $(LIBMLX)
	@curl -fsSL https://raw.githubusercontent.com/Naddy22/Script/master/Brew_check.sh | zsh

$(LIBMLX)/build: $(LIBMLX)
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

$(LIBFT)/libft.a:
	@make -C$(LIBFT)

$(OBJDIR):
	@mkdir $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@cc $(CLFAGS) -o $@ -c $< $(HEADERS) \
		&& printf "$(GREEN)$(BOLD)Compiling:$(WHITE) $(notdir $<)\n"

$(NAME): $(LIBMLX)/build $(LIBFT)/libft.a $(OBJDIR) $(OBJS)
	@cc $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

clean:
	@rm -rf $(OBJDIR)
	@make -C$(LIBFT) clean

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(LIBFT)/libft.a
	@rm -rf $(LIBMLX)/build

ffclean: fclean
	@rm -rf $(LIBMLX)

re: fclean all

.PHONY: all, clean, fclean, re
