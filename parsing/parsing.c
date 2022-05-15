#include "../minishell.h"

int words_count(char *str , char c)
{
    int  i;
    int  words;

    i = -1;
    words = 1;
    while (str[++i])
    {
        if ((str[i] == c) && check_inside_quotes(str, i) == 1)
        {
            while (str[i + 1] == c)
                i++;
            words++;
        }
    }
    if(check_inside_quotes(str, ft_strlen(str) ) == 0)
        print_error("9ad l quotes");
    return (words);
}

char **split_things(char *str , char c)
{
    char **strs;
    int words;
    int *indexes;
    int i;
    int j;
    words = words_count(str, c);
    indexes = quotes_indexer(str, c, words);
    strs = malloc(sizeof(char *) * (words + 1));
    i = 0;
    j = 0;
    str = ft_strtrim(str , " ");
    if ( str[0] == '|' || str[ft_strlen(str)-1] == '|')
        print_error("error: pipes must be between commands");
    if (words == 1)
    {

        while (str[i] == ' ')
            i++;
        strs[0] = ft_substr(str , i, ft_strlen(str) - i);
        strs[1] = NULL;
        return strs;
    }
    else
    {
        while (i < words - 1 && str)
        {

            if (i == 0)
                strs[i] = ft_substr(str , j, indexes[i]);
            else
                strs[i] = ft_substr(str , j, indexes[i]  - indexes[i - 1] - 1);
            j = indexes[i] + 1;
            i++;
        }
    }
    j++;
    strs[i] = ft_substr(str , j - 1 ,ft_strlen(str - indexes[i]));
    i++;
    strs[i] = NULL;
    i = -1;
    while(strs[++i])
        strs[i] = ft_strtrim(strs[i] , " ");

    return strs;
}



int arr_couter(char **strs)
{
    int len = 0;
    while (strs[len])
        len++;
    return len;
}

int parsing(t_meta_data *data)
{
    char **strs;
    int len = -1;
    int  i = -1;


    strs = split_things(data->input , '|');
    i = 0  ;
    while (strs[++len]);
    data->command_count = len;
    t_command *commands;
    commands = malloc(( 1 + len) * sizeof(t_command *));

    i = 0;
    while (i < len)
    {

        
        commands[i].unsplited_command = strs[i];
        commands[i].whole_command = trim_things(split_things(strs[i] , ' '));
        commands[i].cmd = commands[i].whole_command[0];
        if (arr_couter(commands[i].whole_command) > 1)
            commands[i].args = &commands[i].whole_command[1];
        ft_lstadd_back(&data->commands, ft_lstnew(&commands[i]));
        i++;
    }
    redirection_preparations(data);
    return (0);
}