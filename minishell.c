#include "minishell.h"

void shelllevel_upddater(t_meta_data *data)
{
    int  i = 0;
    char *tmp ; 
    while (data->env_data.env[i])
    {
        if(ft_strncmp("SHLVL" , data->env_data.env[i] , 5) == 0)
            break;
        i++;
    }
    tmp = ft_substr(data->env_data.env[i], 6 ,ft_strlen(data->env_data.env[i]));
    data->env_data.shellevel = atoi(tmp) + 1;
    
}

void env_setup(char **env, t_meta_data *data)
{
    int i;

    i = 0;
    while (env[i])
        i++;
    data->env_data.env = malloc (sizeof(char *) * i + 1);
    i = -1;
    while (env[++i])
        data->env_data.env[i] = ft_strdup(env[i]);
}


int main (int ac, char **argv, char **env)
{
    (void) ac;
    (void) argv;    
    t_meta_data data;
    env_setup (env, &data);
    shelllevel_upddater(&data);
    // while(1)
    // {
    //     data.input = readline("minishell :");
    //     ft_new_split(&data);








    //     if(strcmp(data.input, "exit") == 0)
    //         break;
    // }
    return 0;
}