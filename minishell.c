#include "minishell.h"

int main (int ac, char **argv, char **env)
{
    (void) ac;
    (void) argv;   
    int i;
    t_meta_data *data;
    data = malloc(sizeof(t_meta_data));
    data->commands = malloc(sizeof(t_list));
    data->commands = NULL;

    env_maker(env , data); // create envirement
    while(1)
    {
        i = -1;
        data->input = readline("minishell :");
        if (!data->input)
            exit(1);
        parsing(data);
        if (execution_env(data) == 0)
            break ;
    }
    return 0;
}