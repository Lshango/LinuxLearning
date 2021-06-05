#include<unistd.h>
#include<sys/wait.h>
#include<iostream>
#include<fcntl.h>
using namespace std;
// const int N{10};
// int main(int args, char* argv[]){
//     pid_t pid[N];
//     int i, child_status;
//     for (i = 0; i < N; i++) {
//     if ((pid[i] = fork()) == 0) {
//     /* Child */
//         sleep(i % 3);
//         printf("Done %d\n", getpid());
//         exit(i);
//         }
//     }
//     for (i = 0; i < N; i++) {
//         pid_t wpid = waitpid(-1, &child_status, 0);
//         if (WIFEXITED(child_status))
//             printf("Saw %d done with %d\n", wpid, WEXITSTATUS(child_status));
//         else
//             printf("Child %d terminated abnormally\n", wpid);
//     }
// }

int main(int args, char* argv[]){
    int fd[2]{0};
    if(pipe(fd) == -1){
        perror("[pipe create the fd]\n");
        return -1;
    }
    int child{0};
    for (; child < 2; ++child){
        pid_t pid = fork();
        if(pid == 0){
            break;
        } 
        if(pid < 0){
            perror("fork error");
        }   
    }

    if (child == 0) {//this is the first child process;
        cout << "This is the first child process ---> " << getpid() << ", parent ---> " << getppid() << endl;
        cout << "This pipe size ---> " << fpathconf(fd[1], _PC_PIPE_BUF) << endl;
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        execl("/bin/ps", "ps", "aux", nullptr);
    }

    if (child == 1) {//this the second child process;
        cout << "This is the second child process ---> " << getpid() << ", parent ---> " << getppid() << endl;
        dup2(fd[0], STDIN_FILENO);
        cout << "This pipe size ---> " << fpathconf(fd[0], _PC_PIPE_BUF) << endl;
        // int flags = fcntl(fd[0], F_GETFL);  //获取原来的 flags， F_GET FL （get flags 的缩写）
        // flags |= O_NONBLOCK;                //添加非阻塞属性
        // fcntl(fd[0], F_SETFL, flags);      //设置新的属性
        close(fd[1]);
        execl("/bin/grep", "grep", "bash", "--color=auto", nullptr);
    }

    if (child == 2){//this is the parent process;
        cout << "This is the parent process ---> " << getpid() << endl;
        close(fd[0]);
        close(fd[1]);
        int wpid{0}, status{0};
        while((wpid = waitpid(-1, nullptr, WNOHANG)) != -1){//all child process
        // while((wpid = wait(&status)) != -1){//all child process
            if (wpid == 0 || wpid == 1) {
                // cout << "--------------------------" << endl;
                continue;
            }
            cout << "child died pid ---> " << wpid <<endl;
        }
    }
    return 0;
}