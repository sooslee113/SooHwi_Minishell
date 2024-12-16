#include "../include/minishell.h"

void	print_error_and_exit(char *err_msg)
{
	printf("%s\n", err_msg);
	exit(1);
}