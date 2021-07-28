# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/08 12:13:07 by user42            #+#    #+#              #
#    Updated: 2021/07/28 11:06:22 by llecoq           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_FILES	=	main.c\
				executor/executor.c\
				executor/create_redirection.c\
				tokenizer/store_token_list.c\
				tokenizer/tokenizer.c\
				tokenizer/store_tokens.c\
				parsing/parser.c\
				parsing/store_path.c\
				parsing/split_words_bonus.c\
				parsing/store_cmds.c\
				utils/clear_memory.c\
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

CFLAGS	= -Wall -Wextra -Werror

DIR		=	.objs/parsing\
			.objs/tokenizer\
			.objs/utils\
			.objs/executor\

$(OBJSPATH)%.o:		$(SRCSPATH)%.c includes/pipex.h libft/libft.h libft/libft.a
			@mkdir -p $(OBJ_PATH) $(DIR)
			$(CC) $(CFLAGS) -c $< -o $@ -I includes/ -I libft/ 

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
