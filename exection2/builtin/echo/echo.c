#include "temp.h"

char	**lets_free(char **str)
{
  int i;

  i = 0;
  while(str[i])
  {
    free(str[i]);
    i ++;
  }
  free(str);
}

void echo_out(int argc, char **argv, int i)
{
	  char **temp;

		temp = NULL;
    while(i < argc)
    {
    		temp = ft_split(argv[i], ' ');
        write(1, temp[0], strlen(temp[0]));
				if (i != argc - 1) 
        	write(1, " " ,1);
        lets_free(temp);
        i ++;
    }
}

void  ft_echo(int argc, char **argv)
{
  int i;

	if (argc > 1 && ft_strncmp(argv[1], "-n", 2) == 0)
	{
    	if(argc > 2)
    	{
      	i = 2;
				echo_out(argc, argv, i);
    	}
	}
	else
	{
	  	if(argc > 1)
    	{
      	i = 1;
				echo_out(argc, argv, i);
    	}
    	printf("\n");
	}
}

int main(int argc, char **argv)
{
  ft_echo(argc, argv);
  return 0;
}