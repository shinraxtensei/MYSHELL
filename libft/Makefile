# -*-🦕-*- Make Libft -*-🦕-*-

NAME		= libft.a

# -*- Definitions of variables -*-

SRCS		= ${shell find . -type f \( -name "ft_*.c" ! -name "ft_lst*.c" ! -name "*bonus.c" ! -wholename "./TestLibft/*.c" \) | cut -d'/' -f2-}
SRCS_BONUS	= ${shell find . -type f \( -name "ft_*.c" ! -wholename "./TestLibft/*.c" \) | cut -d'/' -f2-}

OBJS_DIR	= objs
OBJS		= ${addprefix ${OBJS_DIR}/,${SRCS:.c=.o}}
OBJS_BONUS	= ${addprefix ${OBJS_DIR}/,${SRCS_BONUS:.c=.o}}

HEADER		= libft.h
HEADERS_OWN = libft.h libft_bonus.h

CC			= gcc
RM			= rm -f

CFLAGS		= -Wall -Wextra -Werror

# Colors

GRAY		= \e[1;30m
GREEN 		= \e[1;32m
DARK_GREEN	= \e[0;32m
YELLOW		= \e[1;33m
BLUE		= \e[1;34m
PURPLE		= \e[1;35m
CYAN		= \e[1;36m
WHITE		= \e[1;37m
NORMAL		= \e[0;37m
END			= \e[0m

# -*- The Rules -*-

#	Implicit rules

${OBJS_DIR}/%.o: %.c ${HEADER}
	@mkdir -p objs
	@${CC} ${FLAGS} -o $@ -c $<

#	Active rules

all: $(NAME)

$(NAME): ${OBJS} 
	@ar rcs ${NAME} ${OBJS}
	@printf "${GREEN}Compiled Libft${END}]\n\n"
	@printf "${END}"

bonus: ${OBJS} ${OBJS_BONUS} 
	@ar rcs ${NAME} ${OBJS} ${OBJS_BONUS}
	@printf "[${GREEN}Compiled Libft -bonus ${WHITE}]${END}\n"
	@printf "${END}"

#	Cleaning rules

clean:
	@${RM} ${OBJS_BONUS}
	@rm -rf objs
	@printf "${GREEN}libft cleaned${END}\n"


fclean: clean
	@${RM} ${NAME}


fclean_no_clean:
	@${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean fclean_no_clean re
