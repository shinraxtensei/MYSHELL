#include "../../minishell.h"

void fun_pwd()
{
    char arr[90000];

    getcwd(arr,90000);
    printf("%s\n",arr);
}