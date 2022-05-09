#include "../../minishell.h"

void fun_pwd()
{
    char arr[90000];

    // printf("%s\n",getcwd(arr,90000));
    ft_putstr_fd(getcwd(arr,90000),1);
}