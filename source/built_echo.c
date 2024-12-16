#include "../include/minishell.h"
void lets_free(char **str)
{
    int i = 0;
    while (str[i])
    {
        free(str[i]);
        i++;
    }
    free(str);
}

// echo 명령어 makefile에 넣는 법이 어려워 여기 다 넣습니다.
void echo_out(t_cmd *cmd)
{
	char **temp;

	while (cmd)
	{
		temp = ft_split(cmd->con, ' '); // 공백으로 split
		if (!temp)
			return;

		write(1, temp[0], strlen(temp[0])); // 첫 번째 단어 출력
		if (cmd->next)					  // 다음 명령어가 있다면 공백 추가
			write(1, " ", 1);

		lets_free(temp); // split 결과 해제
		cmd = cmd->next; // 다음 명령어로 이동
	}
}

void ft_echo(t_cmd *cmd)
{
	int flag_n = 0;

	// 첫 번째 명령어가 `-n`인지 확인
	if (cmd && strcmp(cmd->con, "-n") == 0)
	{
		flag_n = 1;
		cmd = cmd->next; // `-n`을 건너뛰고 다음 명령어로
	}

	echo_out(cmd); // 나머지 명령어 출력

	if (!flag_n) // `-n`이 없으면 줄바꿈
		write(1, "\n", 1);
}
// 여기까지가 echo
