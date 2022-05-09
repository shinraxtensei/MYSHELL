#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include <paths.h>
#include "libft/libft.h"

#include  <fcntl.h>                              
                              
#include  <stdlib.h>
        
#include  <sys/types.h> 
#include  <sys/wait.h>           
#include  <sys/stat.h>           
#include  <termios.h>              
#include  <unistd.h> 



typedef struct s_env_data
{
    char **env;
    char **env_export;
    int shellevel;
}t_env_data;

typedef struct s_metadata
{
    int command_count;
    char *input; /* readline input */
    struct s_env_data env_data; /* env structure */
    struct s_list *commands; /* linked list of commands */
    
} t_meta_data;
 
int env_maker(char **env, t_meta_data *data);
int ft_strcmp(char *s1, char *s2);


//--------- | envirement | -----------

void ft_env(t_meta_data *data);
void ft_export(t_meta_data *data);
int execution_env(t_meta_data *data);
void create_env(t_meta_data  *data);

//--------- | parsing | -----------
char **split_things(char *str , char c);
int parsing(t_meta_data *data);

//--------- | execution | -----------
// void sort_env(t_meta_data *data);
void execution(t_meta_data *data);
void exec_non_builtin(t_meta_data *data);
void exec_builtin(t_meta_data *data);
int check_exec(char *arr);
void fun_pwd();
void    fun_cd(t_meta_data *data);


// export
void ft_export(t_meta_data *data);
void add_args_to_export(t_meta_data *data);
void    sort_export(t_meta_data *data);
int check_args_for_export(char **args);
void export_setup(t_meta_data *data);





// //--------- | redirection | -----------
void herdoc(t_meta_data *data);
int piwpiw(t_meta_data *data);

#endif