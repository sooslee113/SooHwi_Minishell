
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(int argc, char **argv)
{


      printf("히히 들어왔다\n");
      if (chdir("/home/sooslee/Minishell/builtin/cd/test") == 0)
        printf("성공?\n");

    return 0;
}