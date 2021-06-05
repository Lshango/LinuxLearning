#include<unistd.h>
#include<fcntl.h>
#include<iostream>
using namespace std;

int main(int args, char* argv[]){
    //this is for learning the dup & redirection
    // int file_des = open("./test.txt", O_WRONLY | O_CREAT | O_APPEND, 0660);
    // if(file_des < 0){
    //     std::cout << "ERROR in open the file test.txt" << std::endl;
    //     perror("./test.txt");
    //     return -1;
    // }
    // cout << "Before dup2" << endl;
    // if(dup2(file_des, STDOUT_FILENO) < 0){
    //     cout << "dup2 error!" << endl;
    // }
    // write(file_des, "This will be output to the file named dup.txt\n", 48);
    // std::cout << "After dup2, send this message to the file." << std::endl;
    int fd[2]{0};
    if(pipe(fd) == -1){
        perror("[pipe create the fd]\n");
        return -1;
    }

    pid_t pid = fork();
    if(pid > 0){
        cout << "This is the parent process" << endl;
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        execl("/bin/ps", "ps", "aux", nullptr);
    }else{
        cout << "This is the child process" << endl;
        dup2(fd[0], STDIN_FILENO);
        close(fd[1]);
        execl("/bin/grep", "grep", "bash", nullptr);
    }
    return 0;
}