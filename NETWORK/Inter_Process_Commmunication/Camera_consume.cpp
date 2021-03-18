#include <fcntl.h> // O_CREATE | ORDWR
#include <unistd.h> //ftruncate and close
#include <string.h>  // memcpy
#include <sys/shm.h>
#include <sys/mman.h> //mmap
#include <iostream>
#include <semaphore.h> //sem_t
#include <csignal> //single handler
#include<opencv2/opencv.hpp> //opencv. read camera array and image processing.
//#include"Camera.hpp"


//quit the infinity while loop in multithreading
static void handler(int signum){
    std::cout <<"Interrupt Signal: " << signum << std::endl;
    exit(signum);
}

//display image
void Show_Frame(cv::Mat &frame, bool &flag){
    cv::imshow("FRAME", frame);
    int keyboard = cv::waitKey(1);
    if (keyboard == 'q' || keyboard == 27){
        flag = false;
    }
    if (keyboard == 'p' || keyboard == 112){
        cv::waitKey(0);
    }
            
}

int main(){
    int h = 1080;
	int w = 1920;
	int c = 3;
    char buffer[h*w*c];
    int fd = shm_open("RYAN", O_CREAT | O_RDWR, 0666);
    if(fd == -1){
        std::cout<<"ERROR with shm_open. "<< std::endl;
    }
    void *addr;

    //cv::Mat frame(480,640,CV_8UC3);

    //addr= static_cast<int *>(mmap(0,sizeof(buffer),PROT_READ | PROT_WRITE,MAP_SHARED,fd,0));
    addr= static_cast<char *>(mmap(0,sizeof(buffer),PROT_READ | PROT_WRITE,MAP_SHARED,fd,0));

    sem_t *sem = sem_open("time",0);
    if (sem==SEM_FAILED) {
        std::cout << "EXIT " << std::endl;
        exit(1);
    }
    signal(SIGINT, &handler);
    bool flag = true;
    cv::Mat frame(h,w,CV_8UC3);
    while(true){
        //Mat outImg(width, height, CV_8UC1);
        memcpy(frame.data, addr,sizeof(buffer));
        //std::cout <<"good" << std::endl;
        if(!frame.empty()){
            cv::imshow("FRAME", frame);
            int keyboard = cv::waitKey(1);
            if (keyboard == 'q' || keyboard == 27){
                break;
            }
            if (keyboard == 'p' || keyboard == 112){
                cv::waitKey(0);
            }
        }
        else{
            std::cout << "NO FRAME" << std::endl;
        }

        munmap(addr,0);

                
    }
    if(close(fd) == -1){ 
        std::cout<<"ERROR with close." << std::endl;
    }
    sem_unlink("time");
   
    sem_close(sem);

}
