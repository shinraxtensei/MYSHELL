#include "../minishell.h"

       



// create a function that will create a file and let the user write in it until he enter "end"
void herdoc(t_meta_data *data)
{
    (void) data;
    int fd;
    char *str;
    
    fd = open("herdoc", O_RDWR | O_CREAT | O_TRUNC, 0666);
    while ( ft_strncmp(str = readline(">") , "end" , 3) != 0)
        write(fd, str, ft_strlen(str));

    close(fd);
}


