NAME 	:= cub3D
CFLAGS	:= -Wextra -Werror -Wall

GITMLX	:= https://github.com/codam-coding-college/MLX42.git
LIBMLX 	:= ./lib/MLX42
LIBFT	:= ./lib/libft

BREW	:= /Users/$(USER)/.brew
CMAKE	:= $(BREW)/opt/cmake
GLFW	:= $(BREW)/opt/glfw/lib/

HEADERS	:= -I./include -I$(LIBMLX)/include -I$(LIBFT)/include
LIBS	:= $(LIBMLX)/build/libmlx42.a $(LIBFT)/libft.a -lglfw -L$(GLFW)
SRCDIR	:= ./src
OBJDIR	:= ./obj

SRCS	:= 
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
		&& printf "\e[1;32mCompiling:\e[0m $(notdir $<)\n"

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
