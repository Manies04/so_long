# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tiade-al <tiade-al@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/04 12:42:38 by tiade-al          #+#    #+#              #
#    Updated: 2024/09/10 14:15:57 by tiade-al         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Source files
SRCS	= main.c get_next_line.c get_next_line_utils.c animation.c \
background.c checkers.c helpers.c img_resizer.c initializer.c map_setup.c

# Object files
OBJS	= $(SRCS:.c=.o)

# Compiler and flags
CC			= cc
RM			= rm -f
CFLAGS		= -Wall -Wextra -Werror -I -Imlx_linux -g
LIBFT_PATH	= ./Libft
LIBFT		= $(LIBFT_PATH)/libft.a
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
				$(RM) $(NAME)
				$(MAKE) -C $(LIBFT_PATH) fclean

# Rebuild everything
re:	fclean all

# Phony targets
.PHONY:	all clean fclean re libft
