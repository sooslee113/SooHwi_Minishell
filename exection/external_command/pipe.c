#include "../../include/minishell.h"

// void	*safe_malloc(size_t bytes)
// {
// 	void	*ret;

// 	ret = malloc(bytes);
// 	if (NULL == ret)
// 	{
// 		perror("malloc errror");
// 		return (NULL);
// 	}
// 	return (ret);
// }

// void free_pipe(t_pipe *pipe)
// {
//     t_pipe *temp;

//     while (pipe != NULL)
//     {
//         temp = pipe->next;

//         free(pipe->fd);
//         if (pipe->redlist)
//         {
//             free(pipe->redlist->type);
//             free(pipe->redlist->file_name);
//             free(pipe->redlist);
//         }

//         free(pipe);
//         pipe = temp;
//     }
// }



// // typedef struct s_redlist //통합(mini"sh"ell)구조체
// // {
// // 	char *type;
// // 	char *file_name;
// // }t_redlist;

// // typedef struct s_pipe // pipe 구조체
// // {
// // 	char **argv;
// // 	int exit_code;
// // 	int *fd;
// //     pid_t   pid;
// // 	t_redlist *redlist;
// // 	struct s_pipe *next;
// // 	struct s_pipe *prev;
// // }t_pipe;

// void    init_pipe(t_pipe **pipe, char **argv)
// {
//     *pipe = safe_malloc(sizeof(t_pipe));
//     (*pipe) -> argv = argv;
//     (*pipe) -> exit_code = 1;
//     (*pipe) -> fd = safe_malloc(sizeof(int) * 2);
//     (*pipe) -> pid = 0;
//     (*pipe) -> redlist = safe_malloc(sizeof(t_redlist));
//     (*pipe)->redlist->type = NULL;
//     (*pipe)->redlist->file_name = NULL;
//     (*pipe)->next = NULL;
//     (*pipe)->prev = NULL;
// }

// void    append_cmd(t_pipe **pipe_line, char **argv)
// {
//     t_pipe  *new_node;
//     t_pipe	*temp_head;

//     init_pipe(&pipe_line, argv);
//     if ((*pipe_line) = NULL)
//         *pipe_line = new_node;
//     else
//     {
//         temp_head = *pipe_line;
//         while(temp_head -> next != NULL)
//             temp_head = temp_head -> next;
//         temp_head->next = new_node;
//         new_node->prev = temp_head;
//         new_node -> next = NULL;
//     }
// }
// // init pipe
// void    full_pipe(t_pipe **pipe_line, int argc, char **argv)
// {
//     int i;
    
//     i = 0;
//     while(i < argc)
//     {
//         append_cmd(pipe_line, &argv[i]);
//         i ++;
//     }
// }

// int main(int argc, char **argv, char **envp)
// {
//     t_pipe *pipe_line;

//     pipe_line = NULL;
//     //init_pipe(&pipe_line, argv);
//     full_pipe(&pipe_line, argc, argv);
//     if (argc == 1)
//     {
//         perror("argv is not enough");
//         exit(1);
//     }
//     t_pipe *temp = pipe_line;
//     printf("Commands in pipe:\n");
//     while (temp != NULL)
//     {
//         printf("- %s\n", temp->argv[0]);
//         temp = temp->next;
//     }

//     free_pipe(pipe_line);
// }

#include "../../include/minishell.h"

void *safe_malloc(size_t bytes)
{
    void *ret;

    ret = malloc(bytes);
    if (NULL == ret)
    {
        perror("malloc error");
        exit(EXIT_FAILURE);
    }
    return (ret);
}

void free_pipe(t_pipe *pipe)
{
    t_pipe *temp;

    while (pipe != NULL)
    {
        temp = pipe->next;

        free(pipe->fd);
        if (pipe->redlist)
        {
            free(pipe->redlist->type);
            free(pipe->redlist->file_name);
            free(pipe->redlist);
        }

        free(pipe);
        pipe = temp;
    }
}

void init_pipe(t_pipe **pipe, char **argv)
{
    *pipe = safe_malloc(sizeof(t_pipe));
    (*pipe)->argv = argv;
    (*pipe)->exit_code = 1;
    (*pipe)->fd = safe_malloc(sizeof(int) * 2);
    (*pipe)->pid = 0;
    (*pipe)->redlist = safe_malloc(sizeof(t_redlist));
    (*pipe)->redlist->type = NULL;
    (*pipe)->redlist->file_name = NULL;
    (*pipe)->next = NULL;
    (*pipe)->prev = NULL;
}

void append_cmd(t_pipe **pipe_line, char **argv)
{
    t_pipe *new_node;
    t_pipe *temp_head;

    init_pipe(&new_node, argv); // 수정된 부분: new_node를 새로 초기화
    if (*pipe_line == NULL) // 리스트가 비어 있으면 새 노드를 head로 설정
    {
        *pipe_line = new_node;
    }
    else
    {
        temp_head = *pipe_line;
        while (temp_head->next != NULL) // 마지막 노드를 찾음
            temp_head = temp_head->next;
        temp_head->next = new_node; // 새 노드를 마지막에 추가
        new_node->prev = temp_head;
    }
}

void full_pipe(t_pipe **pipe_line, int argc, char **argv)
{
    int i = 1; // argv[0]은 프로그램 이름이므로 1부터 시작
    while (i < argc)
    {
        append_cmd(pipe_line, &argv[i]);
        i++;
    }
}

int main(int argc, char **argv, char **envp)
{
    t_pipe *pipe_line = NULL;

    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <commands>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    full_pipe(&pipe_line, argc, argv);

    // 연결 리스트 출력
    t_pipe *temp = pipe_line;
    printf("Commands in pipe:\n");
    while (temp != NULL)
    {
        printf("- %s\n", temp->argv[0]);
        temp = temp->next;
    }

    // 메모리 해제
    free_pipe(pipe_line);

    return 0;
}
