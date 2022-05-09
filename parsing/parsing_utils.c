#include "../minishell.h"

int print_error(char *str)
{
    printf("%s\n", str);
    exit(1);
    return (0);
}


int check_inside_quotes(char *str, int index)
{

    int quotes1 ;
    int quotes2 ;
    int  i ;
    i = 0;
    quotes1 = 0;
    quotes2 = 0;
    while (i <= index)
    {
        if (str[i] == '\"' && quotes2 % 2 == 0 )
            quotes1++;
        if (str[i] == '\'' && quotes1 % 2 == 0 )
            quotes2++;
        i++;
    }
        if ( quotes1 % 2 == 0 && quotes2 % 2 == 0 )
            return (1);
        else
            return (0);
}
int find_word(char *str , char word)
{
    int i;
    i = 0;
    int quotes1;
    int quotes2;
    quotes1 = 0;
    quotes2 = 0;
    while (str[i])
    {
        if (str[i] == word  && check_inside_quotes(str, i) == 1)
            break;
        i++;
    }
    return (i);
}





int *quotes_indexer(char *str,char c ,int words)
{
    int *indexes;
    int i;
    int j;

    i = -1;
    j = 0;
    indexes = malloc (sizeof(int) * words);
    while (str[++i])
    {
        if(str[0] == ' ')
            i++;

        if ((str[i] == c) && check_inside_quotes(str, i) == 1)
        {
            while (str[i + 1] == c)
                i++;
            indexes[j] = i;
            j++;
        }
    }
    if(check_inside_quotes(str, ft_strlen(str)) == 0)
        print_error("9ad l quotes");
    indexes[j] = -1;
    return (indexes);
}


char **trim_things(char **strs)
{
    int i;
    // i = -1;
    // while(strs[++i])
    //     strs[i] = ft_strtrim(strs[i] , "\"");
    i = -1;
    while(strs[++i])
        strs[i] = ft_strtrim(strs[i] , "\'");
    i = -1;
    while(strs[++i])
        strs[i] = ft_strtrim(strs[i] , "(");
    i = -1;
    while(strs[++i])
        strs[i] = ft_strtrim(strs[i] , ")");
    return (strs);
}
