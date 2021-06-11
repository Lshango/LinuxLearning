#include<stdio.h>
#include<unistd.h>

int main(int argc, char *argv[]){
    for (int i = 0; i < 3; i++) {
        printf("-------i = %d\n", i);
    }

    pid_t pid = fork();
    if (pid == 0){
        execlp("./forkBasic", "null", NULL);
    }

    for (int i = 0; i < 3; i++) {
        printf("+++++i = %d\n", i);
    }
    return 0;
}
