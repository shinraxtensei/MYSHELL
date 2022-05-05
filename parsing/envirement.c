
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
    //printf("test\n");
    tmp = ft_substr(data->env_data.env[i], 6 ,ft_strlen(data->env_data.env[i]));
    data->env_data.shellevel = atoi(tmp) + 1;
    //free(data->env_data.env[i]);
    data->env_data.env[i] = ft_strjoin(ft_substr(data->env_data.env[i],0 , 6) , ft_itoa(data->env_data.shellevel));
}

static void env_setup(char **env, t_meta_data *data)
{
    int i;

    i = 0;
    if (!env[i])
        create_env(data);
    else
    {
        while (env[i])
            i++;
        data->env_data.env = malloc (sizeof(char *) * i + 1);
        i = -1;
        while (env[++i])
            data->env_data.env[i] = ft_strdup(env[i]);
        data->env_data.env[i] = 0;
    }
}

void create_env(t_meta_data  *data)
{
    int i;
    char arr[90000];
    i = -1;
    data->env_data.env = malloc(sizeof(char *) * 4);
    getcwd(arr,90000);
    data->env_data.env[0] = ft_strjoin("PWD=",arr);
    data->env_data.env[1] = ft_strdup("SHLVL=0");
    data->env_data.env[2] = ft_strjoin("PATH=", _PATH_STDPATH);
    data->env_data.env[3] = 0;
}

int env_maker(char **env, t_meta_data *data)
{
    env_setup (env, data);
    shelllevel_upddater(data);
    sort_env(data);
    return 0;
}
