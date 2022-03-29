#include "../minishell.h"

int execution_env(t_meta_data *data)
{
    int i;

    i = -1;
    if (data->input[0] == '$')
    {
        data->input = ft_substr(data->input, 1, ft_strlen(data->input)); //remove the $
        data->input = ft_strjoin(data->input, "="); // add the = after the string
        while (data->env_data.env[++i])
        {
            if (!ft_strncmp(data->env_data.env[i],data->input, ft_strlen(data->input))) // search the word in envirement
                break ;
        }
        ft_putstr_fd(data->env_data.env[i], 1); //print the command in envirement
        write(1,"\n",1);
        return (1);
    }
    else if (strcmp(data->input, "env") == 0) // print envirement
    {
        ft_env(data);
        return (1);
    }
    else if (strcmp(data->input, "export") == 0) // print export
    {
        ft_export(data);
        return (1);
    }
    else if(strcmp(data->input, "exit") == 0) // exit
        return (0);
    // else
    // {
    //     ft_putstr_fd("invalid command\n", 1);
    //     write(1,"\n",1);
    //     return (1);
    // }
    return (1);
}