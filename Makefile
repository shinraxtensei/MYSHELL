NAME = minishell

SRCS = minishell.c parsing/envirement.c execution/builtin/env.c execution/builtin/export.c execution/builtin/execution_env.c\
		parsing/parsing.c execution/execution.c execution/builtin/pwd.c execution/builtin/cd.c redirections/redirections.c\
		pipes/piping.c

OBJS	= $(SRCS:.c=.o)

LIBFT = libft/libft.a

CFLAGS =  -Wall -Wextra -Werror -g

HEADER = minishell.h


all : $(LIBFT) $(NAME) $(HEADER)

$(NAME): $(SRCS) $(OBJS) $(HEADER)
		@gcc $(CFLAGS) -lreadline  $(SRCS) $(LIBFT) -o $@
		@echo ------------------------------------
		@echo ----------- R E A D Y --------------
		@echo ------------------------------------


$(LIBFT):
	@Make -C ./libft

clean :
		@Make clean -C ./libft
		@rm -rf $(OBJS) $(OBJS_BONS)

fclean :
		@Make fclean -C ./libft
		@rm -rf $(OBJS) $(OBJS_BONS) $(NAME) $(BONUS)

re :
	@Make fclean all


.PHONY : all clean fclean re