# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ccestini <ccestini@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/16 11:38:14 by ccestini          #+#    #+#              #
#    Updated: 2023/02/14 09:39:16 by ccestini         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -I /usr/local/Cellar/readline/8.1.1/include 

RM			= rm -rf

SRCS		= main.c \
			list_functions.c \
			split_pipes.c \
			parse.c \
			syntax.c \
			tokenization.c \
			dollar_utils.c \
			dollar.c \
			get_fds.c \
			get_path.c \
			get_env.c \
			heredoc.c \
			heredoc_utils.c \
			execute_line.c \
			execute_cmds.c \
			execute_utils.c \
			builtins_child.c \
			builtins_utils.c \
			builtins_parent.c \
			ft_cd.c \
			ft_export.c \
			ft_unset.c \
			ft_echo.c \
			free.c \
			utils.c \
			utils2.c \
			utils3.c \
			signal.c \
			signal2.c
			
OBJS		= $(SRCS:.c=.o)

READ_LIB = -L /usr/local/Cellar/readline/8.1.1/lib

all:		$(NAME)
			@printf "\033[32m-> Executable Done! <-\033[0m\n"

libft.a:
			@$(MAKE) all -C libft

$(NAME):	libft.a $(OBJS)
			@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L ./libft -lft ${READ_LIB} -lreadline

clean:
			@$(RM) $(OBJS)
			@$(MAKE) clean -C libft
			@printf "\033[35m-> *.o cleaned! <-\033[0m\n"

fclean:		clean
			@$(RM) $(NAME)
			@$(MAKE) fclean -C libft
			@printf "\033[36m-> executable deleted! <-\033[0m\n"

re:			fclean all

.PHONY:		all clean fclean re 
