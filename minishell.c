/////////////////////////////////////////////#include "minishell.h"
#include "minishell.h"

void	ft_clear_data(t_list **lst)
{

	if (!lst)
		return ;
	while (*lst)
	{
		(*lst)->command->args = NULL;
		(*lst)->command->whole_command = NULL;
		(*lst)->command->cmd = NULL;
		*lst = (*lst)->next ;
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

    env_maker(env , data);
    while(1)
    {
        i = -1;
        // sig_init();
        data->input = readline("minishell :");
        if (data->input)
            add_history(data->input);

        parsing(data);

        if (!ft_strncmp(data->input,"exit",4))
            exit (0);
        execution(data);
        ft_clear_data(&data->commands);
    }
    return 0;
}