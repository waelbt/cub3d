NAME			=	cub3D

RM				=	rm -rf

CC				=	cc

HEADER			=	src/includes/cub3D.h

CFLAGS			=	-Wall -Wextra -Werror -fsanitize=address

GNL				=	get_next_line_utils get_next_line

LIBFT			=	src/general_tools/libft/libft.a

GENERAL_TOOLS	= $(addsuffix .c, $(addprefix src/general_tools/GNL/, $(GNL)))

LEXER			=	identifier_lexer lexer

TOOLS			=	filter_cases parse_function tools

PARSING			=  	src/parsing/cubscene_parsing.c \
					$(addsuffix .c, $(addprefix src/parsing/lexer/, $(LEXER))) \
					$(addsuffix .c, $(addprefix src/parsing/parsing_tools/, $(TOOLS)))

EXECUTION		=	canvas render/map_render render/rays_rendering

SRCS			= 	$(GENERAL_TOOLS) $(PARSING) \
					$(addsuffix .c, $(addprefix src/execution/, $(EXECUTION)))

OBJ				=	$(SRCS:.c=.o)
	
.c.o:
	@$(CC)  $(CFLAGS) -c $< -o $@

all : $(NAME)

$(NAME): $(HEADER) main.c $(LIBFT) $(OBJ)
	@$(CC) $(CFLAGS) -lmlx -framework OpenGL -framework AppKit $(OBJ) $(LIBFT) main.c -o $(NAME)

$(LIBFT) :
	@make -C src/general_tools/libft/
clean :
	@make clean -C src/general_tools/libft/
	@$(RM) $(OBJ)
	@$(RM)	cub3D.dSYM

fclean : clean
#@make fclean -C src/general_tools/libft/
	@$(RM) $(NAME)

re : fclean all

.PHONY:			all clean fclean re bonus
