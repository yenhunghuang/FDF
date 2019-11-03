# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yehuang <yenhang1@gmail.co>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/17 19:27:32 by yehuang           #+#    #+#              #
#    Updated: 2019/10/28 23:17:12 by yehuang          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	fdf

NOC		=	\033[0m
GREEN	=	\033[0;32m
BLUE	=	\033[0;34m
RED		=	\033[0;31m

SRC		= main.c draw.c setup.c transform.c handler.c

OBJ		= $(addprefix $(OBJDIR),$(SRC:.c=.o))

CC		= gcc
C_FLAGS = -Wall -Wextra -Werror

MLX		= ./minilibx_macos/
MLX_LIB	= $(addprefix $(MLX),mlx.a)
MLX_INC	= -I ./minilibx_macos
MLX_LNK	= -L ./minilibx_macos -l mlx -framework OpenGL -framework AppKit

FT		= ./libft/
FT_LIB	= $(addprefix $(FT),libft.a)
FT_INC	= -I ./libft
FT_LNK	= -L ./libft -l ft

SRCDIR	= ./srcs/
INCDIR	= ./includes/
OBJDIR	= ./objs/

all: obj $(FT_LIB) $(MLX_LIB) $(NAME)

obj:
	@mkdir -p $(OBJDIR)

$(OBJDIR)%.o:$(SRCDIR)%.c
		@$(CC) $(CFLAGS) $(MLX_INC) $(FT_INC) -I $(INCDIR) -o $@ -c $<

$(FT_LIB):
		@make -C $(FT)

$(MLX_LIB):
		@make -C $(MLX)

$(NAME): $(OBJ)
		@$(CC) $(OBJ) $(MLX_LNK) $(FT_LNK) -lm -o $(NAME)
		@echo "$(GREEN)FDF ✓ fdf ready$(NOC)"

clean:
		@rm -rf $(OBJDIR)
		@make -C $(FT) clean
		@make -C $(MLX) clean
		@echo "$(BLUE)FDF ✓ Removed .o files$(NOC)"

fclean: clean
		@make -C $(FT) fclean
		@rm -rf $(NAME)
		@echo "$(RED)FDF ✓ Removed fdf executable$(NOC)"

re: fclean all

.PHONY: all, $(NAME), clean, fclean, re
