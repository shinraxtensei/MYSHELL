#include "../minishell.h"

void execution(t_meta_data *data)
{
    int i;
    char **arr;
    char *tmp;
    
    i = -1;
    while (data->env_data.env[++i])
    {
        if (!ft_strncmp(data->env_data.env[i],"PATH",4))
            break ;
        i++;
    }
    tmp = ft_substr(data->env_data.env[i],5,ft_strlen(data->env_data.env[i]));
    arr = ft_split(tmp, ':');
    i = -1;
    while (arr[++i])
    {
        tmp = ft_strjoin(arr[i],"/");
        tmp = ft_strjoin(tmp,data->commands->command->cmd);
        if (access(tmp,X_OK) == 0)
            break;
    }
    i = -1;
    while (arr[++i])
        free(arr[i]);
    free(arr);
    execve(tmp,data->commands->command->whole_command,data->env_data.env);
}