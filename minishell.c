#include "minishell.h"

int main (int ac, char **argv, char **env)
{
    (void) ac;
    (void) argv;   
    t_meta_data data;
    int i = -1;

    env_maker(env , &data); // create env
    while(1)
    {
        i = -1;
        data.input = readline("minishell :");
        if (data.input[0] == '$')
        {
            data.input = ft_substr(data.input, 1, ft_strlen(data.input)); //remove the $
            data.input = ft_strjoin(data.input, "="); // add the = after the string
            while (data.env_data.env[++i])
            {
                if (!ft_strncmp(data.env_data.env[i],data.input, ft_strlen(data.input))) // search the word in env
                    break ;
            }
            printf("%s\n",data.env_data.env[i]); //prit the env
        }
        else if (strcmp(data.input, "env") == 0)
            while (data.env_data.env[++i])
                printf("%s\n",data.env_data.env[i]);
        
        else if(strcmp(data.input, "exit") == 0) // exit
            break;
    }
    return 0;
}