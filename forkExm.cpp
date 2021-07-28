//#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<iostream>
using namespace std;

int main(int args, char* argv[]){
    pid_t pid{-1};
    pid = fork();

    if(pid > 0){
        cout << "This is the parent process " << getpid() << ", wait ......" << endl;
        int status{0};
        pid_t chld_pid = wait(&status);
        cout << "Free child process resource ---> " << chld_pid << endl;
        if(WIFEXITED(status)){
            cout << "The child process exit with " << WEXITSTATUS(status) << endl;
        }else if(WIFSIGNALED(status)){
            cout << "The child process stopped with signal " << WTERMSIG(status) << endl;
        }
    }else if(pid == 0) {
        cout << "----------------------------------------------------------\n" << 
        "This is the child process " << getpid() << ", parent process " << getppid() << endl;
        execl("/bin/ls", "ls", "-al", "/home/wanghao", NULL);
        cout << "Child process finish" << endl;
    }

    for (int i = 0; i < 4; ++i){
        cout << "--------" << i << endl;
    }
    return 0;
}
