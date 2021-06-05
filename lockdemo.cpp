#include<unistd.h>
#include<fcntl.h>
#include<iostream>
using namespace std;

int main(int argc, char* argv[]){
                       /* l_type   l_whence  l_start  l_len  l_pid   */
    struct flock fl = {F_WRLCK, SEEK_SET,   0,      0,     0 };
    fl.l_pid = getpid();
    if (argc > 1) {
        fl.l_type = F_RDLCK;
    }
    int fd;
    if ((fd = open("lockdemo.cpp", O_RDWR)) == -1) {
        perror("open, lockdemo.cpp");
        exit(1);
    }

    cout << "Press <RETURN> to try to get lock: " << endl;
    getchar();
    cout << "Trying to get lock..." << endl;

    if (fcntl(fd, F_SETLKW, &fl) == -1) {
        perror("fcntl");
        exit(1);
    }

    cout << "got lock" << endl;
    cout << "Press <RETURN> to release lock: " << endl;
    getchar();

    fl.l_type = F_UNLCK;  /* set to unlock same region */

    if (fcntl(fd, F_SETLK, &fl) == -1) {
        perror("fcntl");
        exit(1);
    }

    cout << "Unlocked" << endl;
    close(fd);
    return 0;    
}