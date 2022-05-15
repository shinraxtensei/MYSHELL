#include "../minishell.h"


// int herdoc(t_meta_data *data)
// {
//     char *input;
//     char *limitor;
//     int fd;
//     limitor = ft_strdup(data->commands->command->tokens->herdoc_limitor);
//     fd = data->commands->command->tokens->herdoc_fd;
//     input = readline ("> ");
//     if (!input)
//         return (0);
//     while (ft_strncmp(input, limitor , ft_strlen(limitor)))
//     {
//         input = readline ("> ");
//         ft_putstr_fd(input, fd);
//     }
//     return (0);
// }