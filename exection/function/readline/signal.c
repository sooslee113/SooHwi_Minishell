// #include <stdio.h>
// #include <signal.h>
// #include <unistd.h>

// SIGINT 신호를 처리할 함수
// void handle_sigint(int sig) {
//     printf("\nCaught signal %d: Ctrl+C Pressed!\n", sig);
// }

// int main() {
//     // SIGINT 신호에 대해 handle_sigint 함수를 처리기로 설정
//     signal(SIGINT, handle_sigint);

//     // 10초 동안 대기하며 SIGINT 신호를 기다립니다.
//     printf("Waiting for Ctrl+C (SIGINT)...\n");
//     sleep(5);

//     printf("Program finished\n");

//     return 0;
// }



// int main() {
//     // SIGINT 신호에 대해 handle_sigint 함수를 처리기로 설정
//     signal(SIGQUIT, handle_sigint);

//     // 7초 동안 대기하며 SIGQUIT 신호를 기다립니다.
//     printf("Waiting for Ctrl+C (SIGINT)...\n");
//     sleep(7);

//     printf("Program finished\n");

//     return 0;
// }

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

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
    else if (sig == SIGTERM)
    {
        printf("\nExit\n");
        exit(-1);
    }

}

int main()
{
  char *input;
    signal(SIGQUIT, sig_handler);
    signal(SIGINT, sig_handler);
    signal(SIGTERM, sig_handler); 
  while(1)
  {

    input = readline("Input >");
    if (!input) // citrl + d 는 인풋이 NULL이라는 뜻
      break;
    
    //printf("You entered: %s\n", input);

    if(*input)
    {
      add_history(input);
    }
        //     rl_on_new_line();    // 새 줄로 이동
        // rl_replace_line("", 0); // 현재 입력 줄을 지움
        // rl_redisplay();      // 프롬프트를 새로 표시    

    free(input);
  }
}
