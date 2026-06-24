# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/10 11:54:19 by leramos-          #+#    #+#              #
#    Updated: 2026/06/24 15:06:41 by leramos-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Project structure
NAME = cub3D
SRCS_DIR = src
INCS_DIR = include

# Libft structure
LIBFT_DIR = libft
LIBFT_SRCS_DIR = $(LIBFT_DIR)/src
LIBFT_INCS_DIR = $(LIBFT_DIR)/include
LIBFT_LIB = $(LIBFT_DIR)/libft.a

# MiniLibX structure
MLX_DIR = minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx.a
MLX_DEPENDENCIES = -lXext -lX11 -lm

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(INCS_DIR) -I$(LIBFT_INCS_DIR) -I$(MLX_DIR)
AR = ar rcs
RM = rm -f

# Files
MAIN 			= 	main exit
PARSING 		= 	init colours_parsing, file_utils, file_validation \
					map normalize utils
RUNTIME 		= 	game events render utils

FILES 			= 	$(MAIN) \
					$(addprefix runtime/, $(RUNTIME))
SRCS 			= 	$(addprefix $(SRCS_DIR)/, $(addsuffix .c, $(FILES)))
OBJS 			= 	$(SRCS:.c=.o)

SRCS = $(addprefix $(SRCS_DIR)/, $(addsuffix .c, $(FILES)))
OBJS = $(SRCS:.c=.o)

# Rules
all: $(LIBFT_LIB) $(NAME)

$(LIBFT_LIB):
	@make -C $(LIBFT_DIR)

$(MLX_LIB):
	@make -C $(MLX_DIR)

$(NAME): $(OBJS) $(LIBFT_LIB) $(MLX_LIB)
	$(CC) $(CFLAGS) $^ -L$(MLX_DIR) $(MLX_DEPENDENCIES) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make -C $(LIBFT_DIR) clean
	@make -C $(MLX_DIR) clean
	$(RM) $(OBJS)

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	@make -C $(MLX_DIR) clean
	$(RM) $(NAME)

re: fclean all

# Phony targets
.PHONY: all bonus clean fclean re