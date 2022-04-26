#include "../../minishell.h"

void ft_env(t_meta_data *data)
{
    int i;

    i = -1;
    while (data->env_data.env[++i])
    {
        ft_putstr_fd(data->env_data.env[i],1);
        write(1,"\n",1);
    }
}