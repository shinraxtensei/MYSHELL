
NAME	= minishell


SRCS_DIR		= srcs
SRCS			:= $(shell find $(SRCS_DIR) -name *.c)

OBJS_DIR		= objs
OBJS			:= $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

OBJS_SUB_DIR	:= $(shell find $(SRCS_DIR) -mindepth 1 -type d)
OBJS_SUB_DIR	:= $(OBJS_SUB_DIR:$(SRCS_DIR)/%=$(OBJS_DIR)/%)



LIBFT_DIR		= libft

READLINE_DIR	= /goinfre/ahouari/.brew/opt/readline



INCLUDES		= -I includes -I ${READLINE_DIR}/include
LIBRARIES		= -L ${LIBFT_DIR} -lft -L ${READLINE_DIR}/lib -lreadline

CC				= gcc
RM				= rm -f
MAKE			= make
CFLAGS 			= -Wall -Wextra -Werror

# Colors

GRAY			= \e[1;30m
GREEN 			= \e[1;32m
DARK_GREEN		= \e[0;32m
YELLOW			= \e[1;33m
BLUE			= \e[1;34m
PURPLE			= \e[1;35m
CYAN			= \e[1;36m
WHITE			= \e[1;37m
NORMAL			= \e[0;37m
END				= \e[0m


$(OBJS_DIR)/%.o: ${SRCS_DIR}/%.c
			@mkdir -p ${OBJS_DIR}
			@mkdir -p $(OBJS_SUB_DIR)
			@${CC} ${CFLAGS} ${INCLUDES} -c $< -o $@

all:			${NAME} 


${NAME}:		${OBJS}
			@${MAKE} bonus -C ${LIBFT_DIR}
			@$(CC) ${CFLAGS} ${INCLUDES} ${OBJS} -o $(NAME) $(LIBRARIES)
			@printf "${WHITE}[${GREEN} Success. Compiled minishell.${WHITE}]\
			${END} \n"


bonus:			${NAME}

#	Cleaning rules

clean_no_libft:
			@${RM} ${OBJS} ${OBJS_BONUS}
			@rm -rf objs

clean:
			@${MAKE} clean -C ${LIBFT_DIR}
			@${RM} ${OBJS} ${OBJS_BONUS}
			@rm -rf objs
			@printf "${GREEN}minishell cleaned${END}\n"


fclean:			clean
			@${MAKE} fclean_no_clean -C ${LIBFT_DIR}
			@${RM} ${NAME}

re:				fclean all




































# NAME = Minishell

# SRCS_DIR		= srcs
# SRCS			:= $(shell find $(SRCS_DIR) -name *.c)

# OBJS_DIR		= objs
# OBJS			:= $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

# LIBFT_DIR		= libft



# CC				= gcc
# RM				= rm -f
# MAKE			= make
# CFLAGS 			= -Wall -Wextra -Werror


# # Colors

# GRAY			= \e[1;30m
# GREEN 			= \e[1;32m
# DARK_GREEN		= \e[0;32m
# YELLOW			= \e[1;33m
# BLUE			= \e[1;34m
# PURPLE			= \e[1;35m
# CYAN			= \e[1;36m
# WHITE			= \e[1;37m
# NORMAL			= \e[0;37m
# END				= \e[0m