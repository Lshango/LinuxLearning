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
        cout << "Should input the pipe name as ./fifoWrite myfifo." << endl;
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
    if((fd = open(argv[1], O_WRONLY)) == -1){
        perror("Open file");
        _exit(1);
    }else{
        const char* msg = "2020-12-01 wanghao~";
        int i = 10;
        while(i--){
            cout << "write msg = (" << msg << "), " << i << endl;
            write(fd, msg, strlen(msg)+1);
            sleep(1);
        }
    }

    close(fd);
    return 0;
}