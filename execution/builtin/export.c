#include "../../minishell.h"

void ft_export(t_meta_data *data)
{
    char **tmp;
    int i;
    i = -1;
    if (check_args_for_export(data->commands->command->args) == 1)
    {
        data->env_data.env = check_value(data->commands->command->args,data->env_data.env);
    }
    else if (check_args_for_export(data->commands->command->args) == 3)
    {
        i = -1;
        while (data->env_data.env[++i]);
        tmp = malloc(sizeof(char *) * (i + 1));
        i = -1;
        while(data->env_data.env[++i])
            tmp[i] = data->env_data.env[i];

        sort_export(tmp);
        i = -1;
        while (tmp[++i])
        {
            ft_putstr_fd(ft_strjoin("declare -x ",tmp[i]), 1);
            write(1,"\n",1);
        }
    }
    else
    {
        printf("ERROR\n");
        return ;
    }

}
char **check_value(char **args, char **env)
{
    int i;
    int j;
    int size;
    int flag;

    i = -1;
    while (args[++i])
    {
        j = -1;
        size = -1;
        flag = 0;
        while (args[i][++size] != '=');
        while (env[++j])
        {
            if (!ft_strncmp(ft_substr(args[i],0,size),env[j],size))
                flag = j;
        }
        if (flag)
        {
            free(env[flag]);
            env[flag] = ft_strdup(args[i]);
        }
        else
            env = add_args(args[i],env);
    }
    return env;
}
char **add_args(char *arg, char **env)
{
    int i;
    int j;
    char **tmp;
    i = -1;

    j = -1;
    while (env[++j]);
    tmp = malloc(sizeof(char *) * (j + 2));
    i = -1;
    while (env[++i])
        tmp[i] = ft_strdup(env[i]);
    tmp[i] = ft_strdup(arg);
    i++;
    tmp[i] = 0;
    return (tmp);
}

void export_setup(t_meta_data *data)
{
    int i;
    int size;

    size = 0;
    while (data->env_data.env[size])
        size++;
    data->env_data.env_export = malloc(sizeof(char *) * (size + 1));
    i = -1;
    while(data->env_data.env[++i])
    {
        data->env_data.env_export[i] = ft_strdup(data->env_data.env[i]);
    }
    data->env_data.env_export[i] = 0;
}

void    sort_export(char **env)
{
    int i;
    int j;
    int size;
    char *tmp;

    i = 0;
    size = 0;
    while(env[size])
        size++;
    while (i < size)
    {
        j = i + 1;
        while (j < size)
        {
            if (strcmp(env[i],env[j]) > 0)
            {
                tmp = env[i];
                env[i] = env[j];
                env[j] = tmp;
            }
            j++;
        }
        i++;
    }
}

int check_args_for_export(char **args)
{
    int i = 0;
    int j;
    if (!args)
        return (3);
    while (args[i])
    {
        if (ft_isdigit(args[i][0]))
            return 0;
        j = 1;
        while (args[i][j] && args[i][j] != '=')
        {
            if (!ft_isalnum(args[i][j]) && args[i][j] != '_')
                return 0;
            j++;
        }
        i++;
    }
    return 1;
}