#include "minishell.h"




int main (int ac, char **argv, char **env)
{
    (void) ac;
    (void) argv;   
    int i = 0; 
    t_meta_data data;
    env_maker(env , &data);

    // while(1)
    // {
    //     data.input = readline("minishell :");
    //     ft_new_split(&data);








    //     if(strcmp(data.input, "exit") == 0)
    //         break;
    // }
    return 0;
}