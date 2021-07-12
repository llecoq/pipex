# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: user42 <user42@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/08 12:13:07 by user42            #+#    #+#              #
#    Updated: 2021/07/10 11:00:47 by user42           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_FILES	=	main.c\
				parsing/parser.c\
				parsing/tokenizer.c\
				parsing/store_path.c\
				utils/clear_memory.c\
				utils/store_cmd_list.c\
				utils/error.c\
				utils/calloc_pipex.c\
				utils/del.c\
				utils/print_list.c

SRCSPATH= srcs/

OBJS_FILES = $(SRCS_FILES:.c=.o)

OBJSPATH= .objs/

SRCS = $(addprefix $(SRCSPATH),$(SRCS_FILES))

OBJS = $(addprefix $(OBJSPATH),$(OBJS_FILES))

NAME	= pipex

CC		= gcc

RM		= rm -rf

CFLAGS	= -Wall -Wextra -Werror -g3 -fsanitize=address

DIR		=	.objs/parsing\
			.objs/utils\

$(OBJSPATH)%.o:		$(SRCSPATH)%.c includes/pipex.h libft/libft.h libft/libft.a
			@mkdir -p $(OBJ_PATH) $(DIR)
			$(CC) $(CFLAGS) -c $< -o $@ -I includes/ -I libft/ 
#verify that libft include works no relink

all:		previous $(NAME)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $(OBJS) -Llibft -lft -g -o $(NAME)

previous:
			@$(MAKE) -C ./libft

clean:
			$(RM) $(OBJSPATH)
			$(MAKE) clean -C ./libft

fclean:		clean
			$(RM) $(NAME)
			$(MAKE) fclean -C ./libft

re:			fclean all

.PHONY:		all clean fclean re
