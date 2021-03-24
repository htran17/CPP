#include <fcntl.h> // O_CREATE | ORDWR
#include <unistd.h> //ftruncate and close
#include <string.h>  // memcpy
#include <sys/shm.h>
#include <sys/mman.h> //mmap
#include <iostream>
#include <semaphore.h> //sem_t
#include <csignal> //single handler
#include<opencv2/opencv.hpp> //opencv. read camera array and image processing.
#include"Camera.hpp"

int main(){
    Video_Record Ryan(1920,1080,30);
    Video_Record *Ryan_ptr = &Ryan;
    Ryan_ptr -> Camera_IPC_Consume();
    return 0;
}



