#include "minishell.h"

int main (int ac, char **argv, char **env)
{
    (void) ac;
    (void) argv;   
    int i;
    t_meta_data *data;
    data = malloc (sizeof (t_meta_data ) * 10);
    env_maker(env , data); // create envirement
    while(1)
    {
        i = -1;
        data->input = readline("minishell :");
        parsing(data);
        if (execution_env(data) == 0)
            break ;
    }
    return 0;
}