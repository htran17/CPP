#include <fcntl.h> // O_CREATE | ORDWR
#include <unistd.h> //ftruncate and close
#include <string.h>  // memcpy
#include <sys/shm.h>
#include <sys/mman.h> //mmap
#include <iostream>
#include <semaphore.h> //sem_t
#include <csignal> //single handler

//compile: g++ product.cpp -o product.out -std=c++11 -lpthread -lrt

class share_time{
   public:
      uint32_t msec;
      uint32_t sec;
};

struct timespec s; 

bool loop = true;

int main(){
   share_time time_taken;
   void *addr;  
   int fd = shm_open("PSIONIC", O_CREAT | O_RDWR , 0666);
   if(fd == -1){
      printf("!!!error with shm_open.\n");
   }

   if(ftruncate(fd, sizeof(share_time)) == -1){        
      printf("!!!error with ftruncate.\n");
   }

   addr = static_cast<struct share_time *>(mmap(0, sizeof(share_time), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0));

   if(addr == MAP_FAILED){
      printf("!!!error with mmap.\n");
   }
   
   sem_t* sem = sem_open("time",O_CREAT,0644,1000);
   if (sem==SEM_FAILED) exit(1);
   
   auto signalHandler = [](int signum){
        std::cout << "Interrupt signal (" << signum << ") received.\n";
        loop = false;
        exit(signum);  

   };
   signal(SIGINT, signalHandler);  

   while(loop){
      clock_gettime(CLOCK_REALTIME, &s); 
      time_taken.msec = s.tv_nsec * 1e-6 ;
      time_taken.sec = s.tv_sec;
      std::cout <<"sec: " << time_taken.sec << ". MS: " << time_taken.msec << std::endl;       
      memcpy(addr, &time_taken, sizeof(share_time));
      munmap(addr, 0);
   }
   if(close(fd) == -1){ 
      printf("!!!error with close.\n");
   }
   

   sem_unlink("time");
   
   sem_close(sem);

   return 0;

}