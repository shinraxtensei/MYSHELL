#include "minishell.h"

int main (int ac, char **argv, char **env)
{
    (void) ac;
    (void) argv;   
    t_meta_data data;
    int i;

    env_maker(env , &data); // create envirement
    while(1)
    {
        i = -1;
        data.input = readline("minishell :");
        if (execution_env(&data) == 0)
            break ;
    }
    return 0;
}