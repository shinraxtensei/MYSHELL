#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include "libft/libft.h"

typedef struct s_env_data
{
    char **env;
    int shellevel;
}t_env_data;

typedef struct s_metadata
{
    char *input; /* readline input */
    struct s_env_data env_data; /* env structure */
    struct s_list *commands; /* linked list of commands */
    
} t_meta_data;
 
int env_maker(char **env, t_meta_data *data);
int ft_strcmp(char *s1, char *s2);

#endif