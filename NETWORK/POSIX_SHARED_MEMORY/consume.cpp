#include <fcntl.h> // O_CREATE | ORDWR
#include <unistd.h> //ftruncate and close
#include <string.h>  // memcpy
#include <sys/shm.h>
#include <sys/mman.h> //mmap
#include <iostream>
#include <semaphore.h> //sem_t
#include <csignal> //single handler



class share_time{
    public:
        uint32_t msec;
        uint32_t sec;
};

bool loop = true;


int main(){
    
    share_time *time, *another_time;
    int fd = shm_open("PSIONIC", O_CREAT | O_RDWR , 0666);
    if(fd == -1){
        printf("!!!error with shm_open.\n");
    }

    void *addr;  
    addr = static_cast<struct share_time *>(mmap(0, sizeof(share_time), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0));
    
    sem_t *sem = sem_open("time",0);
    if (sem==SEM_FAILED) {
        std::cout << "EXIT " << std::endl;
        exit(1);
    }
    //lambda express singal handler
    auto signalHandler = [](int signum){
        std::cout << "Interrupt signal (" << signum << ") received.\n";
        loop = false;
        exit(signum);  

    };
    signal(SIGINT, signalHandler);  

    while(loop){

        memcpy(&time, &addr, sizeof(share_time)); 
        munmap(addr, 0);  
        if(time -> msec != another_time -> msec){
            std::cout <<"sec: " << time -> sec << ". msec: " << time -> msec << std::endl;      
        }
        time -> msec = another_time -> msec;
    }
   
    if(close(fd) == -1){ 
        printf("!!!error with close.\n");
    }
   
    sem_unlink("time");
   
    sem_close(sem);
    return 0;

}