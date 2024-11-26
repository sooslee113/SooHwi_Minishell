#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <unistd.h>

void sig_handler(int sig) 
{
    if (sig == SIGQUIT)
    {
        printf("\nQuit!\n");
        exit(1);
    }
    else if (sig == SIGINT)
    {
        printf("\nCtrl + C\n");
        rl_on_new_line();    // 새 줄로 이동
        rl_replace_line("", 0); // 현재 입력 줄을 지움
        rl_redisplay();      // 프롬프트를 새로 표시    
    }
}

void  apply_sig(struct sigaction *sa)
{
  if (sigaction(SIGINT, sa, NULL) == -1) 
  {
        perror("sigaction");
        exit(1);
  }
  else if (sigaction(SIGQUIT, sa, NULL) == -1)
  {
        perror("sigaction");
        exit(1);
  }
}

int main()
{
  char *input;
  
  struct sigaction sa;

  // 핸들러 함수 설정
  sa.sa_handler = sig_handler;
  sa.sa_flags = 0;  // 기본 플래그 설정
  sigemptyset(&sa.sa_mask);  // 추가로 차단할 시그널 없음

  apply_sig(&sa);

  while(1)
  {

    input = readline("Input >");
    if (!input) // citrl + d 는 인풋이 NULL이라는 뜻
      break;

    if(*input)
    {
      add_history(input);
    }
    free(input);
  }
}
