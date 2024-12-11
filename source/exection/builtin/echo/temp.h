#ifndef TEMP_H
# define TEMP_H

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <unistd.h>

int	wrdlen(const char *s, char c);
int	wordcont(char const *s, char c);
char	**ft_free(char **str);
char	*assign(const char *s, char c);
char	**ft_split(char	const *s, char c);
void  ft_echo(int argc, char **argv);
int	ft_strncmp(const char *str1, const char *str2, size_t n);

#endif