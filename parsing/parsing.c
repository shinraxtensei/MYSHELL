#include "../minishell.h"

// static int characters_index(char *str , char quote)
// {
// char *e;
// int index;

// if(!(e = strchr(str, quote)))
//     return -1;
// index = (int)(e - str);
// return (index);
// }


// char **quotes_manager(t_meta_data *data)
// {
//     int i = 0;
//     int  j = 0;
//     int begin = 0;
//     int end = 0;
//     int quotes = 0;
//     char **strs;
//     while (data->input[i])
//     {
//         if (data->input[i]== '\"')
//             quotes++;
//         i++;
//     }
    // if(quotes % 2 != 0)
    // {
    //     printf("error: invalid quotes");
    //     exit(1);
    // }
//     strs = malloc(sizeof(char *) * (quotes / 2) + 2);
 
//     i = 0;
//     while (i < quotes / 2)
//     {
//         if((begin = quotes_index(&data->input[i] , '\"')) != -1)
//             i = begin + 1;
//         if((end = quotes_index(&data->input[i] , '\"')) != -1)
//             i = end + 1;
//         strs[j] = ft_strjoin(ft_substr(data->input, 0 , begin) , &data->input[end + begin + 2]);
//         j++;
//         strs[j] = ft_substr(data->input, begin + 1, end);
//         j++;
//     }

//     return(strs);

    
// }

static void check_everything(char *str , char c)
{
    int i = -1;
    int flag = 0;
    while (str[++i] != c)
    {
        if (str[i] != ' ')
        {
            flag = 1;
            break;
        }
    }
    if (flag == 0)
    {
        printf("zahya espace \n");
        exit(1);
    }
}


static int words_count(char *str , char c)
{
    int  i;
    int  words;
    int quotes1;
    int quotes2;

    i = -1;
    quotes1 = 0;
    words = 1;
    quotes2 = 0;
    while (str[++i])
    {
        if (str[i] == '\"' && quotes2 % 2 == 0)
            quotes1++;
        if (str[i] == '\'' && quotes1 % 2 == 0)
            quotes2++;
        if ((str[i] == c) && quotes1 % 2 == 0 && quotes2 % 2 == 0)
        {
            check_everything(&str[i + 1] ,str[i]);
            words++;
        }
    }
    if(quotes1 % 2 != 0 || quotes2 % 2 != 0)
    {
        printf("error: invalid quotes\n");
        exit(1);
    }
    return (words);
}

static int *quotes_indexer(char *str,char c ,int words)
{
    int *indexes;
    int i;
    int j;
    int quotes1;
    int quotes2;

    i = -1;
    j = 0;
    quotes1 = 0;
    quotes2 = 0;
    indexes = malloc (sizeof(int) * words);
    while (str[++i])
    {
        if (str[i] == '\'' && quotes2 % 2 == 0)
            quotes1++;
        if (str[i] == '\"' && quotes1 % 2 == 0)
            quotes2++;
        if ((str[i] == c) && quotes1 % 2 == 0 && quotes2 % 2 == 0)
        {
            check_everything(&str[i + 1] , str[i]);
            indexes[j] = i;
            j++;
        }
    }
    if(quotes1 % 2 != 0 || quotes2 % 2 != 0)
    {
        printf("error: invalid quotes");
        exit(1);
    }
    indexes[j] = -1;
    return (indexes);
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
    while (i < words - 1 && str)
    {
        if (i == 0)
            strs[i] = ft_substr(str , j, indexes[i]);
        else
            strs[i] = ft_substr(str , j, indexes[i]  - indexes[i - 1] - 1);
        j = indexes[i] + 1;
        i++;
    }
    j++;
    strs[i] = ft_substr(str , j - 1 ,ft_strlen(str - indexes[i]));
    i++;
    strs[i] = NULL;
    return strs;
}

int parsing(t_meta_data *data)
{
    char **strs;
    strs = split_things(data->input , '|');
    int len = 0;
    while (strs[len])
        ++len;
    int  i = -1;
    while (++i < len)
        ft_lstadd_back(data->commands,ft_lstnew(strs[i]));
    return (0);
}