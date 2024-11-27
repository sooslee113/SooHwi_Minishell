#include "minishelltemp.h"

void    ft_pwd()
{
    char cwd[1024];

    // 현재 작업 디렉터리 경로 얻기
    if (getcwd(cwd, sizeof(cwd)) != NULL) 
    {
        printf("%s\n", cwd);
    } 
    else 
    {
        perror("getcwd");
        return ;
    }
    return ;
}
