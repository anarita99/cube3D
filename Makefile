# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adores <adores@student.42lisboa.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/10 11:54:19 by leramos-          #+#    #+#              #
#    Updated: 2026/08/10 15:51:48 by adores           ###   ########.fr        #
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
MLX_REPO := https://github.com/42paris/minilibx-linux.git

# Commands and flags
CC = cc
CFLAGS = -g -Wall -Wextra -Werror -O2 -I$(INCS_DIR) -I$(LIBFT_INCS_DIR) -I$(MLX_DIR)
AR = ar rcs
RM = rm -f
RUN = ./$(NAME) ${MAP}
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes --quiet --tool=memcheck --keep-debuginfo=yes

# Files
MAIN			=	main init exit
PARSING			=	parsing file_validation file_utils \
					colors textures utils \
					map_validation map_grid map_normalize
RUNTIME			=	game events render utils draw initialization \
					movement raycast

FILES			=	$(MAIN) \
					$(addprefix parsing/, $(PARSING)) \
					$(addprefix runtime/, $(RUNTIME))

SRCS			=	$(addprefix $(SRCS_DIR)/, $(addsuffix .c, $(FILES)))
OBJS			=	$(SRCS:.c=.o)

MAP				?=	maps/map.cub

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
	$(RM) $(NAME)

re: fclean all

mlx:
	git clone $(MLX_REPO) $(MLX_DIR)

go: ${NAME}
	${RUN}

valgrind: ${NAME}
	${VALGRIND} ${RUN}

# Phony targets
.PHONY: all bonus clean fclean re