#include "../../minishell.h"

// int ft_echo(t_meta_data *data)
// {
//     int i;
//     char *tmp;
//     if (check_option(data))
//     {
//         i = 1;
//         while (data->commands->command->args[i])
//         {
//             ft_putstr_fd(data->commands->command->args[i] ,1);
//             if (data->commands->command->args[i + 1])
//                 ft_putstr_fd(" ",1);
//             i++;
//         }
//     }
//     else
//     {
//         i = 0;
//         while (data->commands->command->args[i])
//         {
//             if (check_quotes_for_print(data->commands->command->args))
//             {
//                 if (data->commands->command->args[i][0] == '$')
//                 {
//                     tmp = ft_substr(data->commands->command->args[i], 1, ft_strlen(data->input)); //remove the $
//                     data->input = ft_strjoin(data->input, "="); // add the = after the string
//                     while (data->env_data.env[++i])
//                     {
//                         if (!ft_strncmp(data->env_data.env[i],data->input, ft_strlen(data->input))) // search the word in envirement
//                         break ;
//                     }
//                 }
//             }
//                 ft_putstr_fd(data->commands->command->args[i] ,1);
//                 ft_putstr_fd(" ",1);
//             i++;
//         }
//         ft_putstr_fd("\n" , 1);
//     }
//     return (1);
// }

// int check_option(t_meta_data *data)
// {
//     if (!ft_strncmp(data->commands->command->args[0],"-n",2))
//         return (1);
//     return (0);
// }

// int check_quotes_for_print(char **args)
// {
//     if (args[0][0] == '\"')
//         return (1);
//     return (0);
// }