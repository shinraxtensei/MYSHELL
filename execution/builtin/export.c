#include "../../minishell.h"

void ft_export(t_meta_data *data)
{
    int i;

    i = -1;

    sort_env(data);
    printf("hello\n");
    while (data->env_data.env_export[++i])
    {
        ft_putstr_fd(ft_strjoin("1.", data->env_data.env_export[i]), 1);
        write(1,"\n",1);
    }
}

void sort_env(t_meta_data *data)
{
    int i;
    int j;
    int size;
    char tmp[9999];
    i = 0;
    while (data->env_data.env[i])
        i++;
    size = i;
    data->env_data.env_export = malloc(sizeof(char *) * (i + 1));
    i = -1;
    while(data->env_data.env[++i])
        data->env_data.env_export[i] = data->env_data.env[i];
    data->env_data.env_export[i] = 0;
    i = 0;
    while (i < size)
    {
        j = i + 1;
        while (j < size)
        {
            if (strcmp(data->env_data.env_export[i],data->env_data.env_export[j]) > 0)
            {
                strcpy(tmp,data->env_data.env_export[j]);
                strcpy(data->env_data.env_export[j],data->env_data.env_export[i]);
                strcpy(data->env_data.env_export[i],tmp);
            }
            j++;
        }
        i++;
    }
}
