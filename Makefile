# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tiade-al <tiade-al@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/04 12:42:38 by tiade-al          #+#    #+#              #
#    Updated: 2024/09/24 14:45:51 by tiade-al         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

SRC = main.c get_next_line.c get_next_line_utils.c animation.c \
background.c checkers.c helpers.c img_resizer.c initializer.c map_setup.c size.c

CC = @cc

CFLAGS = -Wall -Wextra -Werror -g
MLXFLAGS = -L. -lXext -L. -lX11

LIBFT_PATH = ./Libft
LIBFT = $(LIBFT_PATH)/libft.a

MINILIBX_PATH = ./minilibx-linux
MINILIBX = $(MINILIBX_PATH)/libmlx.a

OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(MINILIBX) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MINILIBX) $(MLXFLAGS) -o $(NAME)

$(LIBFT):
	@echo " [ .. ] | Compiling libft.."
	@make -s -C $(LIBFT_PATH)
	@echo " [ OK ] | Libft ready!"

$(MINILIBX):
	@echo " [ .. ] | Compiling minilibx.."
	@make -s -C $(MINILIBX_PATH)
	@echo " [ OK ] | Minilibx ready!"

clean:
	@rm -f $(OBJS)
	@echo "object files removed."
	
fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFT_PATH)
	@echo "all files created were removed."

re: fclean all

.PHONY:	all clean fclean re