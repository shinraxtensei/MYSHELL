    #include "../minishell.h"


int piwpiw(t_meta_data *data)
{
    int fd[2];
    pipe(fd);
    int i = 0;
    int *id = malloc (sizeof(int) * data->command_count);
    while (data->commands)
    {
        id[i] = fork();
        if (id[i] < 0)
            return -1;
        if (id[i] == 0)
        {
            
            if (i == 0)
            {
                dup2(fd[1], 1);
                close(fd[0]);
                // close(fd[1]);
            }

            else if (i == data->command_count - 1)
            {
                dup2(fd[0], 0);
                close(fd[1]);
                // close(fd[0]);
            }
       
            else
            {
                dup2(fd[0], 0);
                dup2(fd[1], 1);
                // close(fd[1]);
                // close(fd[0]);
            }
            close(fd[0]);
            close(fd[1]);
            if (check_exec(data->commands->command->cmd))
                exec_non_builtin(data);
            else
                exec_builtin(data);
        }
        data->commands = data->commands->next;
        i++;
    }
    close(fd[0]);
    close(fd[1]);
    i = 0;
    while (i < data->command_count)
    {
        waitpid(id[i], 0, 0);
        i++;
    }
    free(id);
    return 0;
}