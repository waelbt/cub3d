# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/30 12:43:19 by waboutzo          #+#    #+#              #
#    Updated: 2022/12/10 17:36:16 by waboutzo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	cub3D

LIBFT	=	src/libft/libft.a

RM		=	rm -rf

CC		=	cc

HEADER	=	src/include/cub3D.h

CFLAGS	=	-Wall -Wextra -Werror -g -fsanitize=address #-lmlx -framework OpenGL -framework AppKit  #

TOOLS	=	get_next_line get_next_line_utils

PARSING	=	cubscene

LEXER	=	lexer

SRCS	= 	$(addsuffix .c, $(addprefix src/tools/, $(TOOLS))) \
			$(addsuffix .c, $(addprefix src/parsing/, $(PARSING))) \
			$(addsuffix .c, $(addprefix src/lexer_tokens/, $(LEXER)))

OBJ		=	$(SRCS:.c=.o)
	
.c.o:
	@$(CC)  $(CFLAGS) -c $< -o $@

all : $(NAME)

$(NAME): $(HEADER) main.c $(LIBFT) $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) main.c -o $(NAME)

$(LIBFT) :
	@make -C src/libft
clean :
#@make clean -C src/libft
	@$(RM) $(OBJ)

fclean : clean
#@make fclean -C src/libft
	@$(RM) $(NAME)

re : fclean all

.PHONY:			all clean fclean re bonus