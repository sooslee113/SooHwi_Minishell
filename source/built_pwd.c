#include "../include/minishell.h"
// 여기 부터 pwd
void	ft_pwd()
{
	char cwd[1024];

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
// 여기 까지가 pwd