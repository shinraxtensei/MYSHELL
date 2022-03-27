NAME = minishell

SRCS = minishell.c parsing/envirement.c execution/env.c execution/export.c execution/execution_env.c\
		parsing/parsing.c

OBJS	= $(SRCS:.c=.o)

LIBFT = libft/libft.a

CFLAGS =  -Wall -Wextra -Werror

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