
#include "../minishell.h"

static void shelllevel_upddater(t_meta_data *data)
{
    int  i = 0;
    char *tmp ; 
    while (data->env_data.env[i])
    {
        if(ft_strncmp("SHLVL" , data->env_data.env[i] , 5) == 0)
            break;
        i++;
    }
    tmp = ft_substr(data->env_data.env[i], 6 ,ft_strlen(data->env_data.env[i]));
    data->env_data.shellevel = atoi(tmp) + 1;
    data->env_data.env[i] = ft_strjoin(ft_substr(data->env_data.env[i],0 , 6) , ft_itoa(data->env_data.shellevel));
}

static void env_setup(char **env, t_meta_data *data)
{
    int i;

    i = 0;
    while (env[i])
        i++;
    data->env_data.env = malloc (sizeof(char *) * i + 1);
    i = -1;
    while (env[++i])
        data->env_data.env[i] = ft_strdup(env[i]);
    data->env_data.env[i] = 0;
    
}


int env_maker(char **env, t_meta_data *data)
{
    env_setup (env, data);
    shelllevel_upddater (data);
    return 0;
}
