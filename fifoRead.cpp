#include<stdio.h>
#include<unistd.h>
#include<iostream>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/fcntl.h>
#include<string.h>
using namespace std;

int main(int argc, char* argv[]){
    if(argc < 2){
        cout << "Should input the pipe name as ./fifoRead myfifo." << endl;
        _exit(1);
    }

    if(access(argv[1], F_OK) == -1){
        if(mkfifo(argv[1], 0777) == -1){
            perror("create fifo file");
            _exit(1);
        }else{
            cout << "mkfifo create success ---> " << argv[1] << endl;
        }
    }

    int fd{0};
    if((fd = open(argv[1], O_RDONLY)) == -1){
        perror("Open file");
        _exit(1);
    }else{
        char buff[512];
        int num{0};
        while(true){
            int len = read(fd, buff, 512);
            buff[len] = '\0';
            if(len > 0){
                num ++;
            }else{
                sleep(1);
            }
            printf("%s, size %d, %d\n", buff, len, num);
        }
    }

    close(fd);
    return 0;
}