#include "temp.h"

void sig_handler(int sig) 
{
    if (sig == SIGQUIT)
    {
        // printf("\nQuit!\n");
        // exit(1);
        printf("\nCtrl + \\\n");
        rl_on_new_line();    // 새 줄로 이동
        rl_replace_line("", 0); // 현재 입력 줄을 지움
        rl_redisplay();      // 프롬프트를 새로 표시 
    }
    else if (sig == SIGINT)
    {
        printf("\nCtrl + C\n");
        rl_on_new_line();    // 새 줄로 이동
        rl_replace_line("", 0); // 현재 입력 줄을 지움
        rl_redisplay();      // 프롬프트를 새로 표시    
    }
}

int main(int argc, char **argv)
{
  char *input;
  
  struct sigaction sa;

  sa.sa_handler = sig_handler;    // SIGINT 발생 시 handle_sigint 핸들러 호출
  sigemptyset(&sa.sa_mask);         // sa_mask를 빈 집합으로 초기화
  sigaddset(&sa.sa_mask, SIGQUIT);  // SIGQUIT 시그널을 sa_mask에 추가
  sa.sa_flags = 0;
  if (sigaction(SIGINT, &sa, NULL) == -1) 
  {
        perror("sigaction");
        exit(EXIT_FAILURE);
  }

  while(1)
  {
    input = readline("minishell$");
    if (!input) // citrl + d 는 인풋이 NULL이라는 뜻
      break;
    if(*input)
      add_history(input);
    free(input);
  }
}