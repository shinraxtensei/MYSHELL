#include "../minishell.h"


static int quotes_index(char *str , char quote)
{
char *e;
int index;

if(!(e = strchr(str, quote)))
    return -1;
index = (int)(e - str);
return index;
}


char **quotes_manager(t_meta_data *data)
{
    int i = 0;
    int  j = 0;
    int begin = 0;
    int end = 0;
    int quotes = 0;
    char **strs;
    while (data->input[i])
    {
        if (data->input[i]== '\"')
            quotes++;
        i++;
    }
    if(quotes % 2 != 0)
    {
        printf("error: invalid quotes");
        exit(1);
    }
    strs = malloc(sizeof(char *) * (quotes / 2) + 2);
 
    i = 0;
    while (i < quotes / 2)
    {
        if((begin = quotes_index(&data->input[i] , '\"')) != -1)
            i = begin + 1;
        if((end = quotes_index(&data->input[i] , '\"')) != -1)
            i = end + 1;
        strs[j] = ft_strjoin(ft_substr(data->input, 0 , begin) , &data->input[end + begin + 2]);
        j++;
        strs[j] = ft_substr(data->input, begin + 1, end);
        j++;
    }

    return(strs);

    
}

int main ()
{
    t_meta_data data;

    data.input = "allo  \"|  asdfasdfas\"asd | idbasiu\"  | asbasifiu\"abds";
    char **strs =  quotes_manager(&data);
    printf("%s\n" ,strs[0]);
    printf("%s\n" ,strs[1]);
    
}