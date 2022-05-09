#include "../../minishell.h"

void ft_export(t_meta_data *data)
{
    int i;
    i = -1;
    if (check_args_for_export(data->commands->command->args) == 1)
    {
        add_args_to_export(data);
        //add_args_to_env(data);
    }
    else if (check_args_for_export(data->commands->command->args) == 3)
    {
        printf("test\n");
        sort_export(data);
        i = -1;
        while (data->env_data.env_export[++i])
        {
            ft_putstr_fd(ft_strjoin("declare -x ",data->env_data.env_export[i]), 1);
            write(1,"\n",1);
        }
    }
    else
    {
        printf("ERROR\n");
        return ;
    }

}

void add_args_to_export(t_meta_data *data)
{
    int i,j;
    char **tmp;
    i = -1;
    j = -1;
    while (data->commands->command->args[++j]);
    if (j == 0)
        return ;
    while (data->env_data.env_export[++i]);
    tmp = malloc(sizeof(char *) * (i + 1 + j));
    i = -1;
    while (data->env_data.env_export[++i])
        tmp[i] = ft_strdup(data->env_data.env_export[i]);
    j = -1;
    while (data->commands->command->args[++j])
    {
        tmp[i] = ft_strdup(data->commands->command->args[j]);
        i++;
    }
    tmp[i] = NULL;
    i = -1;
    while (data->env_data.env_export[++i])
        free(data->env_data.env_export[i]);
    free(data->env_data.env_export);
    data->env_data.env_export = tmp;
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

void    sort_export(t_meta_data *data)
{
    int i;
    int j;
    int size;
    char *tmp;

    i = 0;
    size = 0;
    while(data->env_data.env_export[size])
        size++;
    while (i < size)
    {
        j = i + 1;
        while (j < size)
        {
            if (strcmp(data->env_data.env_export[i],data->env_data.env_export[j]) > 0)
            {
                tmp = data->env_data.env_export[i];
                data->env_data.env_export[i] = data->env_data.env_export[j];
                data->env_data.env_export[j] = tmp;
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