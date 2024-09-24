# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tiade-al <tiade-al@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/04 12:42:38 by tiade-al          #+#    #+#              #
#    Updated: 2024/09/24 12:50:44 by tiade-al         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Source files
SRCS	= main.c get_next_line.c get_next_line_utils.c animation.c \
background.c checkers.c helpers.c img_resizer.c initializer.c map_setup.c size.c

# Object files
OBJS	= $(SRCS:.c=.o)

# Compiler and flags
CC			= cc
RM			= rm -f
CFLAGS		= -I -Imlx_linux -g -Wall -Wextra -Werror 
LIBFT_PATH	= ./Libft
LIBFT		= $(LIBFT_PATH)/libft.a
MLX = ./minilibx-linux
LIBS		= -Lminilibx-linux -lmlx_Linux -L$(LIBFT_PATH) -lft -lX11 -lXext

# Output library name
NAME	= so_long

# Default target
all:	$(NAME)

# Compilation rule for object files
%.o: %.c
				$(CC) $(CFLAGS) -c $< -o $@

# Linking rule for the final executable
$(NAME):	$(OBJS) $(LIBFT)
				@ make -C $(MLX)
				$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

# Build the Libft library
$(LIBFT):
				$(MAKE) -C $(LIBFT_PATH)

# Clean up object files
clean:
				$(RM) $(OBJS)
				$(MAKE) -C $(LIBFT_PATH) clean

# Clean up all generated files
fclean:	clean
				@ make clean -C $(MLX)
				$(RM) $(NAME)
				$(MAKE) -C $(LIBFT_PATH) fclean

# Rebuild everything
re:	fclean all

# Phony targets
.PHONY:	all clean fclean re libft