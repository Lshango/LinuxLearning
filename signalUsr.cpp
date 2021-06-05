#include<unistd.h>
#include<signal.h>
#include<iostream>
using namespace std;

// int got_usr1{0};
volatile sig_atomic_t got_usr1;
void sigusr1_handler(int sig){
    got_usr1 = 10;
}

int main(int argc, char* args[]){
    got_usr1 = 0;
    struct sigaction sa;
    sa.sa_handler = sigusr1_handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);

    if(sigaction(SIGUSR1, &sa, nullptr) == -1){
        perror("sigaction create");
        exit(1);
    }

    while (!got_usr1) {
        cout << "PID " << getpid() << ": working hard, get a console by #kill -USR1 pid# to stop!" << endl;
        sleep(1);
    }
    cout << "Done in by SIGUSR1 " << got_usr1 << endl;

    return 0;
}