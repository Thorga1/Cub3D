# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tordner <tordner@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/14 15:28:00 by tordner           #+#    #+#              #
#    Updated: 2025/08/13 19:58:51 by tordner          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := cub3D

OS := $(shell uname)

SRC_DIR := srcs
OBJ_DIR := objs

SRCS := $(wildcard $(SRC_DIR)/*.c $(SRC_DIR)/*/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

CC := cc
CFLAGS := -Wall -Wextra -Werror -Iincludes -g3 -MMD -MP

ifeq ($(OS), Linux)
	MLX_PATH := ./mlx_linux
	MLX := $(MLX_PATH)/libmlx.a
	CFLAGS += -Imlx_linux
	LIBS := -Lmlx_linux -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz
else
	MLX_PATH := ./mlx
	MLX := $(MLX_PATH)/libmlx.a
	CFLAGS += -Imlx
	LIBS := -L$(MLX_PATH) -lmlx -framework OpenGL -framework AppKit
endif

all: $(NAME)

$(NAME): $(OBJS) $(MLX)
	$(CC) $(OBJS) $(LIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(MLX):
	$(MAKE) -C $(MLX_PATH)

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(MLX_PATH) clean

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re