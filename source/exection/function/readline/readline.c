#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int main()
{
  char *input;

  while(1)
  {
    input = readline("Input >");
    if (!input)
      break;
    
    printf("You entered: %s\n", input);

    if(*input)
    {
      add_history(input);
    }

    free(input);
  }
}
