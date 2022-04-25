#include "../minishell.h"

void execution(t_meta_data *data)
{
    int id;

    id = fork();
    if (check_exec(data->commands->command->cmd))
        exec_non_builtin(data,id);
    else
        exec_builtin(data,id);
}

void exec_non_builtin(t_meta_data *data,int id)
{
    char **arr;
    char *tmp;
    int i;
    if (id == 0)
    {
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
        if (!execve(tmp,data->commands->command->whole_command,data->env_data.env))
            return ;
        free(tmp);
    }
    if (id != 0)
        wait(0);
}
int check_exec(char *arr)
{
    if (!ft_strncmp(arr,"echo",4))
        return (0);
    else if (!ft_strncmp(arr,"cd",2))
        return (0);
    else if (!ft_strncmp(arr,"pwd",3))
        return (0);
    else if (!ft_strncmp(arr,"unset",5))
        return (0);
    else if (!ft_strncmp(arr,"export",6))
        return (0);
    else if (!ft_strncmp(arr,"env",3))
        return (0);
    else if (!ft_strncmp(arr,"exit",4))
        return (0);
    else
        return (1);
}

void exec_builtin(t_meta_data *data, int id)
{
    if (id == 0)
    {
        if (!ft_strncmp(data->commands->command->cmd,"echo",4))
            return ;
        else if (!ft_strncmp(data->commands->command->cmd,"cd",2))
            fun_cd(data);
        else if (!ft_strncmp(data->commands->command->cmd,"pwd",3))
            fun_pwd();
        else if (!ft_strncmp(data->commands->command->cmd,"unset",5))
            return ;
        else if (!ft_strncmp(data->commands->command->cmd,"export",6))
            return ;
        else if (!ft_strncmp(data->commands->command->cmd,"env",3))
            return ;
        else if (!ft_strncmp(data->commands->command->cmd,"exit",4))
            return ;
        else
            printf("Error\n");
    }
    if (id != 0)
        wait(0);
}