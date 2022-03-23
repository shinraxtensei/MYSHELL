#include "../minishell.h"

void ft_export(t_meta_data *data)
{
    int i;


    i = -1;
    while (data->env_data.env[++i])
    {
        ft_putstr_fd(ft_strjoin("declare -x ", data->env_data.env[i]), 1);
        write(1,"\n",1);
    }
}