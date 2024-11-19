#include "../../../include/minishell.h"

int main()
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
        return 1;
    }
    return 0;
}
