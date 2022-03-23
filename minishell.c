#include "minishell.h"

int main (int ac, char **argv, char **env)
{
    (void) ac;
    (void) argv;   
    t_meta_data data;
    env_maker(env , &data);

int i  = 0;
    while(1)
    {
        data.input = readline("minishell :");

        if(strcmp(data.input, "exit") == 0)
            break;
    }
    return 0;
}