/////////////////////////////////////////////#include "minishell.h"
#include "minishell.h"

void	ft_clear_data(t_list **lst)
{

	if (!lst)
		return ;
	while (*lst)
	{
		// free((*lst)->command->args);
		free((*lst)->command->whole_command);
		//free((*lst)->command->cmd);
        //free((*lst)->command->option);
		*lst = (*lst)->next;
	}
	*lst = NULL;
}

int main (int ac, char **argv, char **env)
{
    (void) ac;
    (void) argv;   
    int i;
    t_meta_data *data;
    
    data = malloc(sizeof(t_meta_data));
    data->commands = malloc(sizeof(t_list));
    data->commands = NULL;

    env_maker(env , data); // create envirement
    while(1)
    {
        i = -1;
        data->input = readline("minishell :");
        if (data->input)
            add_history(data->input);
        parsing(data);
        // if (execution_env(data) == 0)
        //     break ;]
        //printf("%s\n",data->commands->command->cmd);
        //printf("%s\n",data->commands->command->args[1]);
        if (!ft_strncmp(data->input,"exit",4))
            exit(1);
        execution(data);
        ft_clear_data(&data->commands);
    }
    return 0;
}