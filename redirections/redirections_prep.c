#include "../minishell.h"

//  function that return the word after or before the redirection

char *find_next_word(char *str)
{
    int start = -1;
    int end = 0;
    char *word;
    while (str[++start] == ' ');
    end = start;
    while (str[end] != ' ' && str[end] != '\0' && str[end] != '>' && str[end] != '<' && check_inside_quotes(str, end))
        end++;
    word = ft_strtrim(ft_substr(str, start, end ), "\"\'");
    if (word[0] == '\0')
        return NULL;
    return (word);
}

char *find_prev_word(char *str , int index)
{
    int start;
    int end;
    end = index;
    char *word;
    while (str[end - 1] == ' ' && end >= 0)
        end--;
    start = end - 1;
    while (str[start] != ' ' && start >= 0)
        start--;
    word  = ft_substr(str, start + 1, index - start - 1);

    if (word[0] == '\0')
        return NULL;
    return word;
}


// function that prepare gather data on the redirection and create fds ...

int append_redirection( t_meta_data *data, char *str , int index)
{
    data->commands->command->tokens.redirection_type = APPEND;
    data->commands->command->tokens.output_file = find_next_word(str + index + 1);
    data->commands->command->tokens.output_fd = open(data->commands->command->tokens.output_file, O_WRONLY | O_APPEND | O_CREAT, 0644);
    return 0;
}

int output_redirection(t_meta_data *data, char *str , int index)
{

    data->commands->command->tokens.redirection_type = OUTPUT_REDIRECTION;
    data->commands->command->tokens.output_file = find_next_word(str + index + 1);
    data->commands->command->tokens.output_fd = open(data->commands->command->tokens.output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    return (0);
}

int herdoc_redirection(t_meta_data *data, char *str , int index)
{
    data->commands->command->tokens.redirection_type = HERDOC;
    data->commands->command->tokens.herdoc_limitor = find_next_word(str + index + 1);
    data->commands->command->tokens.herdoc_fd = open("herdoc", O_RDWR | O_CREAT | O_TRUNC , 0644);
    // unlink("herdoc");
    return 0;
}

int input_redirection(t_meta_data *data, char *str , int index)
{
    data->commands->command->tokens.redirection_type = INPUT_REDIRECTION;
    data->commands->command->tokens.input_file = find_next_word(str + index + 1);
    data->commands->command->tokens.input_fd = open(data->commands->command->tokens.input_file, O_RDONLY);
    return 0;
}

// // a function that check if there is any redirection in the command and prepare the data

int redirection_preparations(t_meta_data *data)
{
    int i;
    char *str;
    t_list *tmp;
    tmp = data->commands;
    while (tmp)
    {
        i = 0;
        str = data->commands->command->unsplited_command;
        if (str[0] == '>')
            data->commands->command->tokens.first_pos = 1;

        while (str[i])
        {
            if(str[i] == '>' && check_inside_quotes(str, i))
            {
                if (str[i + 1] == '>')
                {
                    i++;
                    append_redirection(data ,str, i );
                }
                else
                    output_redirection(data, str, i);
            }
            else if (str[i] == '<')
            {
                if (str[i + 1] == '<')
                {
                    i++;
                    herdoc_redirection(data, str, i);
                }
                else
                    input_redirection(data, str, i);
            }
            i++;
        }
        tmp = tmp->next;
    }
    return 0;
}
