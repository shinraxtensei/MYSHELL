#include "../../minishell.h"

void ft_export(t_meta_data *data)
{
    int i;

    i = -1;
    printf("hello\n");
    while (data->env_data.env_export[++i])
    {
        ft_putstr_fd(data->env_data.env_export[i], 1);
        write(1,"\n",1);
    }
}

void sort_env(t_meta_data *data)
{
    int i;
    int j;
    int size;
    char *tmp;

    size = 0;
    while (data->env_data.env[size])
        size++;
    data->env_data.env_export = malloc(sizeof(char *) * (size + 1));
    i = -1;
    while(data->env_data.env[++i])
    {
        data->env_data.env_export[i] = ft_strjoin("declare -x ", data->env_data.env[i]);
    }
    data->env_data.env_export[i] = 0;
    i = 0;
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