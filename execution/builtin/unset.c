#include "../../minishell.h"

void ft_unset(t_meta_data *data)
{
    int i;
    int j;
    int size;
    i = -1;
    if (!data->commands->command->args)
        return ;
    while (data->commands->command->args[++i])
    {
        j = -1;
        while (data->env_data.env[++j])
        {
            size=-1;
            while (data->env_data.env[j][++size] != '=');
            if (!ft_strncmp(data->commands->command->args[i],ft_substr(data->env_data.env[j],0,size),size))
            {
                data->env_data.env = delete_value(data->env_data.env,j);
            }
        }
    }
}

char **delete_value(char **env,int pos)
{
    int i;
    int j;
    char **tmp;
    i = -1;
    j = 0;
    while(env[++i]);
    tmp = malloc(sizeof(char *) * i);
    i = 0;
    while (env[i])
    {
        if (i != pos)
        {
            tmp[j] = env[i];
            j++;
        }
        i++;
    }
    tmp[j] = 0;
    i = -1;
    while (env[++i])
        free(env[i]);
    free(env);
    return (tmp);
}