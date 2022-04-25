#include "../../minishell.h"

void    fun_cd(t_meta_data *data)
{
    // int i;
    // char tmp[900000];
    // i = -1;
    // while(data->env_data.env[++i])
    // {
    //     if (!ft_strncmp(data->env_data.env[i],"OLDPWD",4))
    //             break ;
    // }
    // getcwd(tmp,900000);
    // free(data->env_data.env[i]);
    // data->env_data.env[i] = ft_strdup(tmp);
    // printf("oldpwd :%s\n",data->env_data.env[i]);
    chdir(data->commands->command->args[0]);
    // i = -1;
    // while(data->env_data.env[++i])
    // {
    //     if (!ft_strncmp(data->env_data.env[i],"PWD",4))
    //             break ;
    // }
    // getcwd(tmp,900000);
    // // free(data->env_data.env[i]);
    // // data->env_data.env[i] = ft_strdup(tmp);
    // printf("pwd :%s\n",data->env_data.env[i]);
}